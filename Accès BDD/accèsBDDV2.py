import mysql.connector
import paho.mqtt.client as mqtt
import json

# Configuration de la connexion à la base de données MySQL
cnx = mysql.connector.connect(user='phpmyadmin', password='phpmyadmin',
                              host='172.20.233.40', database='Base_Projet')
cursor = cnx.cursor()

# Callback appelée lors de la connexion au broker MQTT
def on_connect(client, userdata, flags, rc):
    print("Connecté au broker MQTT avec le code de retour : " + str(rc))
    # Abonnement au sujet "capteur/Temperature"
    client.subscribe("test_co2")

# Callback appelée lorsqu'un message est reçu sur le sujet "capteur/Temperature"
def on_message(client, userdata, msg):
    # Décodage du message JSON
    donnees = json.loads(msg.payload.decode())
    print("Reçu : " + str(donnees))

    # Requête d'insertion pour la table "capteur"
    requete = """
    INSERT INTO Capteur (numéro, version)
    VALUES (%s, %s)
    """
    params = (donnees['numéro'], donnees['version'])
    cursor.execute(requete, params)

    # Enregistrement des modifications
    cnx.commit()

# Création d'un client MQTT
client = mqtt.Client()

# Configuration du callback pour la connexion au broker MQTT
client.on_connect = on_connect

# Configuration du callback pour la réception des messages MQTT
client.on_message = on_message

# Connexion au broker MQTT
client.connect("172.20.233.40", 3306, 60)

# Boucle d'écoute des messages MQTT
client.loop_forever()

# Fermeture de la connexion à la base de données MySQL
cursor.close()
cnx.close()
