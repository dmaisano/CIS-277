-- MySQL dump 10.13  Distrib 5.7.30, for Linux (x86_64)
--
-- Host: localhost    Database: cs_288_covid
-- ------------------------------------------------------
-- Server version	5.7.30-0ubuntu0.18.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `covid_cases`
--

DROP TABLE IF EXISTS `covid_cases`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `covid_cases` (
  `us_state` varchar(64) NOT NULL,
  `confirmed_cases` int(11) NOT NULL,
  `new_cases` int(11) NOT NULL,
  `confirmed_deaths` int(11) NOT NULL,
  `new_deaths` int(11) NOT NULL,
  PRIMARY KEY (`us_state`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `covid_cases`
--

LOCK TABLES `covid_cases` WRITE;
/*!40000 ALTER TABLE `covid_cases` DISABLE KEYS */;
INSERT INTO `covid_cases` VALUES ('Alabama',8437,0,315,0),('Alaska',371,0,9,0),('Arizona',9305,0,395,0),('Arkansas',3496,0,82,0),('California',58621,2,2376,1),('Colorado',17364,0,903,0),('Connecticut',30621,0,2633,0),('Delaware',5371,0,187,0),('District Of Columbia',5322,0,264,0),('Florida',37439,0,1471,0),('Georgia',29892,0,1295,0),('Hawaii',625,0,17,0),('Idaho',2127,0,65,0),('Illinois',65962,0,2838,0),('Indiana',21033,0,1326,0),('Iowa',10111,0,207,0),('Kansas',5632,0,161,0),('Kentucky',5822,0,275,0),('Louisiana',29996,0,2115,0),('Maine',1226,0,61,0),('Maryland',27117,0,1390,0),('Massachusetts',70271,0,4212,0),('Michigan',44397,0,4179,0),('Minnesota',7851,0,455,0),('Mississippi',8207,0,342,0),('Missouri',8977,0,400,0),('Montana',457,0,16,0),('Nebraska',6438,0,82,0),('Nevada',5594,0,276,0),('New Hampshire',2636,0,92,0),('New Jersey',131705,0,8292,0),('New Mexico',4138,0,162,0),('New York',330139,0,25204,0),('North Carolina',12511,0,470,0),('North Dakota',1266,0,25,0),('Ohio',20971,0,1136,0),('Oklahoma',4127,0,247,0),('Oregon',2839,0,113,0),('Pennsylvania',53907,0,3196,0),('Rhode Island',9933,0,355,0),('South Carolina',6841,0,296,0),('South Dakota',2721,0,24,0),('Tennessee',13690,0,226,0),('Texas',34238,0,960,0),('Utah',5449,0,56,0),('Vermont',907,0,52,0),('Virginia',20256,0,713,0),('Washington',16360,0,870,0),('West Virginia',1242,0,50,0),('Wisconsin',8566,0,353,0),('Wyoming',604,0,7,0);
/*!40000 ALTER TABLE `covid_cases` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_preferences`
--

DROP TABLE IF EXISTS `user_preferences`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_preferences` (
  `ip_addr` varchar(32) NOT NULL,
  `settings` text,
  PRIMARY KEY (`ip_addr`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_preferences`
--

LOCK TABLES `user_preferences` WRITE;
/*!40000 ALTER TABLE `user_preferences` DISABLE KEYS */;
/*!40000 ALTER TABLE `user_preferences` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-05-05 20:56:45
