<?php

	require "Classes/Volunteer.php";
	
	if(isset($_POST['entrar']))
	{
		$data = array("email", "password");
		
		foreach ($data as $value) 
			if(!isset($_POST[$value]))
				return false;
	
		$vol = new Volunteer();
		if($id = $vol->login($_POST['email'], $_POST['password']))
		{
			session_start();
			$_SESSION['volID'] = $id;
			header('Location: /voluntario.html');
		}
	}

	else if(isset($_POST['cadastrar']))
	{
		$data = array("email", "password", "name");
		
		foreach ($data as $value) 
			if(!isset($_POST[$value]))
				return false;
	
		$vol = new Volunteer();
		if($vol->insert($_POST['email'], $_POST['password'], $_POST['name']))
			echo "Cadastrado";
	}

