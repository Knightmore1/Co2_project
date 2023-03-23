# Définition:

Le (ou la) Wi-Fi, aussi orthographié wifi1, est un ensemble de protocoles de communication sans fil régis par les normes du groupe IEEE 802.11 (ISO/CEI 8802-11). Un réseau Wi-Fi permet de relier par ondes radio plusieurs appareils informatiques (ordinateur, routeur, smartphone, modem Internet, etc.) au sein d'un réseau informatique afin de permettre la transmission de données entre eux.

# Installation: 
--------------------------------------------------------------------------------------
## __Prérequis de l'installation:__
* __Avoir installer Visual Studio Code__
* __Brancher son ESP32 Saola à son ordinateur en USB.__
* __Avoir télécharger les [extentions](https://github.com/Knightmore1/Co2_project/wiki/Extention) C++: "C/C++", "C/C++ Entension Pack", "C/C++ Theme", "C/C++ Runner.__
* __Avoir télécharger l'[extention](https://github.com/Knightmore1/Co2_project/wiki/Extention) "PlatformIo".__
* __Avoir télécharger le logiciel Putty.__
--------------------------------------------------------------------------------------
### Pour que la communication entre le broker MQTT et l'esp 32 Saola se fasse il faut:

__1. Télécharger le fichier en entier [Wifi_v2](https://github.com/Knightmore1/Co2_project/tree/WiFi/Wifi_v2) sur vos documents.__  
![exemle1](https://user-images.githubusercontent.com/123626872/227144513-354c106e-7f62-4f82-b094-bb3e900e0597.PNG)  

__2. Ouvrir avec visual Studio Code et ouvrir le dossier Wifi_v2.__  
![exemple2](https://user-images.githubusercontent.com/123626872/227149227-5e127a41-a947-4fb9-97ef-be3adb7d5b4f.png)  

__3. Sélectionner "src" et selectionner le fichier "main.cpp", une fois le fichier ouvert il faut remplir l'adresse IP de la raspberry sur la ligne 7.__  
![Exemple3](https://user-images.githubusercontent.com/123626872/227161662-25c5f4be-b521-4076-878c-72db647508b0.PNG)  

