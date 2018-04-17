-- MySQL dump 10.16  Distrib 10.1.26-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: paralel_net
-- ------------------------------------------------------
-- Server version	10.1.26-MariaDB-0+deb9u1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `admin`
--

DROP TABLE IF EXISTS `admin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `admin` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `email` varchar(40) NOT NULL,
  `password` varchar(512) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `admin`
--

LOCK TABLES `admin` WRITE;
/*!40000 ALTER TABLE `admin` DISABLE KEYS */;
INSERT INTO `admin` VALUES (1,'adriano.jaguarao@gmail.com','$2y$10$ygCtui3rHIttU0FXwCCl7u9fIrC04tjKVY7VML/q4gQyIWVF6cmBW');
/*!40000 ALTER TABLE `admin` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `data`
--

DROP TABLE IF EXISTS `data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `data` (
  `data_key` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `value` varchar(512) NOT NULL,
  `project` int(11) NOT NULL,
  `hash` varchar(128) DEFAULT NULL,
  PRIMARY KEY (`data_key`),
  KEY `project` (`project`),
  CONSTRAINT `data_ibfk_1` FOREIGN KEY (`project`) REFERENCES `project` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=36 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `data`
--

LOCK TABLES `data` WRITE;
/*!40000 ALTER TABLE `data` DISABLE KEYS */;
INSERT INTO `data` VALUES (1,'teste',19,NULL),(2,'teste',19,NULL),(3,'',19,NULL),(4,'teste',19,NULL),(6,'',19,NULL),(7,'',19,NULL),(8,'',19,NULL),(9,'',19,NULL),(10,'',19,NULL),(11,'',19,NULL),(12,'',19,NULL),(13,'',19,NULL),(17,'',19,NULL),(18,'',19,NULL),(19,'testenovo',19,NULL),(20,'',19,NULL),(21,'',19,NULL),(22,'',19,NULL),(24,'',19,NULL),(25,'',19,NULL),(26,'teste',19,NULL),(27,'testee',19,NULL),(28,'testee',19,NULL),(29,'testee',19,NULL),(30,'testando',19,NULL),(31,'test',19,NULL),(32,'test1',19,NULL),(33,'sadw',21,'1231rasd23123'),(34,'saasddw',21,'1231asasd23123'),(35,'saaasdsddw',21,'12a31asasd23123');
/*!40000 ALTER TABLE `data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `processing`
--

DROP TABLE IF EXISTS `processing`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `processing` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `data` bigint(20) unsigned NOT NULL,
  `user` bigint(20) unsigned NOT NULL,
  `dt` date DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `data` (`data`),
  KEY `user` (`user`),
  CONSTRAINT `processing_ibfk_1` FOREIGN KEY (`data`) REFERENCES `data` (`data_key`),
  CONSTRAINT `processing_ibfk_2` FOREIGN KEY (`user`) REFERENCES `volunteer` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `processing`
--

LOCK TABLES `processing` WRITE;
/*!40000 ALTER TABLE `processing` DISABLE KEYS */;
INSERT INTO `processing` VALUES (1,1,1,NULL);
/*!40000 ALTER TABLE `processing` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `project`
--

DROP TABLE IF EXISTS `project`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `project` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `descr` varchar(2048) DEFAULT NULL,
  `path` varchar(512) NOT NULL,
  `admin` int(11) DEFAULT NULL,
  `dt` date DEFAULT NULL,
  `title` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `admin` (`admin`),
  CONSTRAINT `project_ibfk_1` FOREIGN KEY (`admin`) REFERENCES `admin` (`id`) ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=24 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `project`
--

LOCK TABLES `project` WRITE;
/*!40000 ALTER TABLE `project` DISABLE KEYS */;
INSERT INTO `project` VALUES (19,NULL,'/var/www/html/Projetos/INSTALL',1,NULL,'Mapeamento de numero'),(20,NULL,'/var/www/html/Projetos/comparative-analisys-natural(2).pdf',1,NULL,'Simulação'),(21,NULL,'/var/www/html/Projetos/info',1,NULL,'Simulação genoma'),(22,NULL,'/var/www/html/Projetos/exe.odt',1,NULL,'simulação matematica'),(23,NULL,'/var/www/html/Projetos/exe.odt',1,NULL,'simulação teoria dos');
/*!40000 ALTER TABLE `project` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary table structure for view `project_stats`
--

DROP TABLE IF EXISTS `project_stats`;
/*!50001 DROP VIEW IF EXISTS `project_stats`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `project_stats` (
  `descr` tinyint NOT NULL
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `result`
--

DROP TABLE IF EXISTS `result`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `result` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `resp` varchar(512) DEFAULT NULL,
  `user` bigint(20) unsigned DEFAULT NULL,
  `data` bigint(20) unsigned DEFAULT NULL,
  `dt` date DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `user` (`user`),
  KEY `data` (`data`),
  CONSTRAINT `result_ibfk_1` FOREIGN KEY (`user`) REFERENCES `volunteer` (`id`),
  CONSTRAINT `result_ibfk_2` FOREIGN KEY (`data`) REFERENCES `data` (`data_key`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `result`
--

LOCK TABLES `result` WRITE;
/*!40000 ALTER TABLE `result` DISABLE KEYS */;
INSERT INTO `result` VALUES (1,'test',1,2,'2018-03-25'),(2,'21a',1,3,'2018-03-26'),(3,'2sa1a',2,4,'2018-03-26');
/*!40000 ALTER TABLE `result` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `session`
--

DROP TABLE IF EXISTS `session`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `session` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `user` bigint(20) unsigned NOT NULL,
  `hash` varchar(128) NOT NULL,
  `date` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `user` (`user`),
  UNIQUE KEY `hash` (`hash`),
  CONSTRAINT `session_ibfk_1` FOREIGN KEY (`user`) REFERENCES `volunteer` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=42 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `session`
--

LOCK TABLES `session` WRITE;
/*!40000 ALTER TABLE `session` DISABLE KEYS */;
INSERT INTO `session` VALUES (41,1,'ad0779a8-75e6-4535-b5bc-728abb303aae','2018-03-19 17:56:22');
/*!40000 ALTER TABLE `session` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `volunteer`
--

DROP TABLE IF EXISTS `volunteer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `volunteer` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `email` varchar(40) NOT NULL,
  `password` varchar(128) NOT NULL,
  `name` varchar(30) NOT NULL,
  `dt` date DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `volunteer`
--

LOCK TABLES `volunteer` WRITE;
/*!40000 ALTER TABLE `volunteer` DISABLE KEYS */;
INSERT INTO `volunteer` VALUES (1,'adriano.jaguarao@gmail.com','alfa12','ferreira',NULL),(2,'tst@tst.com','teste','tst','2018-03-26'),(3,'adriano.jaguarao@hotmail.com','$2y$10$h40pOtGnAbSRqi6OjogflOcIFqE0T0.y63dFaW50WtXeXCBWhLeJ6','adriano',NULL);
/*!40000 ALTER TABLE `volunteer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Final view structure for view `project_stats`
--

/*!50001 DROP TABLE IF EXISTS `project_stats`*/;
/*!50001 DROP VIEW IF EXISTS `project_stats`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `project_stats` AS select `project`.`descr` AS `descr` from `project` where (`project`.`id` = 19) union select count(`data`.`project`) AS `count(project)` from `data` where (`data`.`project` = 19) union select count(`processing`.`data`) AS `count(data)` from ((`project` join `data` on((`project`.`id` = `data`.`project`))) join `processing` on((`processing`.`data` = `data`.`data_key`))) where (`data`.`project` = 19) union select count(`result`.`data`) AS `count(data)` from ((`project` join `data` on((`project`.`id` = `data`.`project`))) join `result` on((`result`.`data` = `data`.`data_key`))) where (`data`.`project` = 19) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-04-07  9:03:54
