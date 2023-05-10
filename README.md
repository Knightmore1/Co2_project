# Co2_project


## Présentation du projet


> L’inhalation d’aérosols contenant des virus SARS-CoV-2 est un des trois modes de transmission de la COVID-19. Elle se produit essentiellement dans les espaces clos. Les aérosols (des gouttelettes de diamètre inférieur à 0,01 mm) peuvent rester suspendus dans l’air pendant plusieurs heures. 
Contrairement aux gouttelettes plus grosses, les aérosols peuvent être transportés sur des distances nettement supérieures à 2 m. 
Plusieurs moyens sont particulièrement efficaces pour limiter l’inhalation d’aérosols : le port du masque, la diminution de la densité́ humaine et l’aération des locaux. L’aération consiste à remplacer l’air de la pièce par de l’air extérieur. 

> Selon les autorités de santé, si une salle de classe dépasse un taux de dioxyde de carbone de 800 ppm (parties par millions), cela signifie que l’air est mal renouvelé, que le virus peut donc être présent en grande quantité, et qu’il faut aérer la pièce. C’est pourquoi, avant la rentrée scolaire, le ministère de l’Éducation nationale, « a recommandé fortement » d’équiper les salles de classe avec des détecteurs de CO2. 

![image](https://user-images.githubusercontent.com/123626866/224345326-52176d4f-dcee-4446-b97a-508caec78b3c.png)
> __Voici l'objectif du projet:__  

![Capture](https://user-images.githubusercontent.com/123626872/236166087-a19322f3-87a9-460f-8f74-edd6a1c08cd4.PNG)


## Mise en place du système:

__Le [broker](https://github.com/Knightmore1/Co2_project/blob/MQTT/README.md) est un élément essentiel de l'architecture du projet. Il permet la mise en tampon des données fournies par les différents capteurs des salles. La [base de données](https://github.com/Knightmore1/Co2_project/blob/Broker/Acc%C3%A8s-BDD/README.md) permet de stocker les différentes mesures des différents capteurs, ainsi ces dernières seront récuperées pour en faire de la visualisation de courbes via [IHM](https://github.com/Knightmore1/Co2_project/blob/Supervision/Visu-Courbes/Import-EdT/README.md). Les cartes électroniques [ESP32](https://github.com/Knightmore1/Co2_project/blob/Mesure-CO2/affichage/README.md) installés dans chaque salle permet de récupéré les données des capteurs. Ces données sont envoyé en [trasmition sans fil](https://github.com/Knightmore1/Co2_project/blob/WiFi/README.md).__  

## Matériel:

__- ESP32-S2-Saola: carte de développement de petite taille produite par Espressif. La plupart des broches d'E/S sont réparties sur les en-têtes de broches des deux côtés pour faciliter l'interfaçage. Les développeurs peuvent soit connecter des périphériques avec des fils de connexion, soit monter ESP32-S2-Saola-1 sur une planche à pain.__  
__- Capteur CO2:__  
__- Capteur d'humidité:__  
__- Capteur de température:__  
__- RaspberryPi:__  

## Coût:
