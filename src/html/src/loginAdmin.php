<?php	

	require "Classes/Admin.php";
	
	$data = array("entrar", "email", "password");
	
	foreach ($data as $value) 
		if(!isset($_POST[$value]))
			return false;

	$admin = new Admin();
	if($id = $admin->login($_POST['email'], $_POST['password']))
	{
		session_start();
		$_SESSION['adminID'] = $id;
		header('Location: /administrador.html');
	}
	else
	{
		header('Location: loginAdmin.html');
	}

	
	

	
	
