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
