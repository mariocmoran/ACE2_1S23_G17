/* Creacion de base de datos */
CREATE DATABASE Grupo17$Pomodoro;

USE Grupo17$Pomodoro;

/* Creacion de Tabla */
CREATE TABLE Pomodoro (
	id INT PRIMARY KEY AUTO_INCREMENT,
  Usuario VARCHAR(100),
  Fecha DATETIME,
  Penalizacion_No_P INT,
  Penalizacion_No_S INT,
  Estado TINYINT,
  Tiempo_Trabajo INT,
  Tiempo_Descanso INT,
  No_Pomodoro INT

);

/* Select, Update e Insert utilizados */

/* obtener los datos de la base */
SELECT * FROM Pomodoro; 

/* Obtener datos entre un rango de fechas */
SELECT * FROM Pomodoro WHERE Fecha BETWEEN fecha1 AND fecha2 /* Valores de fecha1 y fecha 2 son variables*/

/* Obtener datos del ultimo pomodoro */
SELECT * FROM Pomodoro WHERE id = (SELECT MAX(id) FROM Pomodoro WHERE Usuario = usuario_global) /* usuario_global es variable */

/* Insertar datos */
INSERT INTO Pomodoro (Usuario, Fecha, Penalizacion_No_P, Penalizacion_No_S, Estado, Tiempo_Descanso, Tiempo_Trabajo, No_Pomodoro) VALUES (%s, NOW(),%s,%s,%s,%s,%s,%s) /* Los valores de %s son variables */

/* Actualizar datos de penalizacion */
UPDATE Pomodoro SET Penalizacion_No_P = Penalizacion_No_P + 1 WHERE id = (SELECT MAX(id) FROM Pomodoro) AND Usuario = usuario_global /* usuario_global es variable  */

UPDATE Pomodoro SET Penalizacion_No_S = Penalizacion_No_S + 1 WHERE id = (SELECT MAX(id) FROM Pomodoro) AND Usuario = usuario_global

/* Actualizar datos de estado */
UPDATE Pomodoro SET Estado = NOT Estado WHERE id = (SELECT MAX(id) FROM Pomodoro) AND Usuario = usuario_global

/* Actualizar datos de tiempo de trabajo y descanso */

UPDATE Pomodoro SET Tiempo_Trabajo = %s WHERE id = (SELECT MAX(id) FROM Pomodoro) AND Usuario = %s /* %s es variable */

UPDATE Pomodoro SET Tiempo_Descanso = %s WHERE id = (SELECT MAX(id) FROM Pomodoro) AND Usuario = %s /* %s es variable */


/* Creacion de procedimiento almacenado */