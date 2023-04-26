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

__2. Ouvrir avec platformIO (dans visual studio code) le dossier [ThreadAlertV2](https://github.com/Knightmore1/Co2_project/tree/Mesure-CO2/affichage/ThreadAlertV2) comme projet.__  
![platformIOIcon](https://user-images.githubusercontent.com/48868173/234328431-71eb40f1-6621-4fce-a47e-b68e263c38d7.png)  
