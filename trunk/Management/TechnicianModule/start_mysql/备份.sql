-- MySQL dump 10.11
--
-- Host: localhost    Database: hoteldb
-- ------------------------------------------------------
-- Server version	5.0.96-community-nt

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
-- Table structure for table `buildingset`
--

DROP TABLE IF EXISTS `buildingset`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `buildingset` (
  `BuildingID` int(4) NOT NULL auto_increment,
  `BuildingName` varchar(64) NOT NULL,
  `FloorNum` int(4) NOT NULL,
  `Extender` int(4) unsigned default NULL,
  PRIMARY KEY  (`BuildingID`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `buildingset`
--

LOCK TABLES `buildingset` WRITE;
/*!40000 ALTER TABLE `buildingset` DISABLE KEYS */;
INSERT INTO `buildingset` VALUES (3,'A',0,0),(4,'B',0,0);
/*!40000 ALTER TABLE `buildingset` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `departments`
--

DROP TABLE IF EXISTS `departments`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `departments` (
  `groupsID` int(4) NOT NULL auto_increment,
  `groupsName` varchar(25) NOT NULL,
  `authority` int(8) unsigned NOT NULL,
  PRIMARY KEY  (`groupsID`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `departments`
--

LOCK TABLES `departments` WRITE;
/*!40000 ALTER TABLE `departments` DISABLE KEYS */;
INSERT INTO `departments` VALUES (1,'前台',511),(2,'工程部',511),(3,'管理员',511),(4,'总经理',65535);
/*!40000 ALTER TABLE `departments` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `equipment_air`
--

DROP TABLE IF EXISTS `equipment_air`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `equipment_air` (
  `ID` int(4) NOT NULL auto_increment,
  `cName` varchar(25) NOT NULL,
  `IsDualDirection` tinyint(1) NOT NULL,
  `EquType` tinyint(2) NOT NULL,
  `ExtendValue` tinyint(4) NOT NULL,
  `Shape` varchar(64) NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `equipment_air`
--

LOCK TABLES `equipment_air` WRITE;
/*!40000 ALTER TABLE `equipment_air` DISABLE KEYS */;
/*!40000 ALTER TABLE `equipment_air` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `equipment_light`
--

DROP TABLE IF EXISTS `equipment_light`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `equipment_light` (
  `ID` int(4) NOT NULL auto_increment,
  `cName` varchar(25) NOT NULL,
  `IsDualDirection` tinyint(1) NOT NULL,
  `EquType` tinyint(2) NOT NULL,
  `ExtendValue` tinyint(4) NOT NULL,
  `Shape` varchar(64) NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `equipment_light`
--

LOCK TABLES `equipment_light` WRITE;
/*!40000 ALTER TABLE `equipment_light` DISABLE KEYS */;
/*!40000 ALTER TABLE `equipment_light` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `equipment_powersaveswitch`
--

DROP TABLE IF EXISTS `equipment_powersaveswitch`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `equipment_powersaveswitch` (
  `ID` int(4) NOT NULL auto_increment,
  `cName` varchar(25) NOT NULL,
  `IsDualDirection` tinyint(1) NOT NULL,
  `EquType` tinyint(2) NOT NULL,
  `ExtendValue` tinyint(4) NOT NULL,
  `Shape` varchar(64) NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `equipment_powersaveswitch`
--

LOCK TABLES `equipment_powersaveswitch` WRITE;
/*!40000 ALTER TABLE `equipment_powersaveswitch` DISABLE KEYS */;
/*!40000 ALTER TABLE `equipment_powersaveswitch` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `equipment_switch`
--

DROP TABLE IF EXISTS `equipment_switch`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `equipment_switch` (
  `ID` int(4) NOT NULL auto_increment,
  `cName` varchar(25) NOT NULL,
  `IsDualDirection` tinyint(1) NOT NULL,
  `EquType` tinyint(2) NOT NULL,
  `ExtendValue` tinyint(4) NOT NULL,
  `Shape` varchar(64) NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `equipment_switch`
--

LOCK TABLES `equipment_switch` WRITE;
/*!40000 ALTER TABLE `equipment_switch` DISABLE KEYS */;
/*!40000 ALTER TABLE `equipment_switch` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `rcuinfo`
--

DROP TABLE IF EXISTS `rcuinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `rcuinfo` (
  `ID` int(4) NOT NULL auto_increment,
  `cName` varchar(25) NOT NULL,
  `equipPortNum` int(4) NOT NULL,
  `statePortNum` int(4) NOT NULL,
  `EquipDetail` blob,
  `pStatusDetail` blob,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `rcuinfo`
--

LOCK TABLES `rcuinfo` WRITE;
/*!40000 ALTER TABLE `rcuinfo` DISABLE KEYS */;
INSERT INTO `rcuinfo` VALUES (1,'RCU-1',20,10,'',''),(2,'RCU-2',10,5,'',''),(3,'RCU-3',50,20,'','');
/*!40000 ALTER TABLE `rcuinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `roomset`
--

DROP TABLE IF EXISTS `roomset`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `roomset` (
  `RoomID` int(4) NOT NULL auto_increment,
  `DoorNum` int(4) NOT NULL,
  `FloorNum` int(4) NOT NULL,
  `BuildingID` int(4) NOT NULL,
  `RoomtypeID` int(4) NOT NULL,
  `IPaddress` varchar(25) NOT NULL,
  `PortValue` int(4) unsigned NOT NULL,
  `EquipBlock` blob,
  `StatusBlock` blob,
  PRIMARY KEY  (`RoomID`),
  KEY `BuildingID` (`BuildingID`),
  KEY `RoomtypeID` (`RoomtypeID`),
  CONSTRAINT `roomset_ibfk_1` FOREIGN KEY (`BuildingID`) REFERENCES `buildingset` (`BuildingID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `roomset_ibfk_2` FOREIGN KEY (`RoomtypeID`) REFERENCES `roomtypeset` (`ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `roomset`
--

LOCK TABLES `roomset` WRITE;
/*!40000 ALTER TABLE `roomset` DISABLE KEYS */;
INSERT INTO `roomset` VALUES (10,6,5,3,1,'192.168.1.180',85,'',''),(11,8,5,3,2,'192.168.5.8',85,'',''),(12,1,10,4,1,'192.168.10.1',85,'','');
/*!40000 ALTER TABLE `roomset` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `roomstate_base`
--

DROP TABLE IF EXISTS `roomstate_base`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `roomstate_base` (
  `ID` int(4) NOT NULL auto_increment,
  `TypeName` varchar(32) NOT NULL,
  `IsDualDirection` tinyint(1) NOT NULL,
  `ExtendValue` tinyint(4) NOT NULL,
  `Shape` varchar(64) NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `roomstate_base`
--

LOCK TABLES `roomstate_base` WRITE;
/*!40000 ALTER TABLE `roomstate_base` DISABLE KEYS */;
INSERT INTO `roomstate_base` VALUES (1,'入住',0,0,'ST00.jpg');
/*!40000 ALTER TABLE `roomstate_base` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `roomstate_others`
--

DROP TABLE IF EXISTS `roomstate_others`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `roomstate_others` (
  `ID` int(4) NOT NULL auto_increment,
  `TypeName` varchar(32) NOT NULL,
  `IsDualDirection` tinyint(1) NOT NULL,
  `ExtendValue` tinyint(4) NOT NULL,
  `Shape` varchar(64) NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `roomstate_others`
--

LOCK TABLES `roomstate_others` WRITE;
/*!40000 ALTER TABLE `roomstate_others` DISABLE KEYS */;
/*!40000 ALTER TABLE `roomstate_others` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `roomstate_service`
--

DROP TABLE IF EXISTS `roomstate_service`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `roomstate_service` (
  `ID` int(4) NOT NULL auto_increment,
  `TypeName` varchar(32) NOT NULL,
  `IsDualDirection` tinyint(1) NOT NULL,
  `ExtendValue` tinyint(4) NOT NULL,
  `Shape` varchar(64) NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `roomstate_service`
--

LOCK TABLES `roomstate_service` WRITE;
/*!40000 ALTER TABLE `roomstate_service` DISABLE KEYS */;
/*!40000 ALTER TABLE `roomstate_service` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `roomstate_temp`
--

DROP TABLE IF EXISTS `roomstate_temp`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `roomstate_temp` (
  `ID` int(4) NOT NULL auto_increment,
  `TypeName` varchar(32) NOT NULL,
  `IsDualDirection` tinyint(1) NOT NULL,
  `ExtendValue` tinyint(4) NOT NULL,
  `Shape` varchar(64) NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `roomstate_temp`
--

LOCK TABLES `roomstate_temp` WRITE;
/*!40000 ALTER TABLE `roomstate_temp` DISABLE KEYS */;
INSERT INTO `roomstate_temp` VALUES (1,'打扫',0,0,'ST00.jpg');
/*!40000 ALTER TABLE `roomstate_temp` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `roomtypeset`
--

DROP TABLE IF EXISTS `roomtypeset`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `roomtypeset` (
  `ID` int(4) NOT NULL auto_increment,
  `roomtypeName` varchar(64) NOT NULL,
  `RCUID` int(4) NOT NULL,
  PRIMARY KEY  (`ID`),
  KEY `RCUID` (`RCUID`),
  CONSTRAINT `roomtypeset_ibfk_1` FOREIGN KEY (`RCUID`) REFERENCES `rcuinfo` (`ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `roomtypeset`
--

LOCK TABLES `roomtypeset` WRITE;
/*!40000 ALTER TABLE `roomtypeset` DISABLE KEYS */;
INSERT INTO `roomtypeset` VALUES (1,'大床房',1),(2,'小床房',2);
/*!40000 ALTER TABLE `roomtypeset` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user` (
  `userID` varchar(25) NOT NULL,
  `password` varchar(25) NOT NULL,
  `groupsID` int(4) NOT NULL,
  PRIMARY KEY  (`userID`),
  KEY `groupsID` (`groupsID`),
  CONSTRAINT `user_ibfk_1` FOREIGN KEY (`groupsID`) REFERENCES `departments` (`groupsID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=gbk;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES ('Cico','abc',3),('Johnson','abc',1),('Tina','abc',2);
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-11-14 23:43:42
