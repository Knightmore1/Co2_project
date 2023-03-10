# Co2_project
Le broker se base sur le protocole MQTT:
[MQTT](https://github.com/Knightmore1/Co2_project/wiki/MQTT)
![image](https://user-images.githubusercontent.com/123626866/224250373-0b556366-cf5e-4581-a010-9f859c024f25.png)
![image](https://user-images.githubusercontent.com/123626866/224250453-cc08b8ad-59e0-4b52-9fda-fde3dd63391c.png)
![image](https://user-images.githubusercontent.com/123626866/224250519-48e9ea12-f584-46db-92aa-f6e1a4db33db.png)
![image](https://user-images.githubusercontent.com/123626866/224250600-c5e4f9b4-e828-49b7-bbdb-4b9f0522d8bb.png)



Infos supp: 

93x plus rapide en débit que le protocole HTTP,  
12x moins gourmand à l’envoi que l’HTTP,  
170x moins gourmand à la réception que l’HTTP,  
consomme 8x moins de réseau que l’HTTP  



un message , taille max 256mo,  
les topics sont construits de manière hiérarchique comme une URL

pourquoi mqtt  

-protocole ouvert, simple, léger et faile à mettre en œuvre  
-Idéal pour la transmission de données avec une faible bande passante  
-Adapté au sans fil  
-Faible consommation elec  
-très rapide  
-fible en ressource processeur et faible emprunte mémoire  


  
La sécurité :  
Niveau transport TLS/SSL  
Niveau authentification par cértificats SSL/TLS  
Authentification par user/mdp  


QOS  

Niveau 0 : message envoyer au plus une fois  
Niveau 1 : message envoyer au moins une fois  
Niveau 2 : message sauvegarder jusqu’à la réception par le subscriber.  

![image](https://user-images.githubusercontent.com/123626866/224341324-0b0a97fe-bb16-4947-96cc-82a7584def6c.png)

