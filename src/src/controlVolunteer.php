<?php

	require "Classes/Volunteer.php";
	
	$vol = new Volunteer();
	if(isset($_POST['entrar']))
	{
		$data = array("email", "password");
		
		foreach ($data as $value) 
			if(!isset($_POST[$value]))
				return false;
		
		if($id = $vol->login($_POST['email'], $_POST['password']))
		{
			session_start();
			$_SESSION['volID'] = $id;
			header('Location: ../perfil.html');
			return;
		}
		header('Location: /tcc 1/index.html');
	}

	else if(isset($_POST['cadastrar']))
	{
		$data = array("email", "password", "name");
		
		foreach ($data as $value) 
			if(!isset($_POST[$value]))
				return false;
	
		if($vol->insert($_POST['email'], $_POST['password'], $_POST['name']))
			header('Location: ../index.html');
		header('Location: ../cadVol.html');
	}

	else if(isset($_GET['sair']))
	{
		session_destroy();
		header('Location: ../index.html');
	}

	else if(isset($_GET['list']))
	{
		echo json_encode($vol->listMany());	
	}
