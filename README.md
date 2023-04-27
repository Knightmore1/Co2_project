# CO2_Projects
BTS Project

## Cette partie est dédiée à l'acquisition l’affichage et l'horodatage qui va se découper en plusieurs parties:
 
1. Mise en place du matériel dans les salles
   - Mise en place de la Raspberry pi
   - Mise en place de la Raspberry pi
   - Mise en place du capteur
 
2. Récupération de la température, l'humidité et le taux de CO2
   - Mise en place de la Raspberry pi
   - Création d'un programme qui récupère les données du capteur sur la Raspberry pi
 
3. Affichage des mesures sur l’écran LED
   - Mise en place de la Raspberry pi
   - Création d'un programme qui affiche les mesures sur l’écran LED
 
4. Puis mise en place de l'horodatage
   - Mise en place de la Raspberry pi
   - Création du fichier contenant les mesures ainsi que l'horodatage qui sera envoyé a la base de données
--------------------------------------------------------------------------------------
# Installation: 

## __Prérequis de l'installation:__
* __Avoir installer Visual Studio Code__
* __Brancher son ESP32 Saola à son ordinateur en USB.__
* __Avoir télécharger les [extentions](https://github.com/Knightmore1/Co2_project/wiki/Extention) C++: "C/C++", "C/C++ Entension Pack", "C/C++ Theme", "C/C++ Runner.__
* __Avoir télécharger l'[extention](https://github.com/Knightmore1/Co2_project/wiki/Extention) "PlatformIo" et le parametré.__
* __Avoir télécharger le logiciel Putty.__

### Pour que la communication entre le broker MQTT et l'ESP 32 Saola se fasse il faut:

__1. Télécharger le dossier [ThreadAlertV2](https://github.com/Knightmore1/Co2_project/tree/Mesure-CO2/affichage/ThreadAlertV2)__  
![image](https://user-images.githubusercontent.com/123626872/234809282-34dcf852-a63d-4f11-81c8-6511b5d00247.png)  

__2. Pour ouvrir le dossier [ThreadAlertV2](https://github.com/Knightmore1/Co2_project/tree/Mesure-CO2/affichage/ThreadAlertV2)__  
 __2.1 Ouvrir le fichier `ThreadAlertV2.zip` dans l'explorateur de fichier et le décompresser là où vous souhaitez dans votre explorateur de fichier__  
 __2.2 Ouvrir avec platformIO (dans visual studio code) le dossier [ThreadAlertV2](https://github.com/Knightmore1/Co2_project/tree/Mesure-CO2/affichage/ThreadAlertV2) comme projet.__  
![platformIOIcon](https://user-images.githubusercontent.com/48868173/234328431-71eb40f1-6621-4fce-a47e-b68e263c38d7.png)  

__3. Sélectionner "src" et selectionner le fichier "main.cpp", une fois le fichier ouvert il faut remplir l'adresse IP de la raspberry sur la ligne 7.__  
![Exemple3](https://user-images.githubusercontent.com/123626872/227161662-25c5f4be-b521-4076-878c-72db647508b0.PNG)  

__4. Mettre le programme dans l'ESP32 Saola:__  
  __4.1 Sélectionner ![Exemple4](https://user-images.githubusercontent.com/123626872/227180263-cd8b45f5-ed71-45cf-91c0-3e2124e82e99.PNG) dans la barre d'état pour build le programme. Si il n'y a pas d'erreur à la compilation du programme, vous pouvez passer à la prochaine étapes.__  
![Capture10](https://user-images.githubusercontent.com/123626872/234802500-afb3f2f0-212e-4ca1-818f-197106f6f919.PNG)  
  __4.2 Sélectionner ![Exemple5](https://user-images.githubusercontent.com/123626872/227181478-e3b0f74e-22eb-443e-b00c-eab24a14f7b4.PNG) dans la barre d'état pour mettre le code compiler dans la carte ESP32.__  
![exemple9](https://user-images.githubusercontent.com/123626872/234801701-226b50d0-b3ab-42da-afd6-8c25e5c78665.PNG)  
 __4.3 Sélectionner![exemple8](https://user-images.githubusercontent.com/123626872/234795098-a2dc5ee5-2152-4587-88e3-4ef397174368.PNG) dans la barre d'état pour éxecuter le programme et afficher le terminal de visual studio.__  

__Si vous ne souhaitez pas utiliser le terminal fournis directement avec visual Studio vous pouvez vous connecter en série avec le logiciel "[Putty](https://github.com/Knightmore1/Co2_project/wiki/Putty)"__  
