CREATE DATABASE Grupo17$Riego;

USE Grupo17$Riego;


CREATE TABLE Datos (
    id INT PRIMARY KEY AUTO_INCREMENT NOT_NULL,
    temperatura_externa INT,
    temperatura_interna INT,
    humedad_tierra INT,
    porcentaje INT,
    estado BOOLEAN,
    fecha DATETIME
);

/*Consultas utilizadas*/

/* obtener los datos de la tabla */
SELECT * FROM Datos; 

/* Obtener datos entre un rango de fechas */
SELECT * FROM Datos WHERE Fecha BETWEEN fecha1 AND fecha2 /* Valores de fecha1 y fecha 2 son variables*/

/* Insertar datos */
INSERT INTO Datos (temperatura_externa, temperatura_interna, humedad_tierra, porcentaje, estado, fecha) VALUES (%s,%s,%s,%s,%s,%s) /* Los valores de %s son variables */

/* Obtener datos del ultimo riego */
SELECT * FROM Datos WHERE id = (SELECT MAX(id) FROM Datos)