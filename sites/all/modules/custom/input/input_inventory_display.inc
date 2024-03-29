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
 				invdb_get_hostname_link($user->name, $row->hostname),
 				__primary_os_long_name($row->primary_os,$id),
 				//invdb_primary_os_version_string($id),
 				__primary_os_version_string($id),
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
  * new we will also make this a link to the os page 
  * @method __primary_os_long_name($os)
  * @param string $os
  * @return string $name
  */
 function __primary_os_long_name($os,$zz_team_inv_inv_id){
 	$name = 'unknown';
 	if ($os === 'W'){
 		$name = 'Windows';
 	}elseif ($os === 'L'){
 		$name = 'Linux';
 	}
 	$stop = 'here';
 	$vstr = invdb_primary_os_version_string($zz_team_inv_inv_id);
 	if ($vstr == 'NotFound'){
 		$stop = 'here';
 		$os = "<font color='#FF0000'>$vstr</font>";
 		$link = $name;
 	}else {
 		$server_name = $_SERVER['HTTP_HOST'];
 		$base_link = 'http://'.$server_name.'/inventory/system/input_secondary_os_data?invid='.$zz_team_inv_inv_id;
 		$link = "<a href=$base_link> $name </a>";
 	}

 	
 	
 	
 	
 	return $link;
 }// end __primary_os_long_name
 
 //---------------------------------------------------------------------------
 /**
  * this method will style the OS Version. if NotFound is returned then make it red
  * @method __primary_os_version_string($id)
  * @param int $id  the id of the computer to check
  * @return string $styled_link
  * 
  */
 //---------------------------------------------------------------------------
 function __primary_os_version_string($id){
 	
 	$stop = 'here';
 	$vstr = invdb_primary_os_version_string($id);
 	$os = $vstr;
 	if ($vstr == 'NotFound'){
 		$stop = 'here';
 		$os = "<font color='#FF0000'>$vstr</font>";
 	}
 	
 	return $os;
 }//end __primary_os_version_string($id)
 //---------------------------------------------------------------------------
 