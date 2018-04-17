<?php
require "Classes/Project.php";

	session_start();
	$prj = new Project();
	echo $_SESSION['adminID'];
	if(isset($_SESSION['adminID']))
	{echo "ok";
		if(isset($_POST['cadastro']))
		{
			if(is_uploaded_file($_FILES['file']['tmp_name'])) 
			{
				$path = "/var/www/html/Projetos/".basename($_FILES['file']['name']);
				$link = "/Projetos/".basename($_FILES['file']['name']);
 				if(move_uploaded_file($_FILES['file']['tmp_name'], $link))
				{
					if( isset($_POST['desc']))
					{
						insert($_SESSION['adminID'], $_POST['desc'], $path);
					}
				}
			}
		}

		else if(isset($_GET['listAd']))
		{
			echo json_encode($prj->listAdmin($_SESSION['adminID'])); 
		}


	}		

 	else if(isset($_SESSION['volID']))
	{
		if(isset($_GET['listAll']))
			echo json_encode($prj->listAll());
		else if(isset($_GET['listVol']))
			echo json_encode($prj->listVol($_SESSION['volID']));
		else if(isset($_GET['listID']))
			echo json_encode($prj->listId($_GET['listID']));
	}
	
	if(isset($_GET['listMany']))
	{
		echo json_encode($prj->listarMany(5));
	}




