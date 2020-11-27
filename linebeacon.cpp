#include "pxt.h"
#include "LineBeaconService.h"
#include <string.h>

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

    //% 
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

    //% 
    void stop() {        
        if (NULL != _pService) {
            _pService->stop();
        }        
    }   

}