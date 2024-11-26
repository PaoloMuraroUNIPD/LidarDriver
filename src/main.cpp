#include "../include/LidarDriver.h"
//
//int main() {
//
//    try {
//
//        LidarDriver lidar(1);
////         Stampo buffer vuoto
//        std::cout << "Buffer vuoto:\n" << lidar << std::endl;
//        // Scansione test
//        std::vector<double> scan1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
//        std::vector<double> scan2 = {10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
//        std::vector<double> scan3 = {2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 1.0};
//        std::vector<double> scan4 = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0, 10.0};
//        std::vector<double> scan5 = {3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 1.0, 2.0};
//        std::vector<double> scan6 = {8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0, 10.0, 9.0};
//        std::vector<double> scan7 = {4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 1.0, 2.0, 3.0};
//        std::vector<double> scan8 = {7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0, 10.0, 9.0, 8.0};
//        std::vector<double> scan9 = {5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 1.0, 2.0, 3.0, 4.0};
//        std::vector<double> scan10 = {6.0, 5.0, 4.0, 3.0, 2.0, 1.0, 10.0, 9.0, 8.0, 7.0};
//        std::vector<double> scan11 = {6.0, 7.0, 8.0, 9.0, 10.0, 1.0, 2.0, 3.0, 4.0, 5.0};
//        std::vector<double> scan12 = {5.0, 4.0, 3.0, 2.0, 1.0, 10.0, 9.0, 8.0, 7.0, 6.0};
//        // Aggiungo scan1 al buffer e stampo
//        std::cout << "Aggiungo scan1...\n";
//        lidar.new_scan(scan1);
//        std::cout << "Buffer dopo l'aggiunta di scan1:\n" << lidar << std::endl;
//        // Aggiungo scan2 al buffer e stampo
//        std::cout << "Aggiungo scan2...\n";
//        lidar.new_scan(scan2);
//        lidar.new_scan(scan3);
//        lidar.new_scan(scan4);
//        lidar.new_scan(scan5);
//        lidar.new_scan(scan6);
//        lidar.new_scan(scan7);
//        lidar.new_scan(scan8);
//        lidar.new_scan(scan9);
//        lidar.new_scan(scan10);
//        lidar.new_scan(scan11);
//        lidar.new_scan(scan12);
//        std::cout << "Buffer dopo l'aggiunta di scan2:\n" << lidar << std::endl;
//
//        // Test angolo
//        double angle = 7.0;
//        std::cout << "Distanza all'angolo " << angle << " nella scansione piu' recente: " << lidar.get_distance(angle)
//                  << std::endl;
//
//        // Test scansione piu vecchia
//        std::cout << "Recupero la scansione piu' vecchia...\n";
//        std::vector<double> oldest_scan = lidar.get_scan();
//        std::cout << "Scansione piu' vecchia:\n";
//        for (double value: oldest_scan) {
//            std::cout << value << " ";
//        }
//        std::cout << std::endl;
//        std::cout << "Buffer dopo la rimozione della scansione piu' vecchia:\n" << lidar << std::endl;
//
//        // Test clear
//        std::cout << "Testo la funzione clear_buffer()...\n";
//        lidar.clear_buffer();
//        std::cout << "Buffer dopo clear_buffer():\n" << lidar << std::endl;
//
//
//    } catch (const std::exception &e) {
//        std::cerr << "Errore: " << e.what() << std::endl;
//    }
//
//
//    return 0;
//}

#include "../include/LidarDriver.h"
#include <iostream>
#include <vector>

void print_menu() {
    std::cout << "Menu:\n";
    std::cout << "1. Aggiungere una nuova scansione\n";
    std::cout << "2. Ottenere la distanza da un angolo\n";
    std::cout << "3. Recuperare la scansione più vecchia\n";
    std::cout << "4. Pulire il buffer\n";
    std::cout << "5. Stampare il buffer corrent\n";
    std::cout << "6. Esci\n";
    std::cout << "Scelta: ";
}

int main() {
    double resolution;
    std::cout << "Inserisci la risoluzione (tra 0.1° e 1°): ";
    std::cin >> resolution;

    try {
        if (resolution < 0.1 || resolution > 1.0) {
            throw std::out_of_range("La risoluzione deve essere compresa tra 0.1° e 1°.");
        }

        LidarDriver lidar(resolution); // supponiamo un buffer di dimensione 12
        int scelta;

        while (true) {
            print_menu();
            std::cin >> scelta;

            switch (scelta) {
                case 1: {
                    std::vector<double> nuova_scansione;
                    double valore;
                    std::cout << "Inserisci i valori della nuova scansione (terminare con un valore negativo): ";
                    while (std::cin >> valore && valore >= 0) {
                        nuova_scansione.push_back(valore);
                    }
                    lidar.new_scan(nuova_scansione);
                    std::cout << "Scansione aggiunta.\n";
                    break;
                }
                case 2: {
                    double angolo;
                    std::cout << "Inserisci l'angolo: ";
                    std::cin >> angolo;
                    try {
                        double distanza = lidar.get_distance(angolo);
                        std::cout << "Distanza all'angolo " << angolo << " nella scansione più recente: " << distanza
                                  << "\n";
                    } catch (const std::exception &e) {
                        std::cerr << "Errore: " << e.what() << std::endl;
                    }
                    break;
                }
                case 3: {
                    try {
                        std::vector<double> scan = lidar.get_scan();
                        std::cout << "Scansione più vecchia:\n";
                        for (double value: scan) {
                            std::cout << value << " ";
                        }
                        std::cout << std::endl;
                    } catch (const std::exception &e) {
                        std::cerr << "Errore: " << e.what() << std::endl;
                    }
                    break;
                }
                case 4: {
                    lidar.clear_buffer();
                    std::cout << "Buffer pulito.\n";
                    break;
                }
                case 5: {
                    std::cout << "Buffer corrente:\n" << lidar << std::endl;
                    break;
                }
                case 6: {
                    std::cout << "Arrivederci.\n";
                    return 0;
                }
                default: {
                    std::cout << "Scelta non valida, riprova.\n";
                    break;
                }
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Errore: " << e.what() << std::endl;
        return 1;
    }
}
