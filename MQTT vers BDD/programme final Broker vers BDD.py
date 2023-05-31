import paho.mqtt.client as mqtt
import mysql.connector

# Configuration de la connexion MQTT
mqtt_broker_address = "172.20.233.39"
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

# Variables pour stocker les differentes donnees
co2_value = None
humidity_value = None
temperature_value = None
mac_address_value = None

# Fonction de rappel pour la reception de messages MQTT
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

    # Verifier si toutes les valeurs sont disponibles, puis inserer dans la base de donnees
    if co2_value is not None and humidity_value is not None and temperature_value is not None:
        try:
            cnx = mysql.connector.connect(user=mysql_user, password=mysql_password,
                                          host=mysql_host, database=mysql_database)
            cursor = cnx.cursor()

             # Premiere requete pour inserer les donnees des topics 1, 2, 3
            query = "INSERT INTO Mesure (CO2, Hum, Temp) VALUES (%s, %s, %s);"
            data = (co2_value, humidity_value, temperature_value)
            cursor.execute(query, data)

            cnx.commit()

            print("Donnees inserees avec succes")
        except mysql.connector.Error as err:
            print("Erreur lors de l'insertion des donnees : {}".format(err))
        finally:
            cursor.close()
            cnx.close()
        

        # Reinitialiser les valeurs apres l'insertion dans la base de donnees
        co2_value = None
        humidity_value = None
        temperature_value = None
        


    # Verifier si la valeur est disponible, puis inserer dans la base
    if mac_address_value is not None:

        try:
            cnx = mysql.connector.connect(user=mysql_user, password=mysql_password,
                                            host=mysql_host, database=mysql_database)
            cursor = cnx.cursor()

                 # Seconde requete pour inserer les donnees du topic 4

            query = "INSERT INTO Capteur (AdresseMac) VALUES (%s);"
            data = (mac_address_value,)
            cursor.execute(query, data)

            cnx.commit()

            print("Donnees inserees avec succes")
        except mysql.connector.Error as err:
            print("Erreur lors de l'insertion des donnees : {}".format(err))
        finally:
            cursor.close()
            cnx.close()

            mac_address_value = None


# Configuration du client MQTT
client = mqtt.Client()
client.username_pw_set(mqtt_username, mqtt_password)
client.on_message = on_message

client.connect(mqtt_broker_address, mqtt_broker_port)
client.subscribe(mqtt_topic1)
client.subscribe(mqtt_topic2)
client.subscribe(mqtt_topic3)
client.subscribe(mqtt_topic4)

# Boucle principale pour la reception de messages MQTT
client.loop_forever()
