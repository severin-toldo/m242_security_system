#include "VL53L0X.h"
#include <cstdint>
#pragma once

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

        int status;
        do {
            status = range->get_distance(&distance);
        }while (status != VL53L0X_ERROR_NONE);
         

        printf("Alarm threshold / Current: %d    /   %d\n", startDistance, distance);
        if(status == VL53L0X_ERROR_NONE) {    
            if(startDistance == 0) {
                startDistance = distance - 15;
            }
            if(startDistance > 2000) {
                startDistance = 2000;
            }

            return distance >= startDistance;
        }

        printf("couldn't read distance\n");

        return false;
    }
};