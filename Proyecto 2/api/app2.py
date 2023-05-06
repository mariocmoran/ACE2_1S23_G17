from flask import Flask, jsonify, request
from flask_mysqldb import MySQL
from flask_cors import CORS,cross_origin
import pytz
from datetime import datetime

activacionBomba = 0 # 0 = False, 1 = True
tiempoActivacion = 0
idRiego = 0

def create_app():
    app = Flask(__name__)
    return app

app = create_app()
cors = CORS(app)

app.config["DEBUG"] = True
app.config['MYSQL_HOST'] = 'Grupo17.mysql.pythonanywhere-services.com'
app.config['MYSQL_USER'] = 'Grupo17'
app.config['MYSQL_PASSWORD'] = '12345678abc'
app.config['MYSQL_DB'] = 'Grupo17$Riego'
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
        sql= "SELECT * FROM Datos WHERE fecha BETWEEN %s AND %s"
        cursor.execute(sql, (fecha1, fecha2))
        datos = cursor.fetchall()
        print(datos)
        Info_al=[]
        for fila in datos:
            Datos_E={"Id":fila[0],"temperatura_externa":fila[1],"temperatura_interna":fila[2],"humedad_tierra":fila[3],"porcentaje":fila[4],"estado":fila[5],"fecha":fila[6]}
            Info_al.append(Datos_E)
        print("/Datos GET")
        print(Info_al)
        return jsonify(Info_al)

    except Exception as ex:
       print(ex)
       return jsonify({"mensaje": "Error 1.0"})

#para obtener el ultimo riego
@cross_origin
@app.route("/ultimo",methods=["GET"])
def ultimo_riego():
    global usuario_global
    try:
        cursor = conexion.connection.cursor()
        sql= "SELECT * FROM Datos WHERE id = (SELECT MAX(id) FROM Datos)"
        cursor.execute(sql)
        datos = cursor.fetchall()
        print(datos)
        Info_al=[]
        for fila in datos:
            Datos_E={"Id":fila[0],"temperatura_externa":fila[1],"temperatura_interna":fila[2],"humedad_tierra":fila[3],"porcentaje":fila[4],"estado":fila[5],"fecha":fila[6]}
            Info_al.append(Datos_E)
        print("/Datos GET")
        print(Info_al)
        return jsonify(Info_al)

    except Exception as ex:
       print(ex)
       return jsonify({"mensaje": "Error 1.1"})


# ingreso de datos, en este caso se lo importante es el idRiego y la fecha ya que los otros datos podran cambiar con el tiempo por lo que al inicio podria ser 0
@cross_origin
@app.route('/add', methods=['POST'])
def ingresar_info():
    print(request.json)
    #obtenemos fecha y hora
    now_utc = datetime.now(pytz.UTC)
    tz = pytz.timezone('America/Guatemala')
    now_guatemala = now_utc.astimezone(tz)
    new_now = now_guatemala.strftime('%Y-%m-%d %H:%M:%S')
    try:
        cursor = conexion.connection.cursor()
        sql = "INSERT INTO Datos (temperatura_externa, temperatura_interna, humedad_tierra, porcentaje, estado, fecha) VALUES (%s,%s,%s,%s,%s,%s)"
        global idRiego
        valores = (
                request.json["temperatura_externa"],
                request.json["temperatura_interna"],
                request.json["humedad_tierra"],
                request.json["porcentaje"],
                activacionBomba,
                new_now,
                )

        cursor.execute(sql, valores)
        conexion.connection.commit()  # Confirma la acción de inserción.
        return jsonify({'mensaje': "Riego registrado."})
    except Exception as ex:
        print(ex)
        return jsonify({'mensaje': "Error 2"})


# actualizar el tiempo de activacion y el estado de la bomba, cuando se envien valores por defecto
@cross_origin
@app.route("/update",methods=["POST"])
def actualizar():
    global activacionBomba
    global tiempoActivacion
    tiempoActivacion = (request.json["tiempoActivacion"])
    activacionBomba = (request.json["activacionBomba"])
    return jsonify({"Mensaje":"Se actualizaron los datos"})

# actualizar el estado de la bomba individual, mas que todo cuando se active o se apague
@cross_origin
@app.route("/update1",methods=["POST"])
def actualizarEstado():
    global activacionBomba
    global tiempoActivacion
    activacionBomba = (request.json["activacionBomba"])
    return jsonify({"Mensaje":"Se actualizaron los datos"})


@cross_origin
@app.route("/estadoRiego",methods=["GET"])
def getEstado():
    global activacionBomba
    global tiempoActivacion
    return jsonify({"activacion":activacionBomba, "tiempo": tiempoActivacion})


# actualizar id del ultimo riego, por el momento no se utiliza
@cross_origin
@app.route("/idRiego",methods=["POST"])
def actualizarID():
    try:
        global idRiego
        idRiego += 1
        print(idRiego)
        return jsonify({"Mensaje": "idRiego actualizado"})
    except:
        return jsonify({"Mensaje":"Error al obtener idRiego"})


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
@cross_origin
@app.route('/')
def home():
    if is_connected():
        return jsonify({'message': 'Hello, World!'})
    else:
        return jsonify({'message': 'Error de conexion'})
