from flask import Flask, jsonify,request
from flask_mysqldb import MySQL
from conexion_base import config
from flask_cors import CORS,cross_origin

#import serial,time


#arduino= serial.Serial("COM3",9600)
#time.sleep(2)
#
#String = arduino.readline()
#print(String)
#

#
#arduino.close()


app= Flask(__name__)
CORS(app)
conexion=MySQL(app)

##======================Lee la informacion de Todos===============
@cross_origin
@app.route("/Datos",methods=["GET"])
def Info_datos():
    try:
        cursor = conexion.connection.cursor()
        sql= "SELECT id, dia, Temperatura_A, Humedad_R, Humedad_A, Punto_R, Velocidad_V, Direccion_V, Presion_B FROM mediciones"
        cursor.execute(sql)
        datos = cursor.fetchall()
        print(datos)
        Info_al=[]
        for fila in datos:
            Datos_E={"id":fila[0],"dia":fila[1],"Temperatura_A":fila[2],"Humedad_R":fila[3],"Humedad_A":fila[4],"Punto_R":fila[5],"Velocidad_V":fila[6],"Direccion_V":fila[7],"Presion_B":fila[8]}
            Info_al.append(Datos_E)
        return jsonify(Info_al)

    except Exception as ex:
       return jsonify({"mensaje": "Error"})
##==============================Ingresa Los Datos==========================
@app.route('/Datos', methods=['POST'])
def ingresar_info():
    # print(request.json)
    try:
        cursor = conexion.connection.cursor()
        sql = """INSERT INTO mediciones (id, dia, Temperatura_A, Humedad_R, Humedad_A, Punto_R, Velocidad_V, Direccion_V, Presion_B) 
            VALUES ({0},{1},{2},{3},{4},{5},{6},{7},{8})""".format(
                request.json['id'],
                request.json["dia"],
                request.json["Temperatura_A"],
                request.json["Humedad_R"],
                request.json["Humedad_A"],
                request.json["Punto_R"],
                request.json["Velocidad_V"],
                request.json["Direccion_V"],
                request.json["Presion_B"])
        cursor.execute(sql)
        conexion.connection.commit()  # Confirma la acción de inserción.
        return jsonify({'mensaje': "Curso registrado."})
    except Exception as ex:
        print(ex)
        return jsonify({'mensaje': "Error"})

##======================Borrar Informacion ============================
@app.route("/Datos/<id>",methods=["DELETE"])    
def eliminar(id):
    try:
          cursor = conexion.connection.cursor()
          sql = "DELETE FROM mediciones WHERE id= '{0}'".format(id)
          cursor.execute(sql)
          conexion.connection.commit()  # Confirma la acción de inserción.
          return jsonify({"Mensaje":"Informacion Eliminado"})


    except Exception as ex:
        return jsonify({"Mensaje":"Error al eliminar"})
    
#Actualizar Datos
@app.route("/Datos/<id>",methods=["PUT"])    
def Actualizar(id):
    # print(request.json)


        try:
                cursor = conexion.connection.cursor()
                sql = """UPDATE mediciones SET Dia= '{0}', Temperatura_A= '{1}', Humedad_R= '{2}', Humedad_A= '{3}', Velocidad_V= '{4}', Direccion_V= '{5}', Presion_B={6} 
                WHERE id = '{7}'""".format(request.json["Dia"],request.json["Temperatura_A"],request.json["Humedad_R"],request.json["Humedad_A"],request.json["Velocidad_V"],
                request.json["Direccion_V"],request.json["Presion_B"],id) 
                cursor.execute(sql)
                conexion.connection.commit()  # Confirma la acción de actualización.
                return jsonify({'mensaje': "Curso actualizado."})
            
        except Exception as ex:
            return jsonify({'mensaje': "Error"})


#Obtener el Ultimo dato ALmacenado en la base de Datos
@app.route("/UltimoDato",methods=["GET"])
def Ultimos_datos():
    try:
        cursor = conexion.connection.cursor()
        sql='SELECT * FROM mediciones ORDER BY id DESC LIMIT 1'
        #sql= "SELECT id, Dia, Temperatura_A, Humedad_R, Humedad_A, Velocidad_V, Direccion_V, Presion_B FROM informacion_metereologica"
        cursor.execute(sql)
        datos = cursor.fetchone()
        
        
        if datos !=0:
          Datos_E={"id":datos[0],"Dia":datos[1],"Temperatura_A":datos[2],"Humedad_R":datos[3],"Humedad_A":datos[4],"Velocidad_V":datos[5],"Direccion_V":datos[6],"Presion_B":datos[7]}
          return jsonify(Datos_E)
        else:
            return jsonify({"Mensaje": "Curso Encontrado","Hola":"Error"})

    except Exception as ex:
       return jsonify({"mensaje": "Error"})


def pagina_no_encontrada(error):
    return "<h1>Página no encontrada</h1>", 404

if __name__=='__main__':
    app.config.from_object(config["development"])  
    app.register_error_handler(404, pagina_no_encontrada)  
    app.run()