import paho.mqtt.client as mqtt
import mysql.connector
import time

# Configuration de la connexion MQTT
mqtt_broker_address = "172.20.233.80"
mqtt_broker_port = 1883
mqtt_topic1 = "co2"
mqtt_topic2 = "humidity"
mqtt_topic3 = "temperature"
mqtt_topic4 = "capteur_num"
mqtt_topic5 = "capteur_version"
mqtt_topic6 = "salles_numero"
mqtt_topic7 = "salles_batiment"
mqtt_topic8 = "salles_etage"
mqtt_topic9 = "salles_capacite"
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
capteur_num_value = None
capteur_version_value = None
salles_numero_value = None
salles_batiment_value = None
salles_etage_value = None
salles_capacite_value = None

# Fonction de rappel pour la réception de messages MQTT
def on_message(client, userdata, message):
    global co2_value
    global humidity_value
    global temperature_value
    global capteur_num_value
    global capteur_version_value
    global salles_numero_value
    global salles_batiment_value
    global salles_etage_value
    global salles_capacite_value

    
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
        capteur_num_value = payload
    elif topic == mqtt_topic5:
        capteur_version_value = payload
    elif topic == mqtt_topic6:
        salles_numero_value = payload
    elif topic == mqtt_topic7:
        salles_batiment_value = payload
    elif topic == mqtt_topic8:
        salles_etage_value = payload
    elif topic == mqtt_topic9:
        salles_capacite_value = payload
    else:
        print("Topic inconnu :", topic)


    # Vérifier si toutes les valeurs sont disponibles, puis insérer dans la base de données
    if co2_value is not None and humidity_value is not None and temperature_value is not None and capteur_num_value is not None and capteur_version_value is not None and salles_numero_value is not None and salles_batiment_value is not None and salles_etage_value is not None and salles_capacite_value is not None:
        try:
            cnx = mysql.connector.connect(user=mysql_user, password=mysql_password,
                                          host=mysql_host, database=mysql_database)
            cursor = cnx.cursor()
            query1 = "INSERT INTO Mesure (CO2, Hum, Temp) VALUES (%s, %s, %s)"
            data1 = (co2_value, humidity_value, temperature_value)
            cursor.execute(query1, data1)

            query2 = "INSERT INTO Capteur (Numero, Version, Salles_Numero) VALUES (%s, %s, %s)"
            data2 = (capteur_num_value, capteur_version_value, salles_numero_value)
            cursor.execute(query2, data2)

            query3 = "INSERT INTO Salles (Numero, Batiment, Etage, Capacite) VALUES (%s, %s, %s, %s)"
            data3 = (salles_numero_value, salles_batiment_value, salles_etage_value, salles_capacite_value)
            cursor.execute(query3, data3)
            cnx.commit()
            print("Données insérées avec succès")
         
        except mysql.connector.Error as err:
            print("Erreur lors de l'insertion des données : {}".format(err))
        finally:
            cursor.close()
            cnx.close()
    else:
        print("impossible d'entrer les données car erreur inattendue")        

        # Réinitialiser les valeurs après l'insertion dans la base de données
        co2_value = None
        humidity_value = None
        temperature_value = None
        capteur_num_value = None
        capteur_version_value = None
        salles_numero_value = None
        salles_batiment_value = None
        salles_etage_value = None
        salles_capacite_value = None

# Configuration du client MQTT
client = mqtt.Client()
client.username_pw_set(mqtt_username, mqtt_password)
client.on_message = on_message
client.connect(mqtt_broker_address, mqtt_broker_port)
client.subscribe(mqtt_topic1)
client.subscribe(mqtt_topic2)
client.subscribe(mqtt_topic3)
client.subscribe(mqtt_topic4)
client.subscribe(mqtt_topic5)
client.subscribe(mqtt_topic6)
client.subscribe(mqtt_topic7)
client.subscribe(mqtt_topic8)
client.subscribe(mqtt_topic9)
# Boucle principale pour la réception de messages MQTT
client.loop_forever()

