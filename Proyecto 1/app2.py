from flask import Flask, jsonify, request
from flask_mysqldb import MySQL
from flask_cors import CORS,cross_origin




usuario_global = ""
tiempoTrabajo_global = 45
tiempoDescanso_global = 15

def create_app():
    app = Flask(__name__)
    return app

app = create_app()
cors = CORS(app)

app.config["DEBUG"] = True
app.config['MYSQL_HOST'] = 'Grupo17.mysql.pythonanywhere-services.com'
app.config['MYSQL_USER'] = 'Grupo17'
app.config['MYSQL_PASSWORD'] = '12345678abc'
app.config['MYSQL_DB'] = 'Grupo17$Pomodoro'
conexion = MySQL(app)



# obtener dator por rango de fecha y hora, esta es para las graficas
@cross_origin
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
            Datos_E={"Id":fila[0],"Usuario":fila[1],"Fecha":fila[2],"Penalizacion_No_P":fila[3],"Penalizacion_No_S":fila[4],"Estado":fila[5],"Tiempo_Trabajo":fila[6],"Tiempo_Descanso":fila[7], "No_Pomodoro":fila[8]}
            Info_al.append(Datos_E)
        print("/Datos GET")
        print(Info_al)
        return jsonify(Info_al)

    except Exception as ex:
       print(ex)
       return jsonify({"mensaje": "Error 1.0"})

#para obtener el ultimo pomodoro
@cross_origin
@app.route("/ultimo",methods=["GET"])
def ultimo_pomodoro():
    global usuario_global
    try:
        cursor = conexion.connection.cursor()
        sql= "SELECT * FROM Pomodoro WHERE id = (SELECT MAX(id) FROM Pomodoro WHERE Usuario = \""+usuario_global+"\")"
        cursor.execute(sql)
        datos = cursor.fetchall()
        print(datos)
        Info_al=[]
        for fila in datos:
            Datos_E={"Id":fila[0],"Usuario":fila[1],"Fecha":fila[2],"Penalizacion_No_P":fila[3],"Penalizacion_No_S":fila[4],"Estado":fila[5],"Tiempo_Trabajo":fila[6],"Tiempo_Descanso":fila[7], "No_Pomodoro":fila[8]}
            Info_al.append(Datos_E)
        print("/Datos GET")
        print(Info_al)
        return jsonify(Info_al)

    except Exception as ex:
       print(ex)
       return jsonify({"mensaje": "Error 1.1"})

#para obtener los ultimos 4 que coincidad con el usuario, para esto hay que tener en cuenta que el usuario nunca se puede repetir, sino podria traer datos de pomodoros de otro ciclo
@cross_origin
@app.route("/ultimos4",methods=["GET"])
def ultimos_4_pomodoro():
    global usuario_global
    try:
        cursor = conexion.connection.cursor()
        sql= "SELECT * FROM Pomodoro WHERE Usuario = \""+usuario_global+"\" ORDER BY id DESC LIMIT 4"
        cursor.execute(sql)
        datos = cursor.fetchall()
        print(datos)
        Info_al=[]
        for fila in datos:
            Datos_E={"Id":fila[0],"Usuario":fila[1],"Fecha":fila[2],"Penalizacion_No_P":fila[3],"Penalizacion_No_S":fila[4],"Estado":fila[5],"Tiempo_Trabajo":fila[6],"Tiempo_Descanso":fila[7], "No_Pomodoro":fila[8]}
            Info_al.append(Datos_E)
        print("/Datos GET")
        print(Info_al)
        return jsonify(Info_al)

    except Exception as ex:
       print(ex)
       return jsonify({"mensaje": "Error"})

# ingreso de datos, en este caso se lo importante es el usuario y la fecha ya que los otros datos podran cambiar con el tiempo por lo que al inicio podria ser 0
# en el caso de Tiempo_Trabajo entiendo que seria los 25min*60seg de trabajo y en Tiempo_Descanso entiendo que seria 5min*60seg de descanso, los valores por default
@cross_origin
@app.route('/data', methods=['POST'])
def ingresar_info():
    print(request.json)
    try:
        cursor = conexion.connection.cursor()
        sql = "INSERT INTO Pomodoro (Usuario, Fecha, Penalizacion_No_P, Penalizacion_No_S, Estado, Tiempo_Descanso, Tiempo_Trabajo, No_Pomodoro) VALUES (%s, NOW(),%s,%s,%s,%s,%s,%s)"
        global usuario_global
        valores = (usuario_global,
                request.json["Penalizacion_No_P"],
                request.json["Penalizacion_No_S"],
                request.json["Estado"],
                request.json["Tiempo_Descanso"],
                request.json["Tiempo_Trabajo"],
                request.json["No_Pomodoro"])

        cursor.execute(sql, valores)
        conexion.connection.commit()  # Confirma la acción de inserción.
        return jsonify({'mensaje': "Pomodoro registrado."})
    except Exception as ex:
        print(ex)
        return jsonify({'mensaje': "Error 2"})

# actualizar la penalizacion P del ultimo pomodoro ingresado
@cross_origin
@app.route("/penalizacionP",methods=["PUT"])
def actualizar1():
    global usuario_global
    try:
          cursor = conexion.connection.cursor() # no es nesesario el usuario pero para confirmar que se esta enviando bien, aumenta en 1 segundo
          sql = "UPDATE Pomodoro SET Penalizacion_No_P = Penalizacion_No_P + 1 WHERE id = (SELECT MAX(id) FROM Pomodoro) AND Usuario = \""+usuario_global+"\""

          cursor.execute(sql)
          conexion.connection.commit()  # Confirma la acción de inserción.
          return jsonify({"Mensaje":"Actualizacion Penalizacion P"})


    except Exception as ex:
        return jsonify({"Mensaje":"Error al actualizar 1"})


