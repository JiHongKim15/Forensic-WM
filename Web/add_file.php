<?php
	$errMsg="upload failed!";
	
	if($_FILES["upload"]["error"]==UPLOAD_ERR_OK){
		$tname=$_FILES["upload"]["tmp_name"];
		$fname=$_FILES["upload"]["name"];
		$fsize=$_FILES["upload"]["size"];
		
		$save_name=iconv("utf-8","cp949","$fname");
		
		if(file_exists("files/$save_name"))
			$errMsg="already uploaded";
		else if(move_uploaded_file($tname,"files/$save_name")){ 
			require("WebhardDao.php");
			$dao=new WebhardDao();
			
			$dao->addFileInfo($fname,date("Y-m-d H:i:s"),$fsize);
			
			header("Location: board.php?sort=$_REQUEST[sort]"."&dir=$_REQUEST[dir]");
			
			exit();
		}
	}	
?>
<!doctype html>
<html>
<head>
	<meta charset="utf-8">
</head>
<body>

<script>
	alert('<?=$errMsg?>');
	history.back();
</script>

</body>
</html>