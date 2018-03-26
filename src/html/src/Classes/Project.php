<?php
require "Classes/Connect.php";

class Project
{
	private $conn;

	function __construct()
	{
		$this->conn = new Connect();
	}

	function insert($id, $desc, $path)
	{
		$stmt = $conn->pdo->prepare("INSERT INTO project(descr, path, admin) VALUES (:descr, :path, :admin)"); 
		$stmt->bindValue(':path', $path); // Evitar injection
		$stmt->bindValue(':descr', $desc);
		$stmt->bindValue(':admin', $id);
		$stmt->execute();
		$exec = $stmt->rowCount();
		if($exec)
		{
			return true;
		} 
		return false;	
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
			$stmt = $this->conn->pdo->prepare("SELECT descr FROM project WHERE id = :proj"); 
			$stmt->bindValue(':proj', $j); 
			$stmt->execute();
			$row = $stmt->rowCount();
			if($row > 0)
			{
				$result = $stmt->fetchAll();
				$resp[$i]['desc'] = $result[0]['descr'];
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

	function listar($id)
	{
			$stmt = $conn->pdo->prepare("SELECT descr,  FROM project where admin = :id"); 
			$stmt->bindValue(':id', $_SESSION['adminID']); // Evitar injection
			$stmt->execute();
			$row = $stmt->rowCount();
			if($row > 0)
			{
				$result = $stmt->fetchAll();
				$result = json_encode($result);
				echo $result;
			} 

	}
}
