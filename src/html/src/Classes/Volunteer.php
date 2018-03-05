<?php

require "User.php";

class Volunteer extends User
{	
	
	function __construct()
	{
		$this->table = "volunteer";
		parent::__CONSTRUCT();
	}

	public function insert($email, $password, $name)
	{
	        $stmt = $this->conn->pdo->prepare("select * from $this->table where email = :email");
	        $stmt->bindValue(':email', $email); // Evitar injection
		$exec = $stmt->execute();
		$result = $stmt->fetchObject();
		if($result) // já cadastrado
			return false; 
	
		$hash = password_hash($password, PASSWORD_DEFAULT); // Criptografando a senha	
	        $stmt = $this->conn->pdo->prepare("INSERT INTO volunteer(email, password, name) VALUES ( :email, :password, :name)");
		$stmt->bindValue(':email', $email);
		$stmt->bindValue(':password', $hash);
		$stmt->bindValue(':name', $name);
		$exec = $stmt->execute();
		if($exec)
			return true;
		return false;
	}

	public function update($id, $nome,$email, $password)
	{
	}
}
