<?php

require "Connect.php";

abstract class User
{
	protected $table;
	public $conn = "teste";

	function __construct()
	{
		$this->conn = new Connect();
	}

	public function login($email, $password)
	{
	        $stmt = $this->conn->pdo->prepare("select * from $this->table where email = :email"); 
		$stmt->bindValue(':email', $email); // Evitar injection
		$stmt->execute();
		$row = $stmt->rowCount();
		if($row == 1)
		{
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			if(password_verify($password, $result['password']))
				return $result['id'];
		} 
		return false;	
	}

	public function delete($id)
	{
	        $stmt = $this->conn->pdo->prepare("delete from $this->table where id = :id"); 
		$stmt->bindValue(':id', $id); // Evitar injection
		$stmt->execute();
		$exec = $stmt->rowCount();
		if($exec)
		{
			return true;
		} 
		return false;	
	}

}
