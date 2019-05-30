<?php
class iKeyDao {
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
	public function getiKey($_iKey){
		try{
			$query = $this -> db -> prepare("select * from iKey where _iKey = :_iKey");
			$query->bindValue(":_iKey", $_iKey, PDO::PARAM_STR);
			$query->execute();
			
			$result = $query->fetch(PDO::FETCH_ASSOC);
		}
		catch(PDOException $e){
			exit($e->getMessage());
		}
		
		return $result;
	}
	
	//추가
	public function insertiKey($_iKey, $_id, $_ip, $_posx, $_posy, $_time, $_fname){
		try{
			$query = $this->db->prepare("insert into iKey values(:_iKey,:_id, :_ip, :_posx, :_posy, :_time, :_fname)");
			$query->bindValue(":_iKey", $_iKey, PDO::PARAM_STR);
			$query->bindValue(":_id", $_id, PDO::PARAM_STR);
			$query->bindValue(":_ip", $_ip, PDO::PARAM_STR);
			$query->bindValue(":_posx", $_posx, PDO::PARAM_STR);
			$query->bindValue(":_posy", $_posy, PDO::PARAM_STR);
			$query->bindValue(":_time", $_time, PDO::PARAM_STR);
			$query->bindValue(":_fname", $_fname, PDO::PARAM_STR);
			$query->execute();
		}
		catch(PDOException $e){
			exit($e->getMessage());
		}
	}
	
	//업데이트
	public function updateiKey($_iKey, $_id, $_ip, $_posx,$_posy, $_time){
		try{
			$query = $this->db->prepare("update iKey set _id=:_id, _ip=:_ip, _posx=:_posx, _posy=:_posy, _time=:_time where _iKey=:_iKey");
			$query->bindValue(":_iKey", $_iKey, PDO::PARAM_STR);
			$query->bindValue(":_id", $_id, PDO::PARAM_STR);
			$query->bindValue(":_ip", $_ip, PDO::PARAM_STR);
			$query->bindValue(":_posx", $_posx, PDO::PARAM_STR);
			$query->bindValue(":_posy", $_posy, PDO::PARAM_STR);
			$query->bindValue(":_time", $_time, PDO::PARAM_STR);
		}
		catch(PDOException $e){
			exit($e->getMessage());
		}
	}
}