#include "../include/LidarDriver.h"
#include <stdexcept> // Gestione delle eccezioni

// Costruttore
LidarDriver::LidarDriver(double res) : resolution(res), buffer(BUFFER_DIM), index_old(0), index_new(-1) {
    if (resolution < 0.1 || resolution > 1.0) {
        throw std::invalid_argument("La risoluzione deve essere compresa tra 0.1 e 1.");
    }
}

// // Metodo ausiliario che incrementa un indice in modo circolare, mantenendolo entro il range [0, BUFFER_DIM - 1]
void LidarDriver::increment_index(size_t& index) {
    index = (index + 1) % BUFFER_DIM;
}

void LidarDriver::new_scan(const std::vector<double>& scan) {

    //il numero di scansioni che ci aspettiamo di rcevere dallo scan
    size_t expected_size = static_cast<size_t>(180 / resolution) + 1;

    //creo una copia dello scan su cui posso fare il resize
    std::vector<double> scan_copy = scan;

    // se la scansione ha un numero minore di dati della size prevista completo con 0
    if (scan_copy.size() < expected_size) { scan_copy.resize(expected_size, 0.0); }
    //se la scansione ha un numero maggiore di dati taglio i dati mancanti
    if (scan_copy.size() > expected_size) { scan_copy.resize(expected_size); }

    // Incrementa l'indice della scansione più vecchia se il buffer è pieno
    if (index_new != size_t(-1) && (index_new + 1) % BUFFER_DIM == index_old) {
        increment_index(index_old);
    }
    //salvo il vettore nella usa locazione all indice e incremento l' indice
    increment_index(index_new);
    buffer[index_new] = std::move(scan_copy);

    //buffer vuoto, inizializzo index_old
    if (index_new == size_t(-1)) {
        index_new = 0;
        index_old = 0;
    }
}

// Restituisce e rimuove la scansione più vecchia dal buffer
std::vector<double> LidarDriver::get_scan() {
    if (index_new == size_t(-1)) {
        throw std::runtime_error("Il buffer è vuoto.");
    }
    std::vector<double> oldest_scan = buffer[index_old];
    if (index_old == index_new) {
        index_new = size_t(-1);
    } else {
        increment_index(index_old);
    }
    return oldest_scan;
}

void LidarDriver::clear_buffer() {
    for (auto& scan : buffer) {
        scan.clear();
    }
    index_new = size_t(-1);
    index_old = 0;
}

double LidarDriver::get_distance(double angle) const {
    if (index_new == size_t(-1)) {
        throw std::runtime_error("Il buffer è vuoto.");
    }
    if (angle < 0 || angle > 180) {
        throw std::out_of_range("L'angolo è fuori dal range.");
    }
    size_t index = static_cast<size_t>(angle / resolution);
    const std::vector<double>& latest_scan = buffer.at(index_new);
    return latest_scan.at(index);
}

std::ostream& operator<<(std::ostream& os, const LidarDriver& lidar) {
    if (lidar.index_new == size_t(-1)) {
        os << "Buffer vuoto\n";
    } else {
        os << "Ultima scansione:\n";
        for (double value : lidar.buffer.at(lidar.index_new)) {
            os << value << " ";
        }
        os << "\n";
    }
    return os;
}
