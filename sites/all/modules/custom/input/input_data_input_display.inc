<?php

/**
 * @filesource 
 * this page will display the data that the user just input
 * the database
 */

/**
 * display the data just entered into the database
 * @method data_input_page($hostname)
 * @param string  $hostname
 * 
 */
function data_input_page(){
	$stop ='here';
	
	if (isset($_GET['data'])){
		$g = $_GET['data'];
		$ar = explode("-",$g);
		
	}
		
	$inv_id = $ar[0];
	$header = array(
			array('data' => 'User Id', ),
			array('data' => 'Cube Id', ),
			array('data' => 'Fixed Asset Tag', ),
			array('data' => 'Serial Number', ),
			array('data' => 'Host Name', ),
			array('data' => 'Ipaddress', ),
			array('data' => 'Primary OS',  ),
			array('data' => 'System Type', ),
			array('data' => 'Project', ),
			array('data' => 'Usage', ),
			array('data' => 'Service Date', ),
	);
	
	
	$select = db_select('zz_team_inv', 'zti')
	->condition('zti.inv_id',$inv_id)
	->fields('zti', array('inv_id','user_id','asset_tag','serial_num','cub_id','hostname',
			               'ip_address','machine_type','machine_user','machine_task','primary_os',
			                'service_date_eop','service_date_str',))
	;
	
	
	// Fetch the result set.
	$result = $select->execute();
	
	//dpm($result);
	
	foreach ($result as $row) {
	
		$rows[] = array(
				$row->user_id,
				$row->cub_id,
				$row->asset_tag,
                $row->serial_num,
				invdb_get_hostname_link($row->user_id, $row->hostname),
				$row->ip_address,
				__get_primary_os($row->primary_os),
				__get_machine_type($row->machine_type),
				__get_project_type($row->machine_user),
				__get_machine_task($row->machine_task),
				$row->service_date_str,
		);//end rows arrar
		
		//$rows[] = array('#markup' => '<p>' . t('Simple page: The quick brown fox jumps over the lazy dog.') . '</p>');
	}
	$output = theme('table', array('header' => $header,
			                         'rows' => $rows,)
			        );
	$k = ('<p>' . t('Simple page: The quick brown fox jumps over the lazy dog.') . '</p>');
	
	//append the k message to the output
	$output .= $k;
	
	
	
	
	return  $output;
}// end data_input_page
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
/**
 * display the OS idenifaction data that was entered to the data base
 * @method data_os_input_display($hostname)
 * @param string $hostname
 * @return html $output
 */
//-----------------------------------------------------------------------------------------
function data_os_input_page(){
	
	$stop = 'here';
	
	if (isset($_GET['data'])){
		$g = $_GET['data'];
		$ar = explode("-",$g);
	
	}
	
	
	$inv_id = $ar[0];
	$header = array(
			array('data' => 'User Id', ),
			array('data' => 'Host Name', ),
			array('data' => 'Primary OS',  ),
			array('data' => 'Secondary OS Num'),
			array('data' => 'OS Version'),
			
	);
	
	
	//$select = db_select('zz_team_inv', 'zti')
	//http://drupal.stackexchange.com/questions/6921/select-fields-from-two-tables-using-db-select
	
	
	$stop = 'here';
	
	$zz_team_inv_inv_id = $_GET['data'];
	$query = db_select('zz_team_inv', 'ti');
	$query->join('zz_system_os', 'os', 'ti.inv_id = os.zz_team_inv_inv_id'); //JOIN node with users
	$result = $query
	->fields('ti', array('user_id', 'hostname'))
	->fields('os', array('sos_type', 'sos_name','sos_version'))
	->condition('zz_team_inv_inv_id', $zz_team_inv_inv_id,'=')
	->condition('sos_type', 'P','=')
	->execute();
	
	$sec_os_results = db_select('zz_system_os', 'os')
	->fields('os',array('sos_type'))
	->condition('zz_team_inv_inv_id', $zz_team_inv_inv_id,'=')
	->condition('sos_type', 'S','=')
	->execute();
	$num_s_os = $sec_os_results->rowCount();
	
	$sec_os_link = __create_secd_os_link($zz_team_inv_inv_id, $num_s_os);
	
	foreach ($result as $row) {
		$stop = 'here';
		$rows[] = array(
				$row->user_id,
				$row->hostname,
				$row->sos_name,
				$sec_os_link,
				$row->sos_version,
				);
		
	};//end foreach
	
	
	
	$output = theme('table', array('header' => $header,
			'rows' => $rows,)
	);
	
	$k = ('<p>' . t('Simple page: The quick brown fox jumps over the lazy dog.') . '</p>');
	
	return $output;
}//end data_os_input_display(
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
/**
 * this method will display the data for the secondary os for a given system
 * @method data_secd_os_input_display()
 */
