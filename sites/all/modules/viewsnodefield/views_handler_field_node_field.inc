<?php

/**
 * Field handler to present a node.
 */
class views_handler_field_node_field extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['nid'] = 'nid';
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['build_mode'] = array('default' => 'teaser');
    $options['links'] = array('default' => TRUE);
    $options['comments'] = array('default' => FALSE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // CCK holds the registry of available build modes, but can hardly
    // push them as options for the node row style, so we break the normal
    // rule of not directly relying on non-core modules.
    if ($modes = module_invoke('content', 'build_modes')) {
      $options = array();
      foreach ($modes as $key => $value) {
        if (isset($value['views style']) && $value['views style']) {
          $options[$key] = $value['title'];
        }
      }
    }
    else {
      $options = array(
        'teaser' => t('Teaser'),
        'full' => t('Full node')
      );
    }
    $form['build_mode'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#title' => t('Build mode'),
      '#default_value' => $this->options['build_mode'],
     );
    $form['links'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display links'),
      '#default_value' => $this->options['links'],
    );
    $form['comments'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display node comments'),
      '#default_value' => $this->options['comments'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    return theme('views_view_row_node', $this->view, $this->options, $values, $this->aliases['nid']);
  }
}
