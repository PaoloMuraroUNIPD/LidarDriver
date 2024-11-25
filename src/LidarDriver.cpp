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
LidarDriver::LidarDriver(double res) {
    //inizializza il buffer con la sua dimensione
    buffer.resize(BUFFER_DIM);
    resolution = res;
    //inizializza le varie scansioni con il numero giusto di angoli
    for (int i = 0; i < BUFFER_DIM; ++i) {
        buffer.at(i).resize((180 / res)+1);
    }
    //inizializza gli indici
    index_new = 0;
    index_old = 0;
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
    index_new = 0;
    index_old = 0;
}

double LidarDriver::get_distance(double angle) {
    return 0;
}

std::ostream &operator<<(std::ostream &os, const LidarDriver &lidar) {

    if (!lidar.buffer.empty()) {
        os << "Ultima scansione:\n";
        for (double scansione: lidar.buffer.at(lidar.index_new)) {
            os << scansione << " ";
        }
    } else {
        os << "Buffer vuoto";
    }
    os << std::endl;
    std::cout << lidar.index_new;

    return os;
}


//questa funzione accetta come argomento il riferimento a un index e incrementa il suo contenuto in modo circolare
void LidarDriver::increment_index(size_t *index) {
    ++(*index);
    if(*index >= BUFFER_DIM)
        *index = 0;
}
