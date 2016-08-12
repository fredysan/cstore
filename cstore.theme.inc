<?php

/**
 * Theme function implementation.
 */
function cstore_add_to_cart_button($vars) {
  $path = $vars['path'];
  $css_class = $vars['css_class'];
  $options = array(
    'attributes' => array(
      'class' => array($css_class)
    )
  );
  return '<div class="cstore-add-to-cart">' . l(t('Add to cart'), $path, $options) . '</div>';
}


/**
 * Theme implementation for rendering the cart element.
 */
function theme_cstore_render_cart_element($variables) {
  // Element name and nid.
  $name = $variables['form']['#name'];
  $nid = (int) str_replace(array('cartcontents[', ']'), '', $name);
  if (empty($nid)) {
    return '';
  }
  // Delete image.
  $vars = array(
    'path' => base_path() . drupal_get_path('module', 'cstore') . '/images/delete2.png',
    'alt' => t('Remove from cart'),
    'title' => t('Remove from cart'),
    'attributes' => array('class' => 'cstore-delete-image-image'),
  );
  $delete_link = l(theme('image', $vars), 'cart/remove/' . $nid, array('html' => TRUE));
  // Getting the node for it's title and description.
  $node = cstore_get_cart($nid);
  // Node description.
  $desc = '';
  if (isset($node->cstore_node_description)) {
    $desc = drupal_strlen($node->cstore_node_description) > 50 ?
                truncate_utf8($node->cstore_node_description, 50) : $node->cstore_node_description;
  }
  // Price and currency.
  $unit_price = isset($node->cstore_unit_price) ? $node->cstore_unit_price : 0;
  $unit_price = cstore_price_format($unit_price);
  
  // Prefix.
  $prefix  = '<div class="cstore-cart-contents row">';
  $prefix .= '  <div class="cstore-delete-image cell">' . $delete_link . '</div>';
  $prefix .= '  <div class="cstore-cart-node-title cell">' . l($node->title, 'node/' . $nid) . '<br />';
  $prefix .= '    <span class="cstore-cart-node-summary">' . $desc . '</span>';
  $prefix .= '  </div>';
  $prefix .= '  <div class="cell cstore-cart-unit-price"><strong>' . $unit_price . '</strong></div>';
  $prefix .= '  <div class="cell cstore-cart-x">x</div>';
  $prefix .= '  <div class="cstore-cart-quantity cell">';
  $prefix .= '    <div class="cell">';
  // Suffix.
  $suffix  = '    </div>';
  $suffix .= '  </div>';
  $suffix .= '</div>';
  
  // Rendering the element as textfield.
  $quantity = theme('textfield', $variables['form']);
  // Full view return.
  return $prefix . $quantity . $suffix;
}
