<?php

/**
 * Implements hook_views_data().
 */
function cstore_views_data() {
  $data = array();
  
  // Order table
  $data['cstore_order']['table']['group'] = t('Orders');
  $data['cstore_order']['table']['base'] = array(
    'title' => t('Orders'),
    'help' => t('Contains records we want cstore to Views.'),
  );
  $data['cstore_order']['table']['join'] = array(
    'cstore_order_details' => array(
      'left_field' => 'oid',
      'field' => 'oid',
    ),
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
    'relationship' => array(
      'base' => 'cstore_order_details',
      'field' => 'oid',
      'handler' => 'views_handler_relationship',
      'label' => t('Order'),
    ),
  );
  // Order creation date
  $data['cstore_order']['created'] = array(
    'title' => t('Creation date'),
    'help' => t('Order creation date'),
    'field' => array(
      'handler' => 'views_date_format_sql_handler_field_date',
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
  
  // Order details table
  $data['cstore_order_details']['table']['group'] = t('Order details');
  $data['cstore_order_details']['table']['base'] = array(
    'field' => 'oid',
    'title' => t('Order details'),
    'help' => t('Contains records we want cstore to Views.'),
  );
  // Foreign key
  $data['cstore_order_details']['oid'] = array(
    'title' => t('Order id from details'),
    'help' => t('The order id from details'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'title',
      'numeric' => TRUE,
      'validate type' => 'nid',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  // Foreign key
  $data['cstore_order_details']['nid'] = array(
    'title' => t('Product node id'),
    'help' => t('The product node id'),
    'field' => array(
      'handler' => 'views_handler_field_node',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_node_nid',
      'name field' => 'title',
      'numeric' => TRUE,
      'validate type' => 'nid',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  // Product
  $data['cstore_order_details']['product'] = array(
    'title' => t('Product name'),
    'help' => t('The saved product name'),
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
  // Unit price
  $data['cstore_order_details']['unit_price'] = array(
    'title' => t('Unit price'),
    'help' => t('The unit price'),
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
  // Quantity
  $data['cstore_order_details']['quantity'] = array(
    'title' => t('Quantity'),
    'help' => t('The quantity'),
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
