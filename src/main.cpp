#include "../include/LidarDriver.h"

int main() {
    try {
        LidarDriver lidar(1.0);
        lidar.new_scan();
        lidar.new_scan();
        std::cout << lidar;
        std::vector<double> retrieved_scan = lidar.get_scan();
        std::cout << "Scansione recuperata:\n";
        for (double value : retrieved_scan) {
            std::cout << value << " ";
        }
        std::cout << "\n";
        double angle = 90.0;
        std::cout << "Distanza all'angolo " << angle << "°: "
                  << lidar.get_distance(angle) << "\n";
        lidar.clear_buffer();
        std::cout << "Buffer dopo la pulizia:\n" << lidar;

    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << std::endl;
    }

    return 0;
}