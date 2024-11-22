// definizione della classe e dei metodi
#ifndef LIDAR_DRIVER_H
#define LIDAR_DRIVER_H

#include <iostream>
#include <vector>

class LidarDriver {

    private:
        double resolution;
        std::vector<std::vector<double>> buffer;
        size_t size;
        size_t count;
        size_t index;

    public:
        LidarDriver(double res, size_t buffer_dim);

        void new_scan(const std::vector<double>& scan);
        std::vector<double> get_scan();
        void clear_buffer();
        double get_distance(double angle);

        friend std::ostream& operator<<(std::ostream& os, const LidarDriver& lidar);

};

#endif