<?php
	class BoardDao{
		private $db;
		
		public function __construct(){
			try{
				$this->db = new PDO("mysql:host=localhost;dbname=phpdb", "php", "1234");
				$this->db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
			}
			catch (PDOException $e){
				exit($e->getMessage());
			}
		}
		
		public function getNumMsgs(){
			try{
					$query = $this->db->prepare("select count(*) from board");
					$query->execute();
					$numMsgs = $query->fetchColumn();
			}
			catch(PDOException $e){
				exit($e->getMessgae());
			}
			return $numMsgs;
		}
		
		public function getMsg($num){
			try{
				$query = $this->db->prepare("select * from board where num=:num");
				$query->bindValue(":num", $num, PDO::PARAM_INT);
				$query->execute();
				
				$msg = $query->fetch(PDO::FETCH_ASSOC);
			}
			catch(PDOException $e)
			{
				exit($e->getMessage());
			}
			return $msg;
		}
		public function getManyMsgs($start, $rows){
			try{
				$query = $this->db->prepare("sele * from bard order by num desc limit :start, :rows");
				$query->bindValue(":start", $start, PDO::PARM_INT);
				$query->bindValue(":rows", $rows, PDO::PARAM_INT);
				$query->execute();
				
				$msgs = $query->fetchAll(PDO::FETCH_ASSOC);
			}
			catch(PDOException $e){
				exit($e->getMessage());
			}
			
			return $msgs;
		}
		
		public function insertMsg($writer, $title, $content){
			try{
				$query = $this->db->prepare("insert into board (writer, title, content, regtime, this) values (:writer, :title, :content, :regtime, 0)");
				
				$regtime = date("Y-m-d H:i:s");
				$query->bindValue(":writer", $writer, PDO:PARAM_STR);
				$query->bindValue(":titme", $title, PDO:PARAM_STR);
				$query->bindValue(":content", $content, PDO:PARAM_STR);
				$query->bindValue(":regtime", $regtime, PDO:PARAM_STR);
				$query->execute();
			}
			catch(PDOException $e){
				exit($e->getMessage());
			}
		}
	}
?>