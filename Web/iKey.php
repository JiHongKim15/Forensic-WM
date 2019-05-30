
<?php
	require_once("tools.php");
	require_once("iKeyDao.php");
	
	session_start_if_none();
	$_id = sessionVar("uid");	
	
	$_iKey = mt_rand(1,10); //랜덤번호

	for($idx = 0; $idx < strlen($_id); $idx++){
        $_iKey = $_iKey+ord($_id[$idx]);
	}
	$_iKey = $_iKey."1";

	$_ip = $_SERVER['REMOTE_ADDR'];
	
		
	$_posx = 1
	$_posy = 2
	$_time = date("Y-m-d H:i:s");
	
	$kdao = new iKeyDao();
	
	kdao->insertiKey($_iKey, $_id, $_ip, $_posx, $_posy, $_time);
?>