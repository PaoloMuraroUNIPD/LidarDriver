#ifndef LIDAR_DRIVER_H
#define LIDAR_DRIVER_H

#include <iostream>
#include <vector>

constexpr size_t BUFFER_DIM = 10; //Dimensione massima del buffer circolare

class LidarDriver {

    private:

        double resolution; // Risoluzione angolare (tra 0.1° e 1°)
        std::vector<std::vector<double>> buffer; // Buffer circolare delle scansioni
        size_t index_old; // Indice della scansione più vecchia
        size_t index_new; // Indice della scansione più recente

        // Metodo ausiliario che incrementa un indice in modo circolare
        void increment_index(size_t& index);

    public:

        // Costruttore
        explicit LidarDriver(double res);

        // Aggiunge una nuova scansione al buffer
        void new_scan(const std::vector<double>& scan); 

        // Restituisce e rimuove la scansione più vecchia
        std::vector<double> get_scan();

        // Elimina tutte le scansioni dal buffer
        void clear_buffer();

        // Restituisce la distanza per un dato angolo
        double get_distance(double angle) const;

        // Overloading dell'operatore di output per stampare l'ultima scansione
        friend std::ostream& operator<<(std::ostream& os, const LidarDriver& lidar);

};

#endif
