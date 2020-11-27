#include "pxt.h"
#include "LineBeaconService.h"
#include <stdio.h>

using namespace pxt;

/**
 * Support for LINE Beacon.
 */
namespace linebeacon {
    LineBeaconService* _pService = NULL;

    void HexStringToBytes(StringData *strData, uint8_t *data) {
        ManagedString m(strData);
        int16_t len = m.length();
        for (int16_t i=0; i<len; i+=2) {
            unsigned int x;
            
            sscanf(m.substring(i,2).toCharArray(), "%02x", &x);
            data[i/2] = (uint8_t) x;
        }
    }

    /**
    *  LINE Beacon Start with Device Message. 1 byte to 13 bytes.
    * @param hwid hex HWID, eg: "0f0f0f0f0f"
    * @param message hex Device Message 1byte to 13byte, eg: "1a2b3c4d5e6f70809010a0b0c0"
    */
    //% blockId=linebeacon_start_with_devicemessage block="LINE Beacon start HWID is %hwid|with Device Message %message"
    //% shim=linebeacon::startWithDeviceMessage
    //% blockGap=8 weight=55 blockExternalInputs=1
    void startWithDeviceMessage(StringData *hwid, StringData *message) {
        if (NULL == _pService) {
            _pService = new LineBeaconService(*uBit.ble);
        }

        uint8_t hwidBytes[5];
        HexStringToBytes(hwid, hwidBytes);

        ManagedString m(message);
        uint8_t mlen = m.length() / 2;

        // DeviceMessage は、1byte以上、13byte以下        
        if (mlen > 13) mlen = 13;
        uint8_t messageBytes[mlen];
        HexStringToBytes(message, messageBytes);
        _pService->start(hwidBytes, messageBytes, mlen);
    }

    /**
    *  LINE Beacon Stop
    */
    //% blockId=linebeacon_stop block="LINE Beacon stop"
    //% shim=linebeacon::stop
    //% blockGap=8 weight=20 
    void stop() {        
        if (NULL != _pService) {
            _pService->stop();
        }        
    }   

}