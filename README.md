# Co2_project
Le broker se base sur le protocole [MQTT](https://github.com/Knightmore1/Co2_project/wiki/MQTT) :
![image](https://user-images.githubusercontent.com/123626866/224250600-c5e4f9b4-e828-49b7-bbdb-4b9f0522d8bb.png) 

### MQTT c'est quoi ?


Plus connu sous l’acronyme MQTT, le protocole Message Queuing Telemetry Transport est un protocole de messagerie léger adapté aux situations où les clients doivent utiliser peu de code et sont connectés à des réseaux peu fiables ou limités en bande passante. Il est principalement utilisé dans la communication entre machines (M2M) ou sur les types de connexions propres à l’Internet des Objets.

### Pourquoi mqtt ?

-Protocole __ouvert__, __simple__, __léger__ et __facile à mettre en œuvre__.  
-Idéal pour la __transmission de données__ avec une __faible bande passante__.  
-__Adapté au sans fil__.  
-__Faible consommation électrique__.  
-__Très rapide__.  
-__Faible en ressource processeur__ et __faible empreinte mémoire__.  
-__93x plus rapide en débit__ que le protocole HTTP.  
-__12x moins gourmand à l’envoi__ que l’HTTP.  
-__170x moins gourmand à la réception__ que l’HTTP.  
-Utilise __8x moins de bande passante__ sur le réseau que l’HTTP.  
-Un message peut faire __une taille maximum de 256mo__.  
-Les topics sont construits de manière hiérarchique comme une URL.  


  
### La sécurité :  
Niveau transport TLS/SSL  
Niveau authentification par certificats SSL/TLS  
Authentification par user/mdp  


### QOS:  

Niveau 0 : message envoyer au plus une fois  
Niveau 1 : message envoyer au moins une fois  
Niveau 2 : message sauvegarder jusqu’à la réception par le subscriber.  

![image](https://user-images.githubusercontent.com/123626866/224341324-0b0a97fe-bb16-4947-96cc-82a7584def6c.png)






## Configurer le broker MQTT avec mosquitto:

1. Installer le broker MQTT  
![image](https://user-images.githubusercontent.com/123626866/225907997-7da581b8-d3b5-4008-8e41-100eac11da4e.png)

2. Une fois installer, vérifier si il est en cours d’exécution  
![image](https://user-images.githubusercontent.com/123626866/225908020-359707a3-0cbe-462c-a2c7-01218ba2aee8.png)

Ceci devrait apparaître :
![image](https://user-images.githubusercontent.com/123626866/225908094-1de234bd-0fa4-494f-8180-566f1b312cd7.png)

Cela signifie qu’il tourne bien.  


3. Pour tester le broker MQTT, il faut utiliser un système subscribe/publish sur des topics, les commandes mosquitto_sub et mosquitto_publish permettent de le faire. La commande "mosquitto_sub" permet de se connecter à un broker MQTT et de s'abonner à un ou plusieurs topics pour recevoir les messages publiés sur ces topics.  

La commande "mosquitto_pub" permet quant à elle de publier des messages sur un topic spécifique via un broker MQTT.  

Pour utiliser ces commandes, il faut installer le client MQTT mosquitto :

![image](https://user-images.githubusercontent.com/123626866/225908166-0bb3c05d-7af9-4c54-825b-258f29128c97.png)




Une fois cela fait, on peut utiliser les deux commandes

sub : S’abonner à un topic pour voir les publications du topic en quesion
![image](https://user-images.githubusercontent.com/123626866/225908205-cbddee23-4db7-4aa5-85c4-1ce821e0f7b5.png)



-h : pour l’adresse IP du server ou le nom de domaine  -t : le nom du topic
exemple : S’abonner au topic maison/cuisine/temperature

![image](https://user-images.githubusercontent.com/123626866/225908235-d772635c-9c2a-4d7b-9c0f-8b90c5218329.png)




pub : Publier un message

![image](https://user-images.githubusercontent.com/123626866/225908263-541062f5-37eb-4ab7-9698-53dac40cc0d2.png)




-h : pour l’adresse IP du server ou le nom de domaine  -t : le nom du topic -m :  publier un message


exemple : publier un message sur le topic maison/cuisine/temperature

![image](https://user-images.githubusercontent.com/123626866/225908297-22b2dc4c-8e5d-4825-b437-ef7a1d4bceb9.png)



BROKER MQTT mosquitto opérationnel, on peut envoyer des messages sur les topics ainsi que s’y abonner. 

Extra : Pour éviter de recevoir des spam ou d(autres choses inutile dans les topics, on peut mettre en place un système d’authentification avec nom d’utilisateur/Mot de passe.

Pour le faire , il faut ouvrir le fichier de configuration du broker mosquitto avec la commande suivante :

![image](https://user-images.githubusercontent.com/123626866/225908325-445c21cf-0c8b-4667-a393-112dac5ffb1f.png)



Le fichier s ‘ouvrira avec le logiciel de traitement de texte nano.

A la fin du fichier, il faut ajouter les deux lignes suivantes :

![image](https://user-images.githubusercontent.com/123626866/225908348-b85e4482-da7a-4db5-913e-1a0f9ae6f140.png)


première ligne : désactive la possibilité de se connecter anonymement à votre broker 
deuxième ligne : spécifie l'emplacement du fichier qui contiendra les noms d'utilisateur et les mots de passe.  Fichier qu’il faut créer bien sur.

Le fichier de mot de passe doit être comme ceci :

![image](https://user-images.githubusercontent.com/123626866/225908455-ad8ce094-b5f0-4584-b25a-8b5c39ba3f9a.png)






Enregistrez le fichier de mot de passe et redémarrez votre broker MQTT pour prendre en compte les modifications. 

Une fois que vous avez créé des noms d'utilisateur et des mots de passe pour votre broker MQTT, vous pouvez vous connecter à votre broker en utilisant ces informations d'identification. Par exemple, si vous utilisez le client MQTT Mosquitto, vous pouvez vous connecter en utilisant la commande suivante : 

mosquitto_sub -h <nom_de_domaine_ou_adresse_IP_du_broker> -t <topic> -u <nom_d_utilisateur> -P <mot_de_passe>

avec -u pour le nom d’utilisateur et -P pour le mot de passe.

