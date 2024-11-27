LidarDriver

Il progetto mira allo sviluppo di una libreria dedicata alla gestione dei dati generati da un sensore LiDAR (Light Detection and Ranging). A tal fine, è stato creato il file LidarDriver.cpp, che implementa la classe dichiarata in LidarDriver.h e fornisce le funzionalità necessarie per l'elaborazione e la gestione dei dati provenienti dal sensore.
Questa libreria mantiene in memoria un buffer circolare per gestire le scansioni provenienti dal sensore LiDAR. Utilizza un vector `buffer` di dimensione fissa (`BUFFER_DIM`) e due indici (`index_new` e `index_old`) per tenere traccia della posizione dell'ultima scansione e di quella più vecchia. Le scansioni sono memorizzate come `vector<double>`.

Ecco una breve descrizione delle sue funzionalità principali:

Aggiunta di Nuove Scansioni - sviluppato da Alberto Faccio
Quando una nuova scansione viene aggiunta tramite `new_scan`, la libreria verifica se la posizione corrente del `buffer` è vuota. Se non lo è, incrementa l'indice delle nuove scansioni (`index_new`) in modo circolare. Se l'indice delle nuove scansioni coincide con l'indice delle vecchie scansioni (`index_old`), incrementa anche quest'ultimo per mantenere il buffer circolare.

Incremento degli Indici - sviluppato da Federico Maniglio
 La funzione `increment_index` assicura che gli indici vengano incrementati in modo circolare, riportandoli a zero se superano la dimensione del buffer.

Recupero delle Scansioni Più Vecchie - sviluppato da Paolo Muraro
 La funzione `get_scan` restituisce e rimuove la scansione più vecchia dal buffer, aggiornando conseguentemente l'indice delle vecchie scansioni. Se il buffer è vuoto, solleva un'eccezione.

Pulizia del Buffer - sviluppato da Alberto Faccio
 Il metodo `clear_buffer` elimina tutte le scansioni presenti nel buffer e reinizializza gli indici a zero, segnando il buffer come vuoto.

Calcolo della Distanza dato un angolo - sviluppato da Paolo Muraro
 La funzione `get_distance` calcola l'indice appropriato nel buffer a partire da un angolo specificato e restituisce la distanza corrispondente. Genera eccezioni se il buffer è vuoto o se l'angolo è fuori dal range consentito (0-180 gradi).

Overload dell'Operatore di Output - sviluppato da Federico Maniglio
Il metodo `operator<<` permette di stampare l'ultima scansione contenuta nel buffer del `LidarDriver`. Se il buffer all'indice più recente è vuoto, viene stampato un messaggio indicante che il buffer è vuoto. Altrimenti, vengono stampate le misurazioni dell'ultima scansione.


Inoltre, per completare il progetto, sono stati sviluppati anche ulteriori componenti:

LidarDriver.h - sviluppato da Paolo Muraro
Questo file contiene la dichiarazione della classe `LidarDriver`. Include tutti i metodi e comprende inoltre la definizione di alcuni membri privati come la risoluzione dell'angolo, un buffer circolare, e gli indici per le scansioni vecchie e nuove.

main.cpp - sviluppato da Federico Maniglio e Alberto Faccio
Questo file implementa la funzione main, concepita per eseguire e verificare le funzionalità della libreria LidarDriver. Include un menu interattivo che consente all'utente di accedere e testare tutte le caratteristiche fornite dalla libreria.




Contributori del progetto LidarDriver - Gruppo 404
Alberto Faccio - Implementazione delle funzionalità di aggiunta di nuove scansioni, pulizia del buffer e main.cpp.
Federico Maniglio - Implementazione delle funzionalità di incremento degli indici, overload dell'operatore di output e main.cpp.
Paolo Muraro - Implementazione delle funzionalità di recupero delle scansioni più vecchie, calcolo della distanza dato l'angolo e LidarDriver.h

