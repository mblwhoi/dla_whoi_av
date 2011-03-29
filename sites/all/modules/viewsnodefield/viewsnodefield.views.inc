<?php

/**
 * Implementation of hook_views_data(). 
 */
 
 function viewsnodefield_views_data() {
  $data['node']['nodefield'] = array(
    'field' => array(
      'title' => t('Node field'),
      'help' => t('Display the node.'),
      'handler' => 'views_handler_field_node_field',
    ),
  );
  return $data;
}

/**
 * Implementation of hook_views_handlers(). 
 */
 
function viewsnodefield_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'viewsnodefield') ,
    ),
    'handlers' => array(
      // field handlers
      'views_handler_field_node_field' => array(
        'parent' => 'views_handler_field',
      ),
    )
  );
}