# actualizar la penalizacion S del ultimo pomodoro ingresado
@cross_origin
@app.route("/penalizacionS",methods=["PUT"])
def actualizar2():
    global usuario_global
    try:
          cursor = conexion.connection.cursor() # no es nesesario el usuario pero para confirmar que se esta enviando bien, solamente aumenta en 1 segundo
          sql = "UPDATE Pomodoro SET Penalizacion_No_S = Penalizacion_No_S + 1 WHERE id = (SELECT MAX(id) FROM Pomodoro) AND Usuario = \""+usuario_global+"\""
          cursor.execute(sql)
          conexion.connection.commit()  # Confirma la acción de inserción.
          return jsonify({"Mensaje":"Actualizacion Penalizacion S"})


    except Exception as ex:
        return jsonify({"Mensaje":"Error al actualizar 2"})

# actualizar el estado aunque no se si sirva de algo porque no hay grafica en vivo de esta, y al final no se que va a mostrar
@cross_origin
@app.route("/estado",methods=["PUT"])
def actualizarE():
    global usuario_global
    try:
          cursor = conexion.connection.cursor() # no es nesesario el usuario pero para confirmar que se esta enviando bien, cambia entre 0 y 1
          sql = "UPDATE Pomodoro SET Estado = NOT Estado WHERE id = (SELECT MAX(id) FROM Pomodoro) AND Usuario = \""+usuario_global+"\""
          cursor.execute(sql)
          conexion.connection.commit()  # Confirma la acción de inserción.
          return jsonify({"Mensaje":"Actualizacion Estado"})

    except Exception as ex:
        return jsonify({"Mensaje":"Error al actualizar Estado"})

# actualizar el tiempo de trabajo del ultimo pomodoro ingresado, ahora se modifica con el tiempo de trabajo global
@cross_origin
@app.route("/tiempot",methods=["PUT"])
def actualizarTT():
    try:
        cursor = conexion.connection.cursor() # no es nesesario el usuario pero para confirmar que se esta enviando bien
        sql = "UPDATE Pomodoro SET Tiempo_Trabajo = %s WHERE id = (SELECT MAX(id) FROM Pomodoro) AND Usuario = %s"
        global usuario_global
        global tiempoTrabajo_global
        cursor.execute(sql, (tiempoTrabajo_global, usuario_global))
        conexion.connection.commit()  # Confirma la acción de inserción.
        return jsonify({"Mensaje":"Actualizacion tiempoT"})


    except Exception as ex:
        return jsonify({"Mensaje":"Error al actualizar tiempoT"})

# actualizar el tiempo de trabajo y descanso del ultimo pomodoro ingresado, esto en las variables globales
@cross_origin
@app.route("/tiempotd",methods=["PUT"])
def actualizarTTD():
    global tiempoTrabajo_global
    global tiempoDescanso_global
    tiempoTrabajo_global = (request.json["Tiempo_Trabajo"])
    tiempoDescanso_global = (request.json["Tiempo_Descanso"])
    return jsonify({"Mensaje":"Se actualizaron los tiempos"})

# obtener Tiempo Trabajo y Descanso
@cross_origin
@app.route("/obtenerTTD",methods=["GET"])
def obtenerTTrabajoDescanso():
    #global usuario_global
    global tiempoTrabajo_global
    global tiempoDescanso_global
    try:
        #cursor = conexion.connection.cursor()
        #sql= "SELECT Tiempo_Trabajo, Tiempo_Descanso FROM Pomodoro WHERE id = (SELECT MAX(id) FROM Pomodoro WHERE Usuario = \""+usuario_global+"\")"
        #cursor.execute(sql)
        #dato = cursor.fetchone();
        #print(dato)
        dator = {"Tiempo_Trabajo": tiempoTrabajo_global, "Tiempo_Descanso": tiempoDescanso_global}
        print(dator)
        return jsonify(dator)


    except Exception as ex:
        return jsonify({"Mensaje":"Error al obtener TT y TD"})

# actualizar el usuario del ultimo pomodoro ingresado,
@cross_origin
@app.route("/usuario",methods=["PUT"])
def actualizarU():
    global usuario_global
    usuario_global = (request.json["Usuario"])
    return jsonify({"Mensaje":"Usuario recibido"})

# actualizar el tiempo de descanso del ultimo pomodoro ingresado, ahora se modifica con el tiempo de descanso global
@cross_origin
@app.route("/tiempoD",methods=["PUT"])
def actualizarTD():
    try:
          cursor = conexion.connection.cursor() # no es nesesario el usuario pero para confirmar que se esta enviando bien
          sql = "UPDATE Pomodoro SET Tiempo_Descanso = %s WHERE id = (SELECT MAX(id) FROM Pomodoro) AND Usuario = %s"
          global usuario_global
          global tiempoDescanso_global
          cursor.execute(sql, (tiempoDescanso_global, usuario_global))
          conexion.connection.commit()  # Confirma la acción de inserción.
          return jsonify({"Mensaje":"Actualizacion tiempo Descanso"})


    except Exception as ex:
        return jsonify({"Mensaje":"Error al actualizar tiempo Descanso"})

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
@cross_origin
@app.route('/')
def home():
    if is_connected():
        return jsonify({'message': 'Hello, World!'})
    else:
        return jsonify({'message': 'Error de conexion'})

