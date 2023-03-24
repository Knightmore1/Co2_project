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

except mysql.connector.Error as err:
    print("Erreur de connexion à la base de données : {}".format(err))

#finally:
    # Fermeture de la connexion
    #if 'cnx' in locals() and cnx.is_connected():
     #   cnx.close()
      #  print("Connexion à la base de données fermée")
