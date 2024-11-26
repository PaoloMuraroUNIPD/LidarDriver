#include "../include/LidarDriver.h"
#include <stdexcept> // Gestione delle eccezioni

//
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

// Costruttore
LidarDriver::LidarDriver(double res) : resolution(res), buffer(BUFFER_DIM), size(BUFFER_DIM), count(0), index_old(0), index_new(0) {
    if (resolution < 0.1 || resolution > 1.0) {
        throw std::invalid_argument("La risoluzione deve essere compresa tra 0.1 e 1.");
    }
}

// // Metodo ausiliario che incrementa un indice in modo circolare, mantenendolo entro il range [0, BUFFER_DIM - 1]
// ******* Ho sostituito il puntatore con un riferimento e ho reso l'operazione più leggibile
void LidarDriver::increment_index(size_t& index) {
    index = (index + 1) % BUFFER_DIM;
}

// ****** new scan provvisorio. Usato per testare la classe
// NB. cambiare nel file 'LidarDrive.h' e mettere const std::vector<double>& scan tra parentesi
void LidarDriver::new_scan() {
    std::vector<double> scan = {
        0.72, 0.34, 1.57, 0.11, 1.98, 1.22, 0.89, 1.01, 1.43, 1.03,
        1.88, 0.51, 1.71, 0.45, 0.99, 1.35, 0.84, 1.44, 0.26, 1.62,
        1.17, 0.05, 1.90, 0.61, 0.20, 1.65, 0.37, 1.09, 1.55, 0.23,
        1.47, 0.10, 1.78, 0.90, 1.53, 0.30, 1.76, 1.06, 0.59, 1.27,
        0.14, 1.81, 1.49, 0.72, 1.66, 0.33, 1.38, 1.00, 0.43, 0.28,
        1.46, 0.16, 1.63, 0.31, 1.25, 1.07, 0.95, 1.37, 0.18, 1.68,
        0.46, 1.21, 1.52, 0.19, 1.83, 0.66, 1.29, 0.92, 0.35, 1.12,
        1.75, 0.54, 1.33, 0.01, 1.85, 0.58, 0.48, 1.20, 1.11, 0.07,
        1.87, 0.64, 0.15, 1.45, 0.77, 1.24, 0.02, 0.88, 1.82, 0.70,
        1.40, 0.08, 1.77, 0.93, 1.05, 0.12, 1.13, 0.42, 1.34, 0.03,
        1.19, 0.62, 0.17, 1.56, 1.08, 0.50, 1.64, 0.40, 0.96, 1.14,
        0.27, 1.86, 0.55, 1.41, 0.71, 0.21, 1.50, 0.04, 0.68, 1.84,
        0.47, 1.31, 1.10, 0.25, 1.69, 0.91, 1.28, 0.49, 1.73, 0.35,
        0.98, 1.60, 0.41, 1.23, 0.09, 1.67, 0.52, 1.42, 0.32, 1.58,
        0.67, 1.30, 0.06, 1.79, 0.24, 1.48, 0.65, 1.36, 0.13, 1.80,
        1.04, 0.56, 1.59, 0.22, 1.72, 0.74, 1.26, 0.29, 1.51, 0.81,
        0.36, 1.18, 0.60, 1.39, 0.57, 1.15, 0.38, 1.70, 1.02, 0.73,
        1.89, 0.53, 1.32, 0.44, 2.00, 0.78, 1.16, 0.69, 1.74, 1.61,
        0.09
    };
    buffer[index_new] = scan;
    increment_index(index_new);
    if (count < size) {
        ++count;
    } else {
        increment_index(index_old);
    }
}

// Restituisce e rimuove la scansione più vecchia dal buffer
std::vector<double> LidarDriver::get_scan() {
    if (count == 0) {
        throw std::runtime_error("Il buffer è vuoto.");
    }
    std::vector<double> oldest_scan = buffer[index_old];
    increment_index(index_old);
    --count;
    return oldest_scan;
}

void LidarDriver::clear_buffer() {
    for (auto& scan : buffer) {
        scan.clear();
    }
    count = 0;
    index_new = 0;
    index_old = 0;
}

// *****Ho corretto un errore e aggiunto la gestione delle eccezioni.
double LidarDriver::get_distance(double angle) const {
    if (count == 0) {
        throw std::runtime_error("Il buffer è vuoto.");
    }
    if (angle < 0 || angle > 180) {
        throw std::out_of_range("L'angolo è fuori dal range.");
    }
    size_t last_index = (index_new == 0) ? (BUFFER_DIM - 1) : (index_new - 1);
    size_t index = static_cast<int>(angle / resolution);
    const std::vector<double>& latest_scan = buffer.at(last_index);
    return latest_scan.at(index);
}

//******** index_new puntava alla prossima scansione
//******** migliorato output
std::ostream& operator<<(std::ostream& os, const LidarDriver& lidar) {
    if (lidar.count == 0) {
        os << "Buffer vuoto\n";
    } else {
        os << "Ultima scansione:\n";
        size_t last_index = (lidar.index_new == 0) ? (BUFFER_DIM - 1) : (lidar.index_new - 1);
        for (double value : lidar.buffer.at(last_index)) {
            os << value << " ";
        }
        os << "\n";
    }
    return os;
}

// void LidarDriver::new_scan(const std::vector<double> &scan) {
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
// }