//-----------------------------------------------------------------------------------------
function data_secd_os_input_page(){
	//data_secd_os_input_page
	$stop ='here';
	
	$zz_team_inv_inv_id = $_GET['invid'];
	
	$os_info = invdb_get_sec_os_data($zz_team_inv_inv_id);
	
	$header = array(
			array('data' => 'ID'),
			array('data' => 'User Id', ),
			array('data' => 'Host Name', ),
			array('data' => 'OS Name',  ),
			array('data' => 'OS Version'),
			array('data' => 'OS Type'),
				
	);
	
		
	$output = theme('table', array('header' => $header,
			'rows' => $os_info,)
	);
	
	$k = ('<p>' . t('Simple page: The quick brown fox jumps over the lazy dog zippy do.') . '</p>');
	return $output;
}//end data_secd_os_input_display()
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
/**
 * return the type of task the machine is used for
 * @method __get_machine_task($machine_task)
 * @param char $machine_task
 * @return string $tasked
 */
//-----------------------------------------------------------------------------------------
function __get_machine_task($machine_task){
	if ($machine_task === 'S'){
		$tasked = 'Support';
	}elseif ($machine_task === 'D'){
		$tasked = 'Development';
	}elseif ($machine_task === 'B'){
		$tasked = 'Business Analyst';
	}elseif ($machine_task === 'O'){
		$tasked = 'Other';
	}else{
		$tasked = 'No Sure';
	}
	
	return $tasked;
}//__get_machine_task
//-----------------------------------------------------------------------------------------
/**
 * return the type of project the machine is used for
 * @method __get_project_type($machine_user)
 * @param string $machine_user
 * @return string $project
 */
//-----------------------------------------------------------------------------------------
function __get_project_type($machine_user){
	
	if ($machine_user ==='J'){
		$project = 'JobZone';
	}elseif ($machine_user ==='O'){
		$project = 'Aosos';
	}elseif ($machine_user ==='B'){
		$project = 'JobZone & Aosos';
	}else{
		$project = 'Not Known';
	}
	
	return $project;
}//__get_project_type
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
/**
 * return name for the primary os for the system
 * @method __get_primary_os($primary_os)
 * @param char $primary_os
 * @return string $os_name
 */
//-----------------------------------------------------------------------------------------
function __get_primary_os($primary_os){
	
	if ($primary_os === 'L'){
		$os_name = 'Linux';
	}elseif ($primary_os === 'W'){
		$os_name = 'Windows';
	}elseif ($primary_os === 'S'){
		$os_name = 'Solaris';
	}else{
		$os_name = 'Unknown';
	}
	
	return $os_name;
}//end __get_primary_os
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
/**
 * method to return whether the system is desktop or laptop
 * @method __get_machine_type($type_letter)
 * @parm string  $type_letter
 * @return string $machine_type
 */
//------------------------------------------------------------------------------------------
function __get_machine_type($type_letter){
	
	if ($type_letter === 'D'){
		$machine_type = 'Desk Top';
	}elseif ($type_letter === 'L'){
		$machine_type = 'Lap Top';
	}else {
		$machine_type = 'Unknow';
	}
	
	return $machine_type;
}// end __get_machine_type
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
/**
 * this method will create the link to take you to the page that displays the secondary os
 * @method __create_secd_os_link($zz_team_inv_inv_id, $num_sec_os)
 * @param int $zz_team_inv_inv_id  the id of the system with sec os
 * @param int $num_sec_os
 * @return string $link
 */
//------------------------------------------------------------------------------------------
function __create_secd_os_link($zz_team_inv_inv_id, $num_sec_os){
	
	$stop = 'here';
	$server_name = $_SERVER['HTTP_HOST'];
	$base_link = 'http://'.$server_name.'/inventory/system/input_secondary_os_data?invid='.$zz_team_inv_inv_id;
	
	
	$link = "<a href=$base_link> $num_sec_os </a>";
	
	return $link;
}//end __create_secd_os_link($zz_team_inv_inv_id, $num_sec_os){
//------------------------------------------------------------------------------------------
