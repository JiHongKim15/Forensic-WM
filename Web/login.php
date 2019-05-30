
<?php
	require_once("tools.php");
	require_once("MemberDao.php");
	$id = requestValue("id");
	$pw = requestValue("pw");
	
	$mdao = new MemberDao();
	$member = $mdao->getMember($id);

	if($member && $member["pw"] == $pw) { //member와 member의 pw가 같으면
		session_start_if_none();
		$_SESSION["uid"] = $id;
		$_SESSION["uname"] = $member["name"];
	
	}
	else
		errorBack("아이디 또는 비밀번호가 잘못 입력되었습니다.");
?>

<html xmlns="http://www.w3.org/1999/xhtml">
<body>
<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<style>
		div{
			text-align:center;
			margin-top:250px;
		}</style>
	</head>
	<script ="text/javascript">
		var latitude;
		var longitude;
		init();
		function init(){
			window.navigator.geolocation.getCurrentPosition(current_position);
		}
	
		function current_position(position){
			latitude=position.coords.latitude;
			longitude=position.coords.longitude;
			setTimeout("draw()",1000);
		}
		function draw(){
			window.location.href = "board.php?posx=" + latitude+"&posy="+longitude;
		}
	</script>
	<div>
	<img src='loading.gif' align='center' width='200'height='200'>
	</div>
	</body>
</html>

