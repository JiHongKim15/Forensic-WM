<?php
	require_once("tools.php");
    require_once("iKeyDao.php");
	require("WebhardDao.php");$dao = new WebhardDao();
$fname=$_GET['value'];
 
$file_size = $dao->getFileSize($fname); 

  
error_reporting (E_ALL);

$address = "127.0.0.1";

 
$service_port = 9000;

$socket = socket_create (AF_INET, SOCK_STREAM, 0); 
if($socket < 0) 
{
 echo "\n 해당 소켓 정의에 문제가 발생 하였습니다\n"; 
 exit; 
}
 
$result = socket_connect ($socket, $address, $service_port); 
if($result < 0) 
{
 echo "\n 접속 에러. Error : ".socket_strerror($result)."\n"; 
}


//$buf=$fname."\0";
//보낼 메세지 설정 
//$sw = socket_write($socket,$buf);
//if($sw < 0) { 
//      echo "\n 서버에 메세지 전송에 실패 하였습니다. Error : ".socket_strerror($result)."\n"; 
//      socket_close($socket);  
//      exit; 
//   }




$buf=$file_size."\0";
$sw = socket_write($socket,$buf);
if($sw < 0) { 
      echo "\n 서버에 메세지 전송에 실패 하였습니다. Error : ".socket_strerror($result)."\n"; 
      socket_close($socket);  
      exit; 
   }
$file=fopen("$fname","rb");

$i=0; $fpsize=0; $buf=0;
// Server에 메세지 보내기 오류 체크 
while(1){
   if($file_size-256<=0){
      
	  $buf=fread($file,$file_size);
      
      socket_write($socket,$buf);//send($socket,&$buf,$fpsize,0);
      break;
   }
   $buf=fread($file,256);
   socket_write($socket,$buf);

   $file_size=$file_size-256;
}
fclose($file);

/*
//Server에 메세지 전송
$sw = socket_write($socket,$in,strlen($in));

// Server에 메세지 보내기 오류 체크 
if($sw < 0) 
{ 
  echo "\n 서버에 메세지 전송에 실패 하였습니다. Error : ".socket_strerror($result)."\n"; 
  socket_close($socket);  
  exit; 
}
 */
@socket_close ($socket);


error_reporting (E_ALL);

session_start_if_none();
   
    $_id = sessionVar("uid");

    $_ip = $_SERVER['REMOTE_ADDR'];
   
   

    $_posx = $_GET['posx'];;
    $_posy = $_GET['posy'];;
    $_time = date("Y-m-d H:i:s");
    
    $_t = date("His");


    $_iKey = mt_rand(1,10); //랜덤번호

    for($idx = 0; $idx < strlen($_id); $idx++){
         $_iKey = $_iKey+ord($_id[$idx]);
    }
   
   
   $_iKey = $_iKey + $_t;
   
   $kdao = new iKeyDao();
   
   $kdao->insertiKey($_iKey, $_id, $_ip, $_posx, $_posy, $_time,$fname);
   
$address = "127.0.0.1";

 
$service_port = 9000;

$socket = socket_create (AF_INET, SOCK_STREAM, 0); 
if($socket < 0) 
{
 echo "\n 해당 소켓 정의에 문제가 발생 하였습니다\n"; 
 exit; 
}
 
$result = socket_connect ($socket, $address, $service_port); 
if($result < 0) 
{
 echo "\n 접속 에러. Error : ".socket_strerror($result)."\n"; 
}
//Server에 메세지 전송
//$sw = socket_write($socket,$in,strlen($in));
$sw = socket_write($socket,$_iKey,strlen($_iKey));

// Server에 메세지 보내기 오류 체크 
if($sw < 0) 
{ 
  echo "\n 서버에 메세지 전송에 실패 하였습니다. Error : ".socket_strerror($result)."\n"; 
  socket_close($socket);  
  exit; 
}

@socket_close ($socket);
   
   errorBack("다운로드가 완료되었습니다.");
?>