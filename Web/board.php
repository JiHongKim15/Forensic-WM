
<?php
   require_once("tools.php");
   require_once("iKeyDao.php");
   require("WebhardDao.php");
	$dao=new WebhardDao();
	
	$sort=isset($_REQUEST["sort"])?$_REQUEST["sort"]:"fname";
	$dir=isset($_REQUEST["dir"])?$_REQUEST["dir"]:"asc";
	
	$result=$dao->getFileList($sort,$dir);
   session_start_if_none();
   
   $_id = sessionVar("uid");   

   $_ip = $_SERVER['REMOTE_ADDR'];
   
   $_posx = $_GET['posx'];
   $_posy = $_GET['posy'];
   $_time = date("Y-m-d H:i:s");
   $i=1;
   $pathDir="files";
   if(!is_dir($pathDir))mkdir($pathDir);
?> 



<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
   <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
      
	  <style>
      #div_root{
         margin:auto;
         width:auto;
      }
      #div_before{
         width:100%;
         height:20px;
      }
      #div_top{
         width:100%;
         height:150px;
         margin-left:30px;
      }
      #div_text{
         width:15%;
         height:60px;
         float:left;
         text-align:left;
		 color:#414141;
         background-color:#FFFFFF;
      }
      #div_forText{
         width:85%;
         height:60px;
         float:right;
         text-align:center
      }
      #div_menu{
         width:3.3%;
         height:500px;
         float:left;
         text-align:center
      }
      #div_body{
         width:96.7%;
         height:500px;
         float:right;
      }
      
      table{
         width:81.5%;
         border:2px solid #888888;
		 border-collapse: separate;
		border-spacing: 10px 10px;
      }
      </style>
   </head>
   
   
   <body>
      <div id="div_root">
      <div id="div_before"></div>
      <div id="div_top">
         <canvas id="myCanvas" width="1210" height="150" style="border:0"position="relative">
      </canvas>
      <script ="text/javascript">
         var ctx=document.getElementById("myCanvas");
         var myContext=ctx.getContext("2d");
         var text="Information";
         myContext.font="30px comic sans ms"
         myContext.fillText(text,40,30);
         myContext.moveTo(35,20);
         myContext.lineTo(20,20);
         myContext.lineTo(20,100);
         myContext.lineTo(1210,100);
         myContext.lineTo(1210,20);
         myContext.lineTo(220,20);
         myContext.stroke();
		
         text="ID: "
         myContext.font="15px Courier"
         myContext.fillText(text,50,70);
         var id='<?php echo $_id;?>';
         myContext.fillText(id,80,70);
         text="IP: "
         myContext.fillText(text,140,70);
         var ip='<?php echo $_ip;?>';
         myContext.fillText(ip,170,70);
         text="LATITUDE: "
         myContext.fillText(text,270,70);
         var posx='<?php echo $_posx;?>';
         myContext.fillText(posx,355,70);
         text="LONGITUDE:  "
         myContext.fillText(text,530,70);
         var posy='<?php echo $_posy;?>';
         myContext.fillText(posy,625,70);
         text="TIME: "
         myContext.fillText(text,810,70);
         var time='<?php echo $_time;?>';
         myContext.fillText(time,860,70);

      </script>
      </div>
      <div id="div_text">
		<p style="font-family:comic sans ms; font-size: 36px; margin: 0;padding-left: 70px;padding-bottom:0px">Board</p>
      </div>
	  
      <div id="div_forText">
		<form action="add_file.php?sort=<?=$sort?>&dir=<?=$dir?>&posx=<?=$_posx?>&posy=<?=$_posy?>"
			enctype="multipart/form-data"method="post">
			파일 선택
			<input type="file" name="upload">
			<input type="submit" value="업로드">
	</div>
      <div id="div_menu"></div>
      <div id="div_body">
	  <table>
	  <tr>
      <?php foreach($result as $row): ?>
		<td><a href="download.php?value=<?=$row["fname"]?>&posx=<?=$_posx?>&posy=<?=$_posy?>">
		<img src='files/<?=$row["fname"]?>' border='0' width='250'height='210'></a></td>
		<td><a href="del_file.php?num=<?=$row["num"]?>&sort=<?=$sort ?>&dir=<?=$dir?>">X</td>
		<?php
			if($i%4==0&&$i!=0){
				echo"</tr>";
				echo"<tr>";
			}
			$i++;
		?>
		<?php endforeach ?></tr></table>
      </div>
</form>
   </body>
</html>