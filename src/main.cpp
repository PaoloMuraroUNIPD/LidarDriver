// main per testare la classe

#include <iostream>

#include "../include/LidarDriver.h"

int main(void) {
//    Serve un costruttore generico?
    LidarDriver lidarDriver(1,10);
    lidarDriver.clear_buffer();
    std::cout<<lidarDriver<<std::endl;
    std::cout << "OK, LET'S GO" << std::endl;
    return 0;
}