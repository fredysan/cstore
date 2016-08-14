<?php

function cstore_reports_monthy_sales() {
  $query = db_select('cstore_order', 'o');
  $query->addExpression('COUNT(o.total)', 'total');
  $query->fields('o', array('created'));
  $query->groupBy('o.created');
  $result = $query->execute();
  dpq($query);
  $row = $result->fetchAssoc();
  
  
  return '...';
}

function cstore_reports_ranking_sales() {
  drupal_goto('/cstore/reports/cupcakes-ranking');
  return;
}
