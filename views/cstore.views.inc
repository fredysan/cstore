<?php

/**
 * Implements hook_views_data().
 */
function cstore_views_data() {
  $data = array();
  $data['cstore_order']['table']['group'] = t('Cupcake store');
  $data['cstore_order']['table']['base'] = array(
    'title' => t('Orders'),
    'help' => t('Contains records we want cstore to Views.'),
  );

  // Id
  $data['cstore_order']['oid'] = array(
    'title' => t('Order id'),
    'help' => t('The order id.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  // Order creation date
  $data['cstore_order']['created'] = array(
    'title' => t('Creation date'),
    'help' => t('Order creation date'),
    'field' => array(
      'handler' => 'views_handler_field_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  // Customer name
  $data['cstore_order']['customer_name'] = array(
    'title' => t('Customer name'),
    'help' => t('Order customer name'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );
  
  // Total
  $data['cstore_order']['total'] = array(
    'title' => t('Total price'),
    'help' => t('The total price'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  return $data;
}
