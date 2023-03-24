import mysql.connector

# Paramètres de connexion à la base de données
host = "172.20.233.40"
user = "phpmyadmin"
password = "phpmyadmin"
database = "Base_Projet"

# Connexion à la base de données
try:
    cnx = mysql.connector.connect(host=host, user=user, password=password, database=database)
    print("Connexion à la base de données réussie")
    
    # Effectuez ici les opérations que vous souhaitez effectuer sur la base de données

     # Exécution d'une requête d'insertion
    cursor = cnx.cursor()
    insert_query = "INSERT INTO Mesure (id, CO2, Temp, Hum, Horodatage) VALUES (%s, %s, %s, %s, %s)"
    values = ("22", "valeur2", "5", "20", "2018-09-15 10:35")
    cursor.execute(insert_query, values)
    cnx.commit()
    print("Données insérées avec succès")

except mysql.connector.Error as err:
    print("Erreur de connexion à la base de données : {}".format(err))

finally:
    # Fermeture de la connexion
    if 'cnx' in locals() and cnx.is_connected():
        cnx.close()
        print("Connexion à la base de données fermée")
