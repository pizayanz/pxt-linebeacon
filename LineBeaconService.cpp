#include "MicroBitConfig.h"
#include "ble/UUID.h"

#include "LineBeaconService.h"

/**
  * Constructor.
  * Create a representation of the LineBeaconService
  * @param _ble The instance of a BLE device that we're running on.
  */
LineBeaconService::LineBeaconService(BLEDevice &_ble) :
        ble(_ble)
{
}

void LineBeaconService::start(const uint8_t *hwid, const uint8_t *message, const uint8_t len)
{    
    ble.gap().startAdvertising();

    GapAdvertisingData payload;
    payload.addData(GapAdvertisingData::FLAGS, flags, 1);
    payload.addData(GapAdvertisingData::COMPLETE_LIST_16BIT_SERVICE_IDS, linecorp, sizeof(linecorp));

    uint8_t buf[sizeof(hwidframe) / sizeof(hwidframe[0]) + len];
    memcpy(buf, hwidframe, sizeof(uint8_t) * sizeof(hwidframe));

    buf[3] = hwid[0];
    buf[4] = hwid[1];
    buf[5] = hwid[2];
    buf[6] = hwid[3];
    buf[7] = hwid[4];

    memcpy(&buf[sizeof(hwidframe) / sizeof(hwidframe[0])], message, sizeof(uint8_t) * len);

    payload.addData(GapAdvertisingData::SERVICE_DATA, buf, sizeof(buf));

    ble.setAdvertisingData(payload);
    ble.startAdvertising();
  
}  


void LineBeaconService::stop() 
{
    ble.gap().stopAdvertising();
}  
