import mysql.connector
import paho.mqtt.client as mqtt

# Paramètres de connexion au broker MQTT
broker_address = "172.20.233.40"
broker_port = 1883
topic = "test_co2"

# Paramètres de connexion à la base de données
db_host = "172.20.233.40"
db_user = "phpmyadmin"
db_password = "phpmyadmin"
db_name = "Base_Projet"

# Fonction de callback qui est appelée lorsque le client MQTT se connecte au broker
def on_connect(client, userdata, flags, rc):
    print("Connexion au broker MQTT établie avec succès")

    # Abonnement au topic
    client.subscribe(topic)


# Fonction de callback qui est appelée lorsque le client MQTT reçoit un message
def on_message(client, userdata, message):
    print("Message reçu sur le topic :", message.topic)
    print("Contenu du message :", message.payload.decode())


# Création d'un client MQTT
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message


# Connexion au broker MQTT
client.connect(broker_address, broker_port)


while 1 == 1:
    client.loop_forever() 
# Boucle principale du client MQTT


    # Connexion à la base de données
    cnx = mysql.connector.connect(host=db_host, user=db_user, password=db_password, database=db_name)
    cursor = cnx.cursor()

    # Exécution d'une requête d'insertion
    insert_query = "INSERT INTO table (colonne1, colonne2) VALUES (%s, %s)"
    values = (message.topic, message.payload.decode())
    cursor.execute(insert_query, values)
    cnx.commit()
    print("Données insérées avec succès")

    # Fermeture de la connexion à la base de données
    cursor.close()
    cnx.close()




