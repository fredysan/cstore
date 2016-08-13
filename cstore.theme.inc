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
    'path' => base_path() . drupal_get_path('module', 'cstore') . '/images/delete.png',
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
  $prefix = '<div class="cstore-cart-contents row">';
  $prefix .= '  <div class="cstore-delete-image cell">' . $delete_link . '</div>';
  $prefix .= '  <div class="cstore-cart-node-title cell">' . l($node->title, 'node/' . $nid) . '<br />';
  $prefix .= '    <span class="cstore-cart-node-summary">' . $desc . '</span>';
  $prefix .= '  </div>';
  $prefix .= '  <div class="cell cstore-cart-unit-price"><strong>' . $unit_price . '</strong></div>';
  $prefix .= '  <div class="cell cstore-cart-x">x</div>';
  $prefix .= '  <div class="cstore-cart-quantity cell">';
  $prefix .= '    <div class="cell">';
  // Suffix.
  $suffix = '    </div>';
  $suffix .= '  </div>';
  $suffix .= '</div>';

  // Rendering the element as textfield.
  $quantity = theme('textfield', $variables['form']);
  // Full view return.
  return $prefix . $quantity . $suffix;
}

/**
 * Theme implementation for rendering the total price.
 * 
 * @todo find a way to pass $price through the variables array.
 */
function theme_cstore_cart_total_price($variables) {
  $price = cstore_get_total_price();
  $total = cstore_price_format($price->total);

  // Building the HTML.
  $html = '<div class="cstore-cart-total-price-contents row">';
  $html .= '  <div class="cstore-total-price cell">' . t('Total price') . ': <strong>' . $total . '</strong></div>';
  $html .= '</div>';

  $vat_is_enabled = (int) variable_get('cstore_vat_state');
  if (!empty($vat_is_enabled) && $vat_is_enabled) {
    $vat_value = cstore_price_format($price->vat);
    $html .= '<div class="cstore-cart-total-vat-contents row">';
    $html .= '  <div class="cstore-total-vat cell">' . t('Total VAT') . ': <strong>' . $vat_value . '</strong></div>';
    $html .= '</div>';
  }

  return $html;
}

function theme_cstore_receipt($order) {
  $html = '';
  $html .= '<h3 class="customer-title">Customer</h3>';

  $html .= '<table class="table cstore-customer-table">';
  $html .= '<tr>';
  $html .= '<th scope = "row">' . t('Name:') . '</th>';
  $html .= '<td>' . $order['customer_name'] . '</td>';
  $html .= '</tr>';
  $html .= '<tr>';
  $html .= '<th scope = "row">' . t('Identification:') . '</th>';
  $html .= '<td>' . $order['customer_id'] . '</td>';
  $html .= '</tr>';
  $html .= '<tr>';
  $html .= '<th scope = "row">' . t('Email:') . '</th>';
  $html .= '<td>' . $order['customer_email'] . '</td>';
  $html .= '</tr>';
  $html .= '</tbody>';
  $html .= '</table>';

  $html .= '<div id="cstore-order-details">';
  $html .= '<h3 class="details-title">Details</h3>';

  $html .= '<table class="table cstore-details-table">';
  $html .= '<tr>';
  $html .= '<th>' . t('Product') . '</th>';
  $html .= '<th>' . t('Quantity') . '</th>';
  $html .= '<th>' . t('Price') . '</th>';
  $html .= '</tr>';
  $html .= '</tbody>';

  foreach ($order['details'] as $detail) {
    $html .= '<tr>';
    $html .= '<td>' . $detail['product'] . '</td>';
    $html .= '<td>' . $detail['quantity'] . '</td>';
    $html .= '<td>' . $detail['quantity'] * $detail['unit_price'] . '</td>';
    $html .= '</tr>';
  }

  $html .= '<tr>';
  $html .= '<td></td><td class="cstore-receipt-total">' . t('Total:') . '</td>';
  $html .= '<td class="cstore-receipt-total">' . $order['total'] . '</td>';
  $html .= '</tr>';
  $html .= '</tbody><table>';
  $html .= '</div>'; // Close cstore-order-details

  return $html;
}
