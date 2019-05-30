<?php
class WebhardDao{
	private $db;
	public function __construct(){
		try{
			$this->db=new PDO("mysql:host=localhost;dbname=phpdb","php","1234");
			$this->db->setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_EXCEPTION);
		}catch(PDOException $e){
			exit($e->getMessage());
		}
	}
	
	public function getFileList($sort,$dir){
		try{
			$query=$this->db->prepare("select * from webhard order by $sort $dir");
			$query->execute();
			$result=$query->fetchAll(PDO::FETCH_ASSOC);
		}catch(PDOException $e){
			exit($e->getMessage());
		}
		return $result;
	}
	public function addFileInfo($fname, $ftime, $fsize){
		try{
			$sql="insert into webhard(fname,ftime,fsize)values(:fname,:ftime,:fsize)";
			$query=$this->db->prepare($sql);
			
			$query->bindValue(":fname",$fname,PDO::PARAM_STR);
			$query->bindValue(":ftime",$ftime,PDO::PARAM_STR);
			$query->bindValue(":fsize",$fsize,PDO::PARAM_INT);
			$query->execute();
		}catch(PDOExeption $e){
			exit($e->getMessage());
		}
	}
	
	public function deleteFileInfo($num){
		try{
			$query=$this->db->prepare("select fname from webhard where num=:num");
			$query->bindValue(":num",$num,PDO::PARAM_INT);
			$query->execute();
			
			$result=$query->fetchColumn();
			
			$query=$this->db->prepare("delete from webhard where num=:num");
			$query->bindValue(":num",$num,PDO::PARAM_INT);
			$query->execute();
		}catch(PDOException $e){
			exit($e->getMessage());
		}
		return $result;
	}
	public function getFileSize($fname){
      try{
         $query=$this->db->prepare("select fsize from webhard where fname=:fname");
         $query->bindValue(":fname",$fname,PDO::PARAM_STR);
         $query->execute();
         $result=$query->fetchColumn();
      }catch(PDOException $e){
         exit($e->getMessage());
      }
      return $result;
   }
}
?>