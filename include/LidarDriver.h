// definizione della classe e dei metodi
#ifndef LIDAR_DRIVER_H
#define LIDAR_DRIVER_H
#define BUFFER_DIM 10

#include <iostream>
#include <vector>

class LidarDriver {

    private:
        double resolution;
        std::vector<std::vector<double>> buffer;
        size_t size;
        size_t count;
        size_t index_old;
        size_t index_new;

    public:
        LidarDriver(double res);

        void new_scan(const std::vector<double>& scan);
        std::vector<double> get_scan();
        void clear_buffer();
        double get_distance(double angle);



        friend std::ostream& operator<<(std::ostream& os, const LidarDriver& lidar);

};

#endif