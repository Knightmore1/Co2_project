import mysql.connector


# Paramètres de connexion à la base de données
db_host = "172.20.233.66"
db_user = "root"
db_password = "root"
db_name = "co2"




while 1 == 1:

    # Connexion à la base de données
    cnx = mysql.connector.connect(host=db_host, user=db_user, password=db_password, database=db_name)
    cursor = cnx.cursor()

    # Exécution d'une requête d'insertion
    insert_query = "INSERT INTO table (CO2) VALUES (%s)"
    values = (message.topic, message.payload.decode())
    cursor.execute(insert_query, values)
    cnx.commit()
    print("Données insérées avec succès")

    # Fermeture de la connexion à la base de données
    cursor.close()
    cnx.close()




