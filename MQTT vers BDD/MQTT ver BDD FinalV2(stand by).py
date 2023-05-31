import paho.mqtt.client as mqtt
import mysql.connector
import time

# Configuration de la connexion MQTT
mqtt_broker_address = "172.20.233.71"
mqtt_broker_port = 1883
mqtt_topic1 = "co2"
mqtt_topic2 = "humidity"
mqtt_topic3 = "temperature"
mqtt_topic4 = "mac_address"
mqtt_username = "root"
mqtt_password = "root"

# Configuration de la connexion MySQL
mysql_host = "172.20.233.66"
mysql_user = "phpmyadmin"
mysql_password = "admin"
mysql_database = "co2"

# Variables pour stocker les différentes données
co2_value = None
humidity_value = None
temperature_value = None
mac_address_value = None

# Fonction de rappel pour la réception de messages MQTT
def on_message(client, userdata, message):
    global co2_value
    global humidity_value
    global temperature_value
    global mac_address_value

    topic = message.topic
    payload = message.payload.decode()
    print("Topic :", message.topic)
    print("Message :", str(message.payload.decode("utf-8")))

    if topic == mqtt_topic1:
        co2_value = payload
    elif topic == mqtt_topic2:
        humidity_value = payload
    elif topic == mqtt_topic3:
        temperature_value = payload
    elif topic == mqtt_topic4:
        mac_address_value = payload
    else:
        print("Topic inconnu :", topic)

    # Vérifier si toutes les valeurs sont disponibles, puis insérer dans la base de données
    if co2_value is not None and humidity_value is not None and temperature_value is not None and mac_address_value is not None:
        try:
            cnx = mysql.connector.connect(user=mysql_user, password=mysql_password,
                                          host=mysql_host, database=mysql_database)
            cursor = cnx.cursor()

             # Première requête pour insérer les données des topics 1, 2, 3
            query1 = "INSERT INTO Mesure (CO2, Hum, Temp) VALUES (%s, %s, %s)"
            data1 = (co2_value, humidity_value, temperature_value)
            cursor.execute(query1, data1)

             # Deuxième requête pour insérer les données du topic4
            query2 = "INSERT INTO Capteur (Numero) VALUES (%s)"
            data2 = (mac_address_value)
            cursor.execute(query2, data2)

            cnx.commit()
            print("Données insérées avec succès")
        except mysql.connector.Error as err:
            print("Erreur lors de l'insertion des données : {}".format(err))
        finally:
            cursor.close()
            cnx.close()
        

        # Réinitialiser les valeurs après l'insertion dans la base de données
        co2_value = None
        humidity_value = None
        temperature_value = None
        mac_address_value = None


# Ajout d'une condition pour afficher un message si rien n'est reçu sur les topics
#def on_subscribe(client, userdata, mid, granted_qos):
 #   print("Abonnement réussi")
  #  if len(granted_qos) != 0:
   #     print("Aucun message reçu sur les topics.")
    #else:
     #   print("Messages reçus sur les topics.")

# Configuration du client MQTT
client = mqtt.Client()
client.username_pw_set(mqtt_username, mqtt_password)
client.on_message = on_message

client.connect(mqtt_broker_address, mqtt_broker_port)
client.subscribe(mqtt_topic1)
client.subscribe(mqtt_topic2)
client.subscribe(mqtt_topic3)
client.subscribe(mqtt_topic4)

# Boucle principale pour la réception de messages MQTT
client.loop_forever()
