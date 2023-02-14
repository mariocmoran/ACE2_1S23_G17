class DevelopmentConfig():
    DEBUG = True
    MYSQL_HOST="localhost"
    PORT=3306
    MYSQL_USER="root"
    MYSQL_PASSWORD="Practica1"
    MYSQL_DB="estación_metereologica"

   
config = {
    "development": DevelopmentConfig
}
