// implementazione della classe e dei metodi
#include <iostream>
#include <vector>

#include "../include/LidarDriver.h"

//
//class LidarDriver {
//
//    private:
//
//        double resolution;
//        std::vector<std::vector<double>> buffer;
//
//        //dimensinoe massima del buffer
//        size_t size;
//        //numero di scansioni nel buffer
//        size_t count;
//        //indice scansione, punta all ultima scansione del lidar
//        size_t index;
//
//        /* boolean isEmpty() { return count == 0 } */
//
//    public:
//
//        LidarDriver() = delete;
//
//        LidarDriver(double res, size_t buffer_dim) {
//
//            resolution = res;
//            size = buffer_dim;
//            count = 0;
//            index = 0;
//        }
//
//        void new_scan(const std::vector<double>& scan) {
//
//            /* parte alta di 181 (numero di scansioni a 1) moltiplicato per la risoluzione,
//            il numero di scansioni che ci aspettiamo di rcevere dallo scan */
//            true_size = (181/resolution) + 1;
//
//            // se la scansione ha un numero minore di dati della size prevista completo con 0
//            if (scan.size() < true_size) { scan.resize(true_size, 0); }
//            //se la scansione ha un numero maggiore di dati taglio i dati mancanti
//            if (scan.size() > true_size) { scan.resize(true_size);
//
//            //aggiungo il nuovo vettore
//            if (index < (size - 1)) {
//                //mette scan nel vettore buffer nella posizione dell' index sucessivo
//                index = index + 1;
//                //dovrebbe mettere tutti i valori della scan in buffer[(index + 1)]
//                for (int i : scan) buffer[index].push_back(i);
//            }
//            else
//            {
//                index = 0;
//                for (int i : scan) buffer[index].push_back(i);
//            }
//            //se il buffer è non gia pieno, incrementa count
//            if (count < size) { count = count + 1; }
//        }
//
//        //elimina tutte le scan
//        void clear_buffer(void) {
//            buffer.clear();
//            count = 0;
//            index = 0;
//        }
//}
LidarDriver::LidarDriver(double res, size_t buffer_dim) {
    resolution = res;
    size = buffer_dim;
    count = 0;
    index = 0;

}

void LidarDriver::new_scan(const std::vector<double> &scan) {
//              PARTE SCRITTA DA ALBERTO
//            /* parte alta di 181 (numero di scansioni a 1) moltiplicato per la risoluzione,
//            il numero di scansioni che ci aspettiamo di rcevere dallo scan */
//            true_size = (181/resolution) + 1;
//
//            // se la scansione ha un numero minore di dati della size prevista completo con 0
//            if (scan.size() < true_size) { scan.resize(true_size, 0); }
//            //se la scansione ha un numero maggiore di dati taglio i dati mancanti
//            if (scan.size() > true_size) { scan.resize(true_size);
//
//            //aggiungo il nuovo vettore
//            if (index < (size - 1)) {
//                //mette scan nel vettore buffer nella posizione dell' index sucessivo
//                index = index + 1;
//                //dovrebbe mettere tutti i valori della scan in buffer[(index + 1)]
//                for (int i : scan) buffer[index].push_back(i);
//            }
//            else
//            {
//                index = 0;
//                for (int i : scan) buffer[index].push_back(i);
//            }
//            //se il buffer è non gia pieno, incrementa count
//            if (count < size) { count = count + 1; }
//        }
}

std::vector<double> LidarDriver::get_scan() {
    return std::vector<double>();
}

void LidarDriver::clear_buffer() {
            buffer.clear();
            count = 0;
            index = 0;
}

double LidarDriver::get_distance(double angle) {
    return 0;
}

std::ostream &operator<<(std::ostream &os, const LidarDriver &lidar) {
    os <<"Ciao";
    return os;
}
