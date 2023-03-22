from flask import Flask, jsonify,request
from flask_mysqldb import MySQL
from flask_cors import CORS,cross_origin




usuario_global = ""

app = Flask(__name__)
app.config["DEBUG"] = True
app.config['MYSQL_HOST'] = 'Grupo17.mysql.pythonanywhere-services.com'
app.config['MYSQL_USER'] = 'Grupo17'
app.config['MYSQL_PASSWORD'] = '12345678abc'
app.config['MYSQL_DB'] = 'Grupo17$Pomodoro'
conexion = MySQL(app)



#@cross_origin
# obtener dator por rango de fecha y hora, esta es para las graficas
@app.route("/data",methods=["GET"])
def Info_datos():
    try:
        cursor = conexion.connection.cursor()

        fecha1 = request.args.get('fecha1')
        fecha2 = request.args.get('fecha2')

        # formato de la fecha %Y-%m-%d %H:%i:%s
        sql= "SELECT * FROM Pomodoro WHERE Fecha BETWEEN %s AND %s"
        cursor.execute(sql, (fecha1, fecha2))
        datos = cursor.fetchall()
        print(datos)
        Info_al=[]
        for fila in datos:
            Datos_E={"Id":fila[0],"Usuario":fila[1],"fecha":fila[2],"Penalizacion_No_P":fila[3],"Penalizacion_No_S":fila[4],"Estado":fila[5],"Sentado_Descanso":fila[6],"Total_Tiempo":fila[7]}
            Info_al.append(Datos_E)
        print("/Datos GET")
        print(Info_al)
        return jsonify(Info_al)

    except Exception as ex:
       print(ex)
       return jsonify({"mensaje": "Error 1"})

#para obtener el ultimo pomodoro
#@cross_origin
@app.route("/ultimo",methods=["GET"])
def ultimo_pomodoro():
    try:
        cursor = conexion.connection.cursor()
        sql= "SELECT * FROM Pomodoro WHERE id = (SELECT MAX(id) FROM Pomodoro)"
        cursor.execute(sql)
        datos = cursor.fetchall()
        print(datos)
        Info_al=[]
        for fila in datos:
            Datos_E={"Id":fila[0],"Usuario":fila[1],"fecha":fila[2],"Penalizacion_No_P":fila[3],"Penalizacion_No_S":fila[4],"Estado":fila[5],"Sentado_Descanso":fila[6],"Total_Tiempo":fila[7]}
            Info_al.append(Datos_E)
        print("/Datos GET")
        print(Info_al)
        return jsonify(Info_al)

    except Exception as ex:
       print(ex)
       return jsonify({"mensaje": "Error 1"})

# ingreso de datos, en este caso se lo importante es el usuario y la fecha ya que los otros datos podran cambiar con el tiempo por lo que al inicio podria ser 0
# en el caso de Total tiempo entiendo que seria los 25min*60seg de trabajo y en Sentado Descanso entiendo que seria 5min*60seg de descanso
@app.route('/data', methods=['POST'])
def ingresar_info():
    print(request.json)
    try:
        cursor = conexion.connection.cursor()
        sql = "INSERT INTO Pomodoro (Usuario, Fecha, Penalizacion_No_P, Penalizacion_No_S, Estado, Sentado_Descanso, Total_Tiempo) VALUES (%s, NOW(),%s,%s,%s,%s,%s)"
        valores = (request.json["Usuario"],
                request.json["Penalizacion_No_P"],
                request.json["Penalizacion_No_S"],
                request.json["Estado"],
                request.json["Sentado_Descanso"],
                request.json["Total_Tiempo"])

        cursor.execute(sql, valores)
        conexion.connection.commit()  # Confirma la acción de inserción.
        return jsonify({'mensaje': "Pomodoro registrado."})
    except Exception as ex:
        print(ex)
        return jsonify({'mensaje': "Error 2"})

