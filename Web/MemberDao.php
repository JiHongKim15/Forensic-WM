<?php
class MemberDao {
	private $db;
	
	//객체 접근
	public function __construct(){
		try{
			$this->db = new PDO("mysql:host=localhost;dbname=phpdb", "php", "1234");
			$this->db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		}
		catch (PDOException $e){
			exit($e->getMessage());
		}
	}
	
	//반환
	public function getMember($id){
		try{
			$query = $this -> db -> prepare("select * from member where id = :id");
			$query->bindValue(":id", $id, PDO::PARAM_STR);
			$query->execute();
			
			$result = $query->fetch(PDO::FETCH_ASSOC);
		}
		catch(PDOException $e){
			exit($e->getMessage());
		}
		
		return $result;
	}
	
	//추가
	public function insertMember($id, $pw, $name){
		try{
			$query = $this->db->prepare("insert into member values(:id, :pw, :name)");
			$query->bindValue(":id", $id, PDO::PARAM_STR);
			$query->bindValue(":pw", $pw, PDO::PARAM_STR);
			$query->bindValue(":name", $name, PDO::PARAM_STR);
			$query->execute();
		}
		catch(PDOException $e){
			exit($e->getMessage());
		}
	}
	
	//업데이트
	public function updateMember($id, $pw, $name){
		try{
			$query = $this->db->prepare("update member set pw=:pw, name=:name where id=:id");
			$query->bindValue(":id", $id, PDO::PARAM_STR);
			$query->bindValue(":pw", $pw, PDO::PARAM_STR);
			$query->bindValue(":name", $name, PDO::PARAM_STR);
		}
		catch(PDOException $e){
			exit($e->getMessage());
		}
	}
}