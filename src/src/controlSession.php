<?php

	if(isset($_SESSION['volID']))
		location("header: perfil.html");
	else if (isset($_SESSION['adminID']))
		location("header: administrador.html");
