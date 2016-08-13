<?php

module_load_include('inc', 'cstore', 'cstore.cart');

/**
 * Callback function for cart listing.
 */
function cstore_order_checkout() {
  $cart = cstore_get_cart();

  if (empty($cart)) {
    return t('Your cart is empty.');
  }

  return drupal_get_form('cstore_order_checkout_form');
}

/**
 * 
 * @param type $form
 * @param type $form_state
 * @return type
 */
function cstore_order_checkout_form($form, &$form_state) {
  $form = array();

  // Total price.
  $form['total_price'] = array(
    '#markup' => t('Total price'),
    '#prefix' => '<div class="cstore-cart cstore-grid">',
    '#suffix' => '</div>',
    '#theme' => 'cstore_cart_total_price',
  );

  $form['customer_id'] = array(
    '#type' => 'textfield',
    '#name' => 'customer_id',
    '#title' => t('Document number'),
    '#required' => TRUE,
  );

  $form['customer_name'] = array(
    '#type' => 'textfield',
    '#name' => 'customer_name',
    '#title' => t('Full name'),
    '#required' => TRUE,
  );

  $form['customer_email'] = array(
    '#type' => 'textfield',
    '#name' => 'customer_email',
    '#title' => t('Email'),
    '#required' => TRUE,
  );

  // Buttons.
  $form['buttons'] = array(
    // Make the returned array come back in tree form.
    '#tree' => TRUE,
    '#prefix' => '<div class="row"><div class="cstore-call-to-action cell">',
    '#suffix' => '</div></div>',
  );
  $form['buttons']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
  );
  $form['buttons']['order'] = array(
    '#type' => 'submit',
    '#value' => t('Enjoy'),
  );

  return $form;
}

/**
 * 
 * @global type $user
 * @param type $form_id
 * @param type $form_state
 */
function cstore_order_checkout_form_submit($form_id, $form_state) {
  global $user;

  $customer = array(
    'id' => $form_state['values']['customer_id'],
    'name' => $form_state['values']['customer_name'],
    'email' => $form_state['values']['customer_email'],
  );
  $total_price = cstore_get_total_price();
  $order_data = array(
    'uid' => $user->uid,
    'created' => time(),
    'total' => $total_price->total,
    'customer_id' => $customer['id'],
    'customer_name' => $customer['name'],
    'customer_email' => $customer['email'],
  );

  $oid = db_insert('cstore_order')->fields($order_data)->execute();

  $cart = cstore_get_cart();
  foreach ($cart as $nid => $node) {
    $order_details_data = array(
      'oid' => $oid,
      'nid' => $nid,
      'product' => $node->title,
      'unit_price' => $node->cstore_unit_price,
      'quantity' => $node->cstore_quantity,
    );

    $odid = db_insert('cstore_order_details')->fields($order_details_data)->execute();
  }

  // cstore_empty_cart();

  drupal_goto('checkout/receipt/' . $oid);
}

/**
 * 
 * @return type
 */
function cstore_order_checkout_receipt($oid) {
  $message = t('Thank you for your purchase: ' . $oid);

  $query = db_select('cstore_order', 'o');
  $query->fields('o');
  $query->condition('o.oid', $oid);
  $query->range(0, 1);
  $result = $query->execute();
  $row = $result->fetchAssoc();

  if (empty($row)) {
    drupal_set_message(t('There are no orders that coincide with the request parameters'));
    return '';
  }
  
  $order = $row;
  $order['details'] = array();
  
  $query = db_select('cstore_order_details', 'od');
  $query->fields('od');
  $query->condition('od.oid', $oid);
  $result = $query->execute();
  
  while ($row = $result->fetchAssoc()) {
    $order['details'][] = $row;
  }
  
  drupal_set_title(t('Order: ' . $oid));
  
  return theme('cstore_receipt', $order);

}
