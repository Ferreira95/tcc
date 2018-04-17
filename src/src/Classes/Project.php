<?php
require "Classes/Connect.php";

class Project
{
	private $conn;
	private $id;

	function __construct()
	{
		$this->conn = new Connect();
	}

	function checkId($hash)
	{
		try {
			$stmt = $this->conn->pdo->prepare("select id from project where hash = :hash");
			$stmt->bindValue(':hash', $hash);  			
			$stmt->execute();
			$row = $stmt->rowCount();

			if($row <= 0)
				return false;
			
			$result = $stmt->fetchAll();
			$this->id = $result['id'];
		} catch(Exception $e) {
			return false;
		}
	}

	function requestData($id_vol)
	{
		try {
			$stmt = $this->conn->pdo->prepare("select data_key, hash, value from data join project on (project.id = data.project) where project.id = :id and data_key not in (select data from processing) and data_key not in (select data from result) LIMIT 1");
			$stmt->bindValue(':id', $this->id);  			
			$stmt->execute();
			$row = $stmt->rowCount();

			if($row <= 0)
				return false;
			$result = $stmt->fetchAll();
						
			$stmt = $this->conn->pdo->prepare("INSERT INTO processing(data, user, dt) VALUES (:key, :id, now())");
			$stmt->bindValue(':key', $result['data_key']);
			$stmt->bindValue(':id', $id_vol);  			
			$stmt->execute();
			return $result;
			
			  
		} catch (Exception $e) {
  			return false;
		}
	}

	function insertResult($hash, $resp)
	{
			$stmt = $this->conn->pdo->prepare("select data_key from data where hash = :hash LIMIT 1");
			$stmt->bindValue(':id', $this->id);  			
			$stmt->execute();
			$row = $stmt->rowCount();

			if($row <= 0)
				return false;
			$result = $stmt->fetchAll();

			$stmt = $this->conn->pdo->prepare("INSERT INTO result(resp, user,data, dt) VALUES (:resp, :id, :key, now())");
			$stmt->bindValue(':key', $result['data_key']);
			$stmt->bindValue(':id', $id_vol);  			
			$stmt->execute();
			return $result;

	}

	function listarMany($num)
	{
		
		$stmt = $this->conn->pdo->prepare("SELECT distinct id FROM project"); 
		$stmt->execute();
		$row = $stmt->rowCount();
		if($row > 0)
			$ids = $stmt->fetchAll();
		$sort = array_rand($ids, $num);
		for( $i = 0 ; $i<$num; $i++)
		{
			$j = $ids[$sort[$i]]['id'];
			$stmt = $this->conn->pdo->prepare("SELECT title FROM project WHERE id = :proj"); 
			$stmt->bindValue(':proj', $j); 
			$stmt->execute();
			$row = $stmt->rowCount();
			if($row > 0)
			{
				$result = $stmt->fetchAll();
				$resp[$i]['title'] = $result[0]['title'];
			}

			$stmt = $this->conn->pdo->prepare("SELECT count(project) as count FROM data WHERE project = :proj"); 
			$stmt->bindValue(':proj', $j); 
			$stmt->execute();
			$row = $stmt->rowCount();
			if($row > 0)
			{
				$result = $stmt->fetchAll();
				$resp[$i]['data'] = $result[0]['count'];
			}


			$stmt = $this->conn->pdo->prepare("SELECT count(data) as count FROM project JOIN data ON (project.id = project) join processing ON (processing.data = data.data_key) WHERE project = :proj"); 
			$stmt->bindValue(':proj', $j); 
			$stmt->execute();
			$row = $stmt->rowCount();
			if($row > 0)
			{
				$result = $stmt->fetchAll();
				$resp[$i]['processing'] = $result[0]['count'];
			}

			$stmt = $this->conn->pdo->prepare("select count(data) as count from project join data on (project.id = project) join result on (result.data = data.data_key) WHERE project = :proj"); 
			$stmt->bindValue(':proj', $j); 
			$stmt->execute();
			$row = $stmt->rowCount();
			if($row > 0)
			{
				$result = $stmt->fetchAll();
				$resp[$i]['result'] = $result[0]['count'];
			}
		}
		return $resp;
	}

	function listAll()
	{
			try {
				$stmt = $this->conn->pdo->prepare("SELECT id, title  FROM project"); 
				$stmt->execute();
				$row = $stmt->rowCount();
				if($row <= 0)
					return false;
			
				$result = $stmt->fetchAll();
				return $result;
			} catch (Exception $e) {
				return false;
			} 

	}

	function listId($id)
	{
			try {
				$stmt = $this->conn->pdo->prepare("select title, descr, path, count(data_key) as data, count(result.id) as result from project left join data on (data.project = project.id) left join result on (data_key = result.id) where project.id = :id group by project.id;
");
				$stmt->bindValue(':id', $id);  
				$stmt->execute();
				$row = $stmt->rowCount();
				if($row <= 0)
					return false;
			
				$result = $stmt->fetchAll();
				return $result[0];
			} catch (Exception $e) {
				return false;
			} 


	}

	function listAdmin($admin)
	{
			try {
				$stmt = $this->conn->pdo->prepare("SELECT title, descr, path FROM project JOIN admin on (admin.id = project.admin) WHERE admin = :admin");
				$stmt->bindValue(':admin', $admin);  
				$stmt->execute();
				$row = $stmt->rowCount();
				if($row <= 0)
					return false;
			
				$result = $stmt->fetchAll();
				return $result;
			} catch (Exception $e) {
				return false;
			} 


	}

	function listVol($vol)
	{
			try {
				$stmt = $this->conn->pdo->prepare(
					"SELECT title, count(result.id) as contrib, max(result.dt) as last FROM project join data on (data.project = project.id) join result on (result.data = data.data_key) join volunteer on (result.user = volunteer.id) where volunteer.id = :vol group by project.id;");
				$stmt->bindValue(':vol', $vol);  
				$stmt->execute();
				$row = $stmt->rowCount();
				if($row <= 0)
					return "erro";
			
				$result = $stmt->fetchAll();
				return $result;
			} catch (Exception $e) {
				return false;
			} 


	}


}
