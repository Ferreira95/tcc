<?php
require "Classes/Connect.php";

	session_start();
	if(isset($_SESSION['adminID']))
	{
		if(isset($_POST['cadastro']))
		{
			if(is_uploaded_file($_FILES['file']['tmp_name'])) 
			{
				$path = "/var/www/html/Projetos/".basename($_FILES['file']['name']);
 				if(move_uploaded_file($_FILES['file']['tmp_name'], $path))
				{
					if( isset($_POST['desc']))
					{
						$conn = new Connect();
						$stmt = $conn->pdo->prepare("INSERT INTO project(descr, path, admin) VALUES (:descr, :path, :admin)"); 
						$stmt->bindValue(':path', $path); // Evitar injection
						$stmt->bindValue(':descr', $_POST['desc']);
						$stmt->bindValue(':admin', $_SESSION['adminID']);
						$stmt->execute();
					}
				}
			}
		}
		else if(isset($_GET['listar']))
		{
			$conn = new Connect();
			$stmt = $conn->pdo->prepare("SELECT * FROM project where admin = :id"); 
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



