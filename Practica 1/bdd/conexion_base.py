class DevelopmentConfig():
    DEBUG = True
    MYSQL_HOST="localhost"
    PORT=3306
    MYSQL_USER="root"
    MYSQL_PASSWORD=""
    MYSQL_DB="estaci__n_metereologica"

   
config = {
    "development": DevelopmentConfig
}