# actualizar la penalizacion P del ultimo pomodoro ingresado
@app.route("/penalizacionP",methods=["PUT"])
def actualizar1():
    try:
          cursor = conexion.connection.cursor() # no es nesesario el usuario pero para confirmar que se esta enviando bien, aumenta en 1 segundo
          sql = "UPDATE Pomodoro SET Penalizacion_No_P = Penalizacion_No_P + 1 WHERE id = (SELECT MAX(id) FROM Pomodoro) AND Usuario = %s"
          cursor.execute(sql, usuario_global)
          conexion.connection.commit()  # Confirma la acción de inserción.
          return jsonify({"Mensaje":"Actualizacion Penalizacion P"})


    except Exception as ex:
        return jsonify({"Mensaje":"Error al actualizar 1"})


# actualizar la penalizacion S del ultimo pomodoro ingresado
@app.route("/penalizacionS",methods=["PUT"])
def actualizar2():
    try:
          cursor = conexion.connection.cursor() # no es nesesario el usuario pero para confirmar que se esta enviando bien, solamente aumenta en 1 segundo
          sql = "UPDATE Pomodoro SET Penalizacion_No_S = Penalizacion_No_S + 1 WHERE id = (SELECT MAX(id) FROM Pomodoro) AND Usuario = %s"
          cursor.execute(sql, (usuario_global))
          conexion.connection.commit()  # Confirma la acción de inserción.
          return jsonify({"Mensaje":"Actualizacion Penalizacion S"})


    except Exception as ex:
        return jsonify({"Mensaje":"Error al actualizar 2"})

# actualizar el estado aunque no se si sirva de algo porque no hay grafica en vivo de esta, y al final no se que va a mostrar
@app.route("/estado",methods=["PUT"])
def actualizarE():
    try:
          cursor = conexion.connection.cursor() # no es nesesario el usuario pero para confirmar que se esta enviando bien, cambia entre 0 y 1
          sql = "UPDATE Pomodoro SET Estado = NOT Estado WHERE id = (SELECT MAX(id) FROM Pomodoro) AND Usuario = %s"
          cursor.execute(sql, (usuario_global))
          conexion.connection.commit()  # Confirma la acción de inserción.
          return jsonify({"Mensaje":"Actualizacion Estado"})

    except Exception as ex:
        return jsonify({"Mensaje":"Error al actualizar Estado"})

# actualizar el tiempo de trabajo del ultimo pomodoro ingresado
@app.route("/tiempot",methods=["PUT"])
def actualizarTT():
    try:
          cursor = conexion.connection.cursor() # no es nesesario el usuario pero para confirmar que se esta enviando bien
          sql = "UPDATE Pomodoro SET Total_Tiempo = %s WHERE id = (SELECT MAX(id) FROM Pomodoro) AND Usuario = %s"
          cursor.execute(sql, (request.json["Total_Tiempo"], usuario_global))
          conexion.connection.commit()  # Confirma la acción de inserción.
          return jsonify({"Mensaje":"Actualizacion tiempoT"})


    except Exception as ex:
        return jsonify({"Mensaje":"Error al actualizar tiempoT"})

# actualizar el tiempo de trabajo del ultimo pomodoro ingresado
@app.route("/tiempoD",methods=["PUT"])
def actualizarTD():
    try:
          cursor = conexion.connection.cursor() # no es nesesario el usuario pero para confirmar que se esta enviando bien
          sql = "UPDATE Pomodoro SET Sentado_Descanso = %s WHERE id = (SELECT MAX(id) FROM Pomodoro) AND Usuario = %s"
          cursor.execute(sql, (request.json["Total_Tiempo"], usuario_global))
          conexion.connection.commit()  # Confirma la acción de inserción.
          return jsonify({"Mensaje":"Actualizacion tiempo Descanso"})


    except Exception as ex:
        return jsonify({"Mensaje":"Error al actualizar tiempo Descanso"})

# actualizar el usuario del ultimo pomodoro ingresado,
@app.route("/usuario",methods=["PUT"])
def actualizarU():
    global usuario_global 
    usuario_global = (request.json["Usuario"])

#verificar coneccion
def is_connected():
    try:

        cursor = conexion.connection.cursor()
        cursor.execute('SELECT 1')
        cursor.close()
        return True
    except:
        return False
#ruta principal
#@cross_origin
@app.route('/')
def home():
    if is_connected():
        return jsonify({'message': 'Hello, World!'})
    else:
        return jsonify({'message': 'Error de conexion'})