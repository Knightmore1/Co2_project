# Base de données du projet  

# Cette partie est dédiée à la base de données ainsi que son accès, celà sera fait en plusieurs étapes :  


* Recherche des besoins 
    * Système
    * données à enregistrer

* Structure de la base de données
    * nombre de table 
    * structure des tables
    * Liaisons
* Choix installation Base de données
    * où             
    * Comment y accéder
* Effectuer les test nécessaires
    * Tests de connexion
    * Remplissage automatique  





1) Recherche des besoins  

   Pour cette partie du projet, une machine virtuelle avec un système d'exploitation Linux Ubuntu sera utilisée pour installer le serveur de base de données. 
   ![image](https://user-images.githubusercontent.com/123626866/234318883-546185b4-316d-44c9-aa7c-8b5761562cd5.png)  
   ![image](https://user-images.githubusercontent.com/123626866/234318315-93b9b2d4-cf08-408d-b889-2fb613a6cef8.png)


   
   Sur cette dernière, un serveur de base de données de type Mariadb sera installé, avec une base de données dédiée au projet.
   ![image](https://user-images.githubusercontent.com/123626866/234317767-a88e9d17-dde5-4bd9-b9ba-8aa3fd643587.png)
   
   
2) Structure de la base de données  
     
     

  
    
      
        
Schéma relationnel de la base de données du projet:  

![image](https://user-images.githubusercontent.com/123626866/227238277-06540518-b3d8-4149-90a8-343847ba7fb5.png)




__Installation d'un serveur de base de données sur une machine virtuelle Linux:__

1. Avoir un ordinateur connéctée à internet avec une machine virtuelle installée 

2. Pour installer le serveur de base de données, il faut taper la commande suivante:
![image](https://user-images.githubusercontent.com/123626866/234315252-6dbf193c-ca4a-4b12-8cc7-70fb505b902a.png)

La commande permet d'installer le serveur de base de données nommé mariaDB.  
SERVEUR INSTALLE!!!  

Pour s'y connecter, il faut utiliser la commande :

![image](https://user-images.githubusercontent.com/123626866/226945101-da09fa9b-feea-4578-8153-7069b8830ccf.png)

cette commande permet d'accéder au serveur avec comme utilisateur root. (Utilisateur par défaut du serveur)

A partir de ce moment là, on peut créer et gérer des bases de données.
Pour connaitre la syntaxe des commandes SQL, consulter ce site https://sql.sh/























