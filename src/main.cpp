#include "../include/LidarDriver.h"

int main() {

    try {

        LidarDriver lidar(1.0);
        // Stampo buffer vuoto
        std::cout << "Buffer vuoto:\n" << lidar << std::endl;
        // Scansione test
        std::vector<double> scan1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
        std::vector<double> scan2 = {10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
        // Aggiungo scan1 al buffer e stampo
        std::cout << "Aggiungo scan1...\n";
        lidar.new_scan(scan1);
        std::cout << "Buffer dopo l'aggiunta di scan1:\n" << lidar << std::endl;
        // Aggiungo scan2 al buffer e stampo
        std::cout << "Aggiungo scan2...\n";
        lidar.new_scan(scan2);
        std::cout << "Buffer dopo l'aggiunta di scan2:\n" << lidar << std::endl;

        // Test angolo
        double angle = 7.0;
        std::cout << "Distanza all'angolo " << angle << " nella scansione piu' recente: " << lidar.get_distance(angle) << std::endl;

        // Test scansione piu vecchia
        std::cout << "Recupero la scansione piu' vecchia...\n";
        std::vector<double> oldest_scan = lidar.get_scan();
        std::cout << "Scansione piu' vecchia:\n";
        for (double value : oldest_scan) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        std::cout << "Buffer dopo la rimozione della scansione piu' vecchia:\n" << lidar << std::endl;

        // Test clear
        std::cout << "Testo la funzione clear_buffer()...\n";
        lidar.clear_buffer();
        std::cout << "Buffer dopo clear_buffer():\n" << lidar << std::endl;


    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << std::endl;
    }
    
    return 0;
}