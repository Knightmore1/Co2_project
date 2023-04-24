import paho.mqtt.client as mqtt
import mysql.connector
import time

# Configuration de la connexion MQTT
mqtt_broker_address = "172.20.233.80"
mqtt_broker_port = 1883
mqtt_topic1 = "co2"
mqtt_topic2 = "humidity"
mqtt_topic3 = "temperature"
mqtt_username = "root"
mqtt_password = "root"

# Configuration de la connexion MySQL
mysql_host = "172.20.233.66"
mysql_user = "phpmyadmin"
mysql_password = "admin"
mysql_database = "co2"

# Variables pour stocker les valeurs de CO2, Humidité et Température
co2_value = None
humidity_value = None
temperature_value = None

# Fonction de rappel pour la réception de messages MQTT
def on_message(client, userdata, message):
    global co2_value
    global humidity_value
    global temperature_value

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
    else:
        print("Topic inconnu :", topic)

    # Vérifier si toutes les valeurs sont disponibles, puis insérer dans la base de données
    if co2_value is not None and humidity_value is not None and temperature_value is not None:
        try:
            cnx = mysql.connector.connect(user=mysql_user, password=mysql_password,
                                          host=mysql_host, database=mysql_database)
            cursor = cnx.cursor()
            query = "INSERT INTO Mesure (CO2, Hum, Temp) VALUES (%s, %s, %s)"
            data = (co2_value, humidity_value, temperature_value)
            cursor.execute(query, data)
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

# Configuration du client MQTT
client = mqtt.Client()
client.username_pw_set(mqtt_username, mqtt_password)
client.on_message = on_message
client.connect(mqtt_broker_address, mqtt_broker_port)
client.subscribe(mqtt_topic1)
client.subscribe(mqtt_topic2)
client.subscribe(mqtt_topic3)
# Boucle principale pour la réception de messages MQTT
client.loop_start()

while True:
    time.sleep(10)  # Attendre pendant 10 secondes
    if co2_value is not None and humidity_value is not None and temperature_value is not None:
        # Insérer les données dans la base de données
        on_message(client, None, None)

