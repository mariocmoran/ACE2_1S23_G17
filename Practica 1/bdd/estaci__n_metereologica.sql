-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Feb 15, 2023 at 09:34 PM
-- Server version: 10.4.27-MariaDB
-- PHP Version: 8.2.0

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `estaci__n_metereologica`
--

-- --------------------------------------------------------

--
-- Table structure for table `informacion_metereologica`
--

CREATE TABLE `informacion_metereologica` (
  `id` int(100) NOT NULL,
  `Dia` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `Temperatura_A` int(100) NOT NULL,
  `Humedad_R` int(100) NOT NULL,
  `Humedad_A` int(100) NOT NULL,
  `Velocidad_V` int(100) NOT NULL,
  `Direccion_V` int(100) NOT NULL,
  `Presion_B` int(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `informacion_metereologica`
--

INSERT INTO `informacion_metereologica` (`id`, `Dia`, `Temperatura_A`, `Humedad_R`, `Humedad_A`, `Velocidad_V`, `Direccion_V`, `Presion_B`) VALUES
(100, 'Miercoles', 0, 0, 0, 0, 100, 635),
(101, 'Miercoles', 0, 0, 0, 0, 101, 635),
(102, 'Miercoles', 0, 0, 0, 0, 102, 635),
(103, 'Miercoles', 0, 0, 0, 0, 103, 635),
(104, 'Miercoles', 0, 0, 0, 0, 104, 635),
(105, 'Miercoles', 0, 0, 0, 0, 105, 635),
(106, 'Miercoles', 24, 56, 0, 1, 106, 635),
(107, 'Miercoles', 24, 56, 0, 2, 107, 635),
(108, 'Miercoles', 24, 56, 0, 0, 108, 635),
(109, 'Miercoles', 24, 55, 0, 0, 109, 635),
(110, 'Miercoles', 24, 55, 0, 0, 110, 635),
(111, 'Miercoles', 24, 56, 0, 0, 111, 635),
(112, 'Miercoles', 24, 56, 0, 0, 112, 635),
(113, 'Miercoles', 24, 56, 0, 0, 113, 635),
(114, 'Miercoles', 24, 55, 0, 0, 114, 635),
(115, 'Miercoles', 24, 55, 0, 0, 115, 635),
(116, 'Miercoles', 24, 56, 0, 0, 116, 635),
(117, 'Miercoles', 24, 56, 0, 0, 117, 635),
(118, 'Miercoles', 24, 56, 0, 0, 118, 635),
(119, 'Miercoles', 24, 56, 0, 0, 119, 635),
(120, 'Miercoles', 24, 55, 0, 0, 120, 635),
(121, 'Miercoles', 24, 55, 0, 0, 121, 635),
(122, 'Miercoles', 24, 55, 0, 0, 122, 635),
(123, 'Miercoles', 24, 55, 0, 0, 123, 635),
(124, 'Miercoles', 24, 55, 0, 0, 124, 635),
(125, 'Miercoles', 24, 56, 0, 0, 125, 635),
(126, 'Miercoles', 24, 56, 0, 0, 126, 635),
(127, 'Miercoles', 24, 56, 0, 0, 127, 635),
(128, 'Miercoles', 24, 56, 0, 0, 128, 635),
(129, 'Miercoles', 24, 56, 0, 0, 129, 635),
(130, 'Miercoles', 24, 56, 0, 0, 130, 635),
(131, 'Miercoles', 24, 56, 0, 0, 131, 635),
(132, 'Miercoles', 24, 56, 0, 0, 132, 635),
(133, 'Miercoles', 24, 56, 0, 0, 133, 635),
(134, 'Miercoles', 24, 56, 0, 0, 134, 635),
(135, 'Miercoles', 24, 56, 0, 0, 135, 635),
(136, 'Miercoles', 24, 56, 0, 0, 136, 635),
(137, 'Miercoles', 24, 56, 0, 0, 137, 635),
(138, 'Miercoles', 24, 56, 0, 0, 138, 635),
(139, 'Miercoles', 24, 56, 0, 0, 139, 635),
(140, 'Miercoles', 24, 56, 0, 0, 140, 635),
(141, 'Miercoles', 24, 56, 0, 0, 141, 635),
(142, 'Miercoles', 24, 56, 0, 0, 142, 635),
(143, 'Miercoles', 24, 56, 0, 0, 143, 635),
(144, 'Miercoles', 24, 56, 0, 0, 144, 635),
(145, 'Miercoles', 24, 56, 0, 0, 145, 635),
(146, 'Miercoles', 24, 56, 0, 0, 146, 635),
(147, 'Miercoles', 24, 56, 0, 0, 147, 635),
(148, 'Miercoles', 24, 56, 0, 0, 148, 635),
(149, 'Miercoles', 24, 56, 0, 0, 149, 635),
(150, 'Miercoles', 24, 56, 0, 0, 150, 635),
(151, 'Miercoles', 24, 56, 0, 0, 151, 635),
(152, 'Miercoles', 24, 56, 0, 0, 152, 635),
(153, 'Miercoles', 24, 56, 0, 0, 153, 635),
(154, 'Miercoles', 24, 56, 0, 0, 154, 635),
(155, 'Miercoles', 24, 56, 0, 0, 155, 635),
(156, 'Miercoles', 24, 56, 0, 0, 156, 635),
(157, 'Miercoles', 24, 57, 0, 0, 157, 635),
(158, 'Miercoles', 24, 57, 0, 0, 158, 635),
(159, 'Miercoles', 24, 57, 0, 0, 159, 635),
(160, 'Miercoles', 24, 57, 0, 0, 160, 635),
(161, 'Miercoles', 24, 57, 0, 0, 161, 635),
(162, 'Miercoles', 24, 57, 0, 0, 162, 635),
(163, 'Miercoles', 24, 57, 0, 0, 163, 635),
(164, 'Miercoles', 24, 57, 0, 0, 164, 635),
(165, 'Miercoles', 24, 57, 0, 0, 165, 635),
(166, 'Miercoles', 24, 57, 0, 0, 166, 635),
(167, 'Miercoles', 24, 57, 0, 0, 167, 635),
(168, 'Miercoles', 24, 56, 0, 0, 168, 635),
(169, 'Miercoles', 24, 57, 0, 0, 169, 635),
(170, 'Miercoles', 24, 56, 0, 0, 170, 635),
(171, 'Miercoles', 24, 56, 0, 0, 171, 635),
(172, 'Miercoles', 24, 56, 0, 0, 172, 635),
(173, 'Miercoles', 24, 56, 0, 0, 173, 635),
(174, 'Miercoles', 24, 56, 0, 0, 174, 635),
(175, 'Miercoles', 24, 56, 0, 0, 175, 635),
(176, 'Miercoles', 24, 56, 0, 0, 176, 635),
(177, 'Miercoles', 24, 56, 0, 0, 177, 635),
(178, 'Miercoles', 24, 56, 0, 0, 178, 635),
(179, 'Miercoles', 24, 56, 0, 0, 179, 635);

-- --------------------------------------------------------

--
-- Table structure for table `mediciones`
--

CREATE TABLE `mediciones` (
  `id` int(50) NOT NULL,
  `dia` int(50) NOT NULL,
  `Temperatura_A` double(100,3) NOT NULL,
  `Humedad_R` double(100,3) NOT NULL,
  `Humedad_A` double(100,3) NOT NULL,
  `Punto_R` double(100,3) NOT NULL,
  `Velocidad_V` double(100,3) NOT NULL,
  `Direccion_V` double(100,3) NOT NULL,
  `Presion_B` double(100,3) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `mediciones`
--

INSERT INTO `mediciones` (`id`, `dia`, `Temperatura_A`, `Humedad_R`, `Humedad_A`, `Punto_R`, `Velocidad_V`, `Direccion_V`, `Presion_B`) VALUES
(100, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.469),
(101, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.478),
(102, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.504),
(103, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.501),
(104, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.481),
(105, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.472),
(106, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.494),
(107, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.488),
(108, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.492),
(109, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.483),
(110, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.462),
(111, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.473),
(112, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.466),
(113, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.494),
(114, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.506),
(115, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.485),
(116, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.492),
(117, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.496),
(118, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 1.000, 633.476),
(119, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 3.000, 633.475),
(120, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.451),
(100, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.457),
(101, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.490),
(102, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.480),
(103, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.481),
(104, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.489),
(105, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.516),
(106, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.491),
(107, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.499),
(108, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.495),
(109, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.500),
(110, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.509),
(111, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.479),
(112, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.504),
(113, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.498),
(114, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.490),
(115, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.492),
(116, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.495),
(117, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.498),
(118, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.475),
(119, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.470),
(120, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.466),
(121, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.488),
(122, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.480),
(123, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.475),
(124, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.449),
(125, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.477),
(126, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.456),
(127, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.490),
(100, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.464),
(101, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.466),
(102, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.477),
(103, 1, 25.000, 56.000, 0.013, 15.597, 0.283, 2.000, 633.496),
(104, 1, 25.000, 56.000, 0.013, 15.597, 1.979, 2.000, 633.487),
(105, 1, 25.000, 56.000, 0.013, 15.597, 1.979, 2.000, 633.505),
(106, 1, 25.000, 56.000, 0.013, 15.597, 1.414, 2.000, 633.491),
(107, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.496),
(108, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.480),
(109, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.482),
(110, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.476),
(100, 1, 25.000, 56.000, 0.013, 15.597, 0.000, 2.000, 633.477);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `informacion_metereologica`
--
ALTER TABLE `informacion_metereologica`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `informacion_metereologica`
--
ALTER TABLE `informacion_metereologica`
  MODIFY `id` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=180;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;