<?php	

	require "Classes/Admin.php";
	
	if(isset($_POST['entrar']))
	{
		$data = array("email", "password");
	
		foreach ($data as $value) 
			if(!isset($_POST[$value]))
				return false;

		$admin = new Admin();
		if($id = $admin->login($_POST['email'], $_POST['password']))
		{
			session_start();
			$_SESSION['adminID'] = $id;
			header('Location: ../administrador.html');
		}
		else
		{
			return false;
		}
	}

	
	

	
	
