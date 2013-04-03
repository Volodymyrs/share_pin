<div class="form-add-favorites">

  <?php
  print render($form['form_id']);
  print render($form['form_token']);
  print render($form['form_build_id']);
  //
  // echo '<pre>';
  // print_r(array_keys($form));
  // echo '</pre>';

  ?>
  <div class="pin_head">
    <div class="left pointer" onmouseover="this.style.background = 'url(<?php print 'http://'.$_SERVER["HTTP_HOST"].'/'.drupal_get_path('module', 'share_pin'); ?>/images/pinwin_bgr_hover.png)'" onmouseout="this.style.background = ''" style="">
      <img src="<?php print 'http://'.$_SERVER["HTTP_HOST"].'/'.drupal_get_path('module', 'share_pin'); ?>/images/pinwin_logo.png">
    </div>
    <div class="pin_close_wrap right pointer" onclick="window.close();">
      <div class="pin_close">
      </div>
    </div>
    <div class="pin_head_separator right">
    </div>
  </div>

  <div class="inline-title">
    <?php print render($form['title']); ?>
  </div>

  <div class="inline-body">
    <?php print render($form['body']); ?>
  </div>


  <div class="fields-summary">
    <div class="add-interests">
      <?php print render($form['field_interests']); ?>
      <?php print render($form['field_tags']); ?>
    </div>
    <?php print render($form['field_source']); ?>
    <?php print render($form['field_image']); ?>
  </div>

  <div class="inline buttons">
    <?php print render($form['actions']); ?>
  </div>
</div>
