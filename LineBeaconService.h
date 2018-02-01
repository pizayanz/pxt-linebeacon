#ifndef LINEBEACON_SERVICE_H
#define LINEBEACON_SERVICE_H

#include "ble/BLE.h"

/**
  * Class definition for the LineBeacon service.
  * Provides a BLE service to receive LineBeaconMessages
  */
class LineBeaconService
{
    public:

    /**
      * Constructor.
      * Create a representation of the BlueDotService
      * @param _ble The instance of a BLE device that we're running on.
      */
    LineBeaconService(BLEDevice &_ble);
    void start(const uint8_t *hwid, const uint8_t *message, const uint8_t len);
    void stop();

    private:

    // Bluetooth stack we're running on.
    BLEDevice           	&ble;

    // https://github.com/line/line-simple-beacon/blob/master/README.ja.md
    const uint8_t flags[1] = {0x06};
    const uint8_t linecorp[2] = {0x6F, 0xFE};
    const uint8_t hwidframe[9] = {
        0x6F, 0xFE, // LINE corp
        0x02,       // Frame Type
        0x00, 0x00, 0x00, 0x00, 0x00,   // HWID 
        0x7F        // Measured TxPower
    };
};


#endif
