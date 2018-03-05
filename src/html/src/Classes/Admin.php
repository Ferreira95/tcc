<?php

require "User.php";
//require "Connect.php";

class Admin extends User
{
	function __construct()
	{
		$this->table = "admin";
		parent::__CONSTRUCT();
	}

	public function insert($email, $password)
	{
	        $stmt = $this->conn->pdo->prepare("select * from $this->table where email = :email");
	        $stmt->bindValue(':email', $email); // Evitar injection
		$exec = $stmt->execute();
		$result = $stmt->fetchObject();
		if($result) // email já cadastrado
			return false;
		
		$hash = password_hash($password, PASSWORD_DEFAULT); // Criptografando a senha	
	        $stmt = $this->conn->pdo->prepare("INSERT INTO admin(email, password) VALUES (:email, :password)");
		$stmt->bindValue(':email', $email);
		$stmt->bindValue(':password', $hash);
		$exec = $stmt->execute();
		if($exec)
			return true;
		return false;
	}

	public function update($id, $email, $password)
	{
	}


}
