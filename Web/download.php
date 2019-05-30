
<?php
	$_value=$_GET['value'];
    require_once("tools.php");
    require_once("iKeyDao.php");
    session_start_if_none();
   
    $_id = sessionVar("uid");

    $_ip = $_SERVER['REMOTE_ADDR'];
   
 
    $_posx = $_GET['posx'];
    $_posy = $_GET['posy'];
    $_time = date("Y-m-d H:i:s");
    
    $_t = date("His");


   
?>

 <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
   <head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
      
   </head>
   <body>
   
    <img src="files/<?=$_value?>" width="500" height="500" align="center"style="margin-top:50px;margin-left: auto; margin-right: auto; display: block;"><br>
	<form method="post" action="WMexe.php?value=<?=$_value?>&posx=<?=$_posx?>&posy=<?=$_posy?>" enctype="multipart/form-data">
	<input type="image" name="submit" src="download.PNG" style="width:200px; height:70px; align:center;margin-left: 850px;">
   </form>
   
   
   
   

   </body>
</html>