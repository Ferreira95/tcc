<?php
class Connect 
{    
	var $pdo;
	function __construct()
	{
		try
		{
			$this->pdo = new PDO('mysql:host=localhost;dbname=paralel_net', '', '');
			$this->pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		}
		catch (PDOException $e)
		{
			echo $e->getMessage();
			exit(1);
		} 
	}	
}
