# Définition:
Le (ou la) Wi-Fi, aussi orthographié wifi1, est un ensemble de protocoles de communication sans fil régis par les normes du groupe IEEE 802.11 (ISO/CEI 8802-11). Un réseau Wi-Fi permet de relier par ondes radio plusieurs appareils informatiques (ordinateur, routeur, smartphone, modem Internet, etc.) au sein d'un réseau informatique afin de permettre la transmission de données entre eux.  

### Cette partie est dédiée à la transmition des données des capteurs vers le broker [MQTT](https://github.com/Knightmore1/Co2_project/tree/MQTT) en liason sans fil.  

__Vous trouvez dans cette partie des différentes versions (étapes) du programme wifi.__  
__- Le dossier WifiV1 permet à l'ESP32 Saola de se connecter au réseau wifi `AP_SNIR`, et de prévenir si l'ESP est connectée.__  
__- Le dossier WifiV2 permet en plus de se connecter au broker [MQTT](https://github.com/Knightmore1/Co2_project/tree/MQTT).__  
__- Le dossier WifiV3 permet en plus d'envoyer une donnée sur le topic "Humidity".__  

__Le derniere version (`wifi_V3`) à été mergé avec le code `TheardAlert` pour s'appeler [`TheardAlertV2`](https://github.com/Knightmore1/Co2_project/tree/Mesure-CO2/affichage/ThreadAlertV2). Il peut envoyé les données des capteurs vers le broker MQTT sous différents [topics](https://github.com/Knightmore1/Co2_project/wiki/MQTT).__  
