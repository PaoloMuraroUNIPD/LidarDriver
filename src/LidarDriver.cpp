#include "../include/LidarDriver.h"
#include <stdexcept>



/**
 * @brief Costruttore della classe LidarDriver.
 *
 * Questo costruttore inizializza un oggetto LidarDriver impostando la risoluzione
 * e creando un buffer di dimensione definita. Inoltre, inizializza gli indici
 * per la gestione del buffer circolare.
 *
 * @param res La risoluzione del Lidar. Deve essere compresa tra 0.1 e 1.0.
 *
 * @throw std::invalid_argument Se la risoluzione non è compresa nel range [0.1, 1.0].
 */
LidarDriver::LidarDriver(double res) : resolution(res), buffer(BUFFER_DIM), index_old(0), index_new(0) {
    if (resolution < 0.1 || resolution > 1.0) {
        throw std::invalid_argument("La risoluzione deve essere compresa tra 0.1 e 1.");
    }
}


/**
 * @brief Incrementa l'indice fornito in modo circolare.
 *
 * Questo metodo prende un riferimento a un indice e lo incrementa di una unità.
 * Se l'indice raggiunge la dimensione del buffer (BUFFER_DIM), viene riportato a zero.
 *
 * @param[in,out] index Riferimento all'indice da incrementare.
 */
void LidarDriver::increment_index(size_t &index) {
    index = (index + 1) % BUFFER_DIM;

}

/**
 * @brief Aggiunge una nuova scansione al buffer e ridimensiona la nuova scansione se necessario.
 *
 * La funzione determina il numero di letture atteso in base alla risoluzione dell'angolo,
 * quindi aggiunge una nuova scansione al buffer. Se il buffer nella posizione corrente non è vuoto,
 * l'indice viene incrementato per fare spazio alla nuova scansione. Se l'indice corrente raggiunge
 * l'indice della scansione più vecchia, anche l'indice della scansione più vecchia viene incrementato.
 *
 * @param scan La nuova scansione che deve essere aggiunta al buffer.
 */
void LidarDriver::new_scan(const std::vector<double> &scan) {

    //il numero di scansioni che ci aspettiamo di rcevere dallo scan
    size_t expected_size = static_cast<size_t>(180 / resolution) + 1;

    //creo una copia dello scan su cui posso fare il resize
    if (!(buffer.at(index_new).empty())) {
        increment_index(index_new);
        if (index_new == index_old) {
            increment_index(index_old);
        }
    }

    buffer.at(index_new) = scan;
    buffer.at(index_new).resize(expected_size, 0);

}

/**
 * @brief Restituisce e rimuove la scansione più vecchia dal buffer del LiDAR.
 *
 * La funzione rimuove la scansione più vecchia dal buffer, la restituisce e
 * aggiorna l'indice della scansione più vecchia. Se il buffer è vuoto,
 * viene generata un'eccezione std::runtime_error.
 *
 * @return Un vettore di double rappresentante la scansione più vecchia.
 * @throws std::runtime_error Se il buffer è vuoto.
 */
std::vector<double> LidarDriver::get_scan() {
    if (buffer.at(index_new).empty()) {
        throw std::runtime_error("Il buffer è vuoto.");
    }
    std::vector<double> oldest_scan = buffer.at(index_old);
    buffer.at(index_old).clear();

    if (index_old != index_new) increment_index(index_old);

    return oldest_scan;
}

/**
 * @brief Elimina tutte le scansioni presenti nel buffer e reinizializza gli indici.
 *
 * Il metodo scorre attraverso tutte le scansioni presenti nel buffer e le elimina.
 * Successivamente, gli indici index_new e index_old vengono reinizializzati a 0,
 * indicando che il buffer è vuoto.
 */
void LidarDriver::clear_buffer() {
    for (auto &scan: buffer) {
        scan.clear();
    }
    index_new = 0; // Buffer vuoto
    index_old = 0;
}

/**
 * @brief Restituisce la distanza per un dato angolo.
 *
 * Questa funzione calcola l'indice appropriato nel buffer a partire dall'angolo specificato
 * e restituisce la distanza corrispondente. Se il buffer è vuoto, viene generata un'eccezione
 * di tipo `std::runtime_error`. Se l'angolo è fuori dal range (0-180 gradi), viene generata
 * un'eccezione di tipo `std::out_of_range`.
 *
 * @param angle L'angolo per il quale si vuole ottenere la distanza, in gradi. Deve essere compreso tra 0 e 180.
 * @return La distanza corrispondente all'angolo specificato.
 * @throws std::runtime_error se il buffer è vuoto.
 * @throws std::out_of_range se l'angolo è fuori dal range consentito.
 */
double LidarDriver::get_distance(double angle) const {
    if (buffer.at(index_new).empty()) {
        throw std::runtime_error("Il buffer è vuoto.");
    }
    if (angle < 0 || angle > 180) {
        throw std::out_of_range("L'angolo è fuori dal range.");
    }

    size_t index = static_cast<size_t> ((angle / resolution) + 0.5);

    return buffer.at(index_new).at(index);
}

/**
 * @brief Sovraccarico dell'operatore di output per la classe LidarDriver.
 *
 * Questo metodo permette di stampare l'ultima scansione contenuta nel buffer del LidarDriver.
 * Se il buffer all'indice più recente è vuoto, viene stampato un messaggio indicante che il buffer è vuoto.
 * Altrimenti, vengono stampate le misurazioni dell'ultima scansione.
 *
 * @param os Stream di output in cui scrivere.
 * @param lidar Oggetto LidarDriver da cui recuperare i dati.
 * @return Riferimento allo stream di output.
 */
std::ostream &operator<<(std::ostream &os, const LidarDriver &lidar) {
    if (lidar.buffer.at(lidar.index_new).empty()) {
        os << "Buffer vuoto\n";
    } else {
        os << "Ultima scansione:\n";
        for (double value: lidar.buffer.at(lidar.index_new)) {
            os << value << " ";
        }
        os << "\n";
    }
    return os;
}
