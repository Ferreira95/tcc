<?php
require "Classes/Project.php";

//	session_start();
	$prj = new Project();
	echo json_encode($prj->listarMany(3));
		
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
						insert($_SESSION['adminID'], $_POST['desc'], $path);
					}
				}
			}
		}
		else if(isset($_GET['listMany']))
		{
			echo json_encode($prj->listarMany(5));
		}
	}



