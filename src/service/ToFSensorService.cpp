#include "VL53L0X.h"
#include <cstdint>

class ToFSensorService {
    private: DevI2C *devI2c;
    private: DigitalOut *shutdown_pin;
    private: VL53L0X *range;

    private: uint32_t startDistance = 0;

    public: ToFSensorService() {
        devI2c = new DevI2C( PB_11, PB_10 );
        shutdown_pin = new DigitalOut( PC_6 );
        range = new VL53L0X(devI2c, shutdown_pin, PC_7);
        range->init_sensor(VL53L0X_DEFAULT_ADDRESS);
    }

    public: bool isInRange() {
        uint32_t distance;
        int status = range->get_distance(&distance);
        if(status == VL53L0X_ERROR_NONE) {
            if(startDistance == 0) {
                startDistance = distance;
            }

            return distance < startDistance;
        }

        return false;
    }
};