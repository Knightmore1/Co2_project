#include <iostream>
#include <ctime>

class WiFi
{
public:
    // Méthode publique pour obtenir la date actuelle
    std::string getDate()
    {
        // Obtenir la date actuelle à partir de la fonction time()
        time_t now = time(0);

        // Convertir la date actuelle en une structure tm
        struct tm* time_info = localtime(&now);

        // Convertir la structure tm en une chaîne de caractères au format AAAA-MM-JJ
        char date_buffer[11];
        strftime(date_buffer, 11, "%Y-%m-%d", time_info);

        // Retourner la date sous forme de chaîne de caractères
        return std::string(date_buffer);
    }

    // Méthode publique pour obtenir l'heure actuelle
    std::string getTime()
    {
        // Obtenir l'heure actuelle à partir de la fonction time()
        time_t now = time(0);

        // Convertir l'heure actuelle en une structure tm
        struct tm* time_info = localtime(&now);

        // Convertir la structure tm en une chaîne de caractères au format HH:MM:SS
        char time_buffer[9];
        strftime(time_buffer, 9, "%H:%M:%S", time_info);

        // Retourner l'heure sous forme de chaîne de caractères
        return std::string(time_buffer);
    }
};

int main()
{
    // Instancier un objet de la classe WiFi
    WiFi wifi;

    // Obtenir la date actuelle à partir de l'objet wifi
    std::string date = wifi.getDate();

    // Obtenir l'heure actuelle à partir de l'objet wifi
    std::string time = wifi.getTime();

    // Afficher la date et l'heure actuelles séparément
    std::cout << "La date actuelle est : " << date << std::endl;
    std::cout << "L'heure actuelle est : " << time << std::endl;

    // Retourner 0 pour indiquer que le programme s'est terminé avec succès
    return 0;
}
