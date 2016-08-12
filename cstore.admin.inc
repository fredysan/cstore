<?php

/**
 * 
 * @param type $form
 * @param type $form_state
 */
function cstore_admin_form($form, &$form_state) {
  $form = array();

  $node_types = node_type_get_types();
  if (empty($node_types)) {
    return NULL;
  }

  $options = array();
  foreach ($node_types as $node_type => $type) {
    if ($node_type == 'order') {
      continue;
    }
    $options[$node_type] = check_plain($type->name);
  }
  
  $default_value = array();
  foreach (cstore_product_types() as $product_type) {
    if (isset($options[$product_type])){
      $default_value[$product_type] = $product_type;
    }
  }

  $form['content_type'] = array(
    '#title' => t('Content type selection'),
    '#type' => 'fieldset',
    '#description' => t('Please select the content types for which you wish to have the "Add to cart" option.'),
  );

  $form['content_type']['cstore_content_types'] = array(
    '#title' => t('Content types'),
    '#type' => 'checkboxes',
    '#options' => $options,
    '#default_value' => $default_value,
  );
  
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));

  return $form;
}


/**
 * Callback submit function for the settings page.
 */
function cstore_admin_form_submit($form, &$form_state) {
  // Remove internal Form API values.
  unset($form_state['values']['form_id'], $form_state['values']['form_token'], $form_state['values']['form_build_id'], $form_state['values']['op']);

  $product_types = array();
  
  // Setting up the price field for the selected content types.
  $content_types = $form_state['values']['cstore_content_types'];
  
  // Unset to prevent 'double' save
  unset($form_state['values']['cstore_content_types']);
  
  if (!empty($content_types) && is_array($content_types)) {
    foreach (cstore_get_fields() as $field_name => $field_) {
      // Check to see if the field already exists.
      $field = field_info_field($field_name);
      // If the field does not exist then create it.
      if (empty($field)) {
        $field = array(
          'field_name' => $field_name,
          'type' => $field_['type'],
          'entity_types' => array('node'),
        );
        
        if (isset($field_['cardinality'])) {
          $field['cardinality'] = $field_['cardinality'];
        }
        
        field_create_field($field);
      }
    }
    
    foreach ($content_types as $type => $checked) {
      
      // If a node type is checked, then create the price field.
      if ($checked) {
        // Save content_type as a product.
        $product_types[$type] = $type;
        
        foreach (cstore_get_fields() as $field_name => $field_) {
          // Foreach checked content type, we must assign the price field to the content type.
          $instance = field_info_instance('node', $field_name, $type);

          if (empty($instance)) {
            $instance = array(
              'field_name' => $field_name,
              'label' => $field_['title'],
              'description' => $field_['description'],
              'entity_type' => 'node',
              'bundle' => $type,
            );
            
            if (isset($field_['settings'])) {
              $instance['settings'] = $field_['settings'];
            }
            
            
            
            // It doesn't exist. Create it.
            field_create_instance($instance);
          }
        }
      }
      // If not, then delete the instance.
      else {
        foreach (cstore_get_fields() as $field_name => $field_) {
          $instance = field_info_instance('node', $field_name, $type);
          if (!empty($instance)) {
            field_delete_instance($instance);
          }
        }
      }
    }
  }

  variable_set('cstore_content_types', $product_types);
  
  // Save other variables.
  foreach ($form_state['values'] as $key => $value) {
    if (is_array($value) && isset($form_state['values']['array_filter'])) {
      $value = array_keys(array_filter($value));
    }
    variable_set($key, $value);
  }
  
  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * 
 * @param type $form
 * @param type $form_state
 */
function cstore_admin_theming_form($form, &$form_state) {
  $form = array();
  
  $form['cstore_buy_button_class'] = array(
    '#title' => t('Css class for the buy button'),
    '#type' => 'textfield',
    '#required' => FALSE,
    '#default_value' => variable_get('cstore_buy_button_class', 'btn'),
  );
  
  return system_settings_form($form);
}
