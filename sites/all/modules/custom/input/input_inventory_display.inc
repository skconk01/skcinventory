<?php

/**
 * @filesource 
 * this page will handle displaying the inventory to the 
 * web page
 */


/**
 * Displays paginated table list of all systems in the inventory
 */
 function system_inventory_page(){
 	
 	$stop = 'here';
 
 	// get access to the user name
 	global $user;
 	
 	if(isset($user->name)){
 		$name = $user->name;
 	}else {
 		$form['loginerror'] = array(
 				'#type' => 'item',
 				'#title' => t('You will need to login to proceed.'),
 		);
 		return $form;
 	}
 	 
 	
	// Headers for theme_table().
 	//$header = array('user_id', 'hostname', 'ip_address', 'asset_tag');

	$header = array(
       array('data' => 'User Id', 'field' => 'user_id', 'sort' => 'ASC'),
	   array('data' => 'Host Name', 'field' => 'hostname', 'sort' => 'ASC'),
	   array('data' => 'Primary OS', 'field' => 'primary_os', ),
       array('data' => 'OS Version', ),	//without field 		
	   array('data' => 'Ip Address', ),
	   array('data' => 'Asset Tag', ),
       array('data' => 'Information File', ),			
	   );


	$select = db_select('zz_team_inv', 'zti')
	  ->extend('PagerDefault')
	  ->extend('TableSort')
	  ->fields('zti', array('inv_id','user_id', 'hostname', 'primary_os', 'ip_address', 'asset_tag',))
	  ->orderByHeader($header)
	  //->orderBy('user_id', 'DESC')
	  ->limit(10)
	  ;
	

// 	$select = db_select('zz_team_inv', 'zti');
// 	//$select->join('zz_system_os', 'os', 'os.zz_team_inv_inv_id = zti.inv_id', 'os.sos_type=P');
	
	
	
// 	$result = $select
//     	->extend('PagerDefault')
//     	->extend('TableSort')
//     	->orderByHeader($header)
//     	->fields('zti', array('inv_id', 'user_id', 'hostname', 'primary_os', 'ip_address', 'asset_tag' ))
//     	//->fields('os', array('sos_version'))
// 		->limit(3)	
//     	;
	
// 	$select->condition('user_id', $user->name)
// 	  ->fields('zti', array('user_id', 'hostname', 'ip_address', 'asset_tag'))
// 	  ->limit(2)
// 	  ->orderByHeader($header)
// 	  ->orderBy('user_id', 'DESC')
// 	  ;


 	/* // Begin building the query. */
 	/* $query = db_select('zz_team_inv', 'zti') */
 	/* ->extend('PagerDefault') */
 	/* ->extend('TableSort') */
 	/* ->orderBy('user_id', 'DESC') */
 	/* ->fields('zti') */
 	/* ->limit(3); */
 	
 	
 	// Fetch the result set.
 	$result = $select->execute();
 	
 	//dpm($result);
 	
  	foreach ($result as $row) {
 		$stop = 'here';
 		
 		$id = $row->inv_id;
 		$owner = $row->user_id;
 		$hex_owner = __string_to_hex($owner);
 		$len = strlen($hex_owner);
 		
 		$color =  drupal_substr($hex_owner, (0), 6);
 		
 		//dpm($row);
 		$stop = 'here';
 		$rows[] = array(
 				'<div style="width:20px;height:20px;float:left;margin-right:10px;background:#' . $color . '"></div>' . $row->user_id,
 				$row->hostname,
 				__primary_os_long_name($row->primary_os),
 				invdb_primary_os_version_string($id),
 				$row->ip_address,
 				$row->asset_tag,
 				invdb_get_info_file_name_link($id),

 				);//end rows arrar
 		
 	}
 	
 	// Format output.
 	//$output = theme('table', array('header' => $header, 'rows' => $rows)) . theme('pager');
 	
 	$output = theme('table', array('header' => $header,
 			                         'rows' => $rows ));
 	
 	# add the pager
 	$output .= theme('pager');
 	
 	
 	return $output;
 }// end system_inventory_page
 
 
 
 /**
  * private method to get a the hex value from a string
  * @method __string_to_hex($string)
  * @param string $string
  * @return string
  */
 
 function __string_to_hex($string) {
 	$hex='';
 	for ($i=0; $i < strlen($string); $i++){
 	  $hex .= dechex(ord($string[$i]));
 	}
 	return $hex;
 }
 
 
 /**
  * private method to return Linux or Windows based on the input letter
  * @method __primary_os_long_name($os)
  * @param string $os
  * @return string $name
  */
 function __primary_os_long_name($os){
 	$name = 'unknown';
 	if ($os === 'W'){
 		$name = 'Windows';
 	}elseif ($os === 'L'){
 		$name = 'Linux';
 	}
 	
 	return $name;
 }// end __primary_os_long_name
 
 