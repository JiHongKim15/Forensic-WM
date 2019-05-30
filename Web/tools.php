<?php
	define("MAIN_PAGE", "main.php");
	define("BOARD", "board.php");
	define("MEMBER_PATH", ".");
	
	function session_start_if_none(){
		if(session_status() == PHP_SESSION_NONE)
			session_start();
	}
	
	function requestValue($name){
		return isset($_REQUEST[$name]) ? $_REQUEST[$name] : "";
	}
	
	function sessionVar($name){
		return isset($_SESSION[$name]) ? $_SESSION[$name] : "";
	}
	
	function goNow($url){
		header("Location: $url");
		exit();
	}
	
	function errorBack($msg){
?>
		<!doctype html>
		<html>
		<head>
			<meta charset = "utf-8">
		</head>
		<body>
		
		<script>
			alert('<?=$msg ?>');
			history.back();
		</script>
		
		</body>
		</html>
<?php
			exit();
	}
	
	function okGo($msg, $url) {
?>
		<!doctype html>
		<html>
		<head>
			<meta charset="utf-8">
		</head>
		<body>
		
		<script>
			alert('<?= $msg ?>');
			location.href='<?= $url ?>';
		</script>
		
		</body>
		</html>
<?php
			exit();
	}
?>

<?php
	function bdUrl($file, $num, $page) {
		$join = "?";
		if ($num){
			$file .= $join . "num=$num";
			$join = "&";
		}
		if($page)
			$file .= $join . "page=$page";
		
		return $file;
	}
?>
