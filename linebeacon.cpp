#include "pxt.h"
#include "LineBeaconService.h"
#include <stdio.h>
#include <ctype.h>
#include "MicroBitConfig.h"

using namespace pxt;

/**
 * Support for LINE Beacon.
 */
//% color=#00c300 weight=100 icon="\uf294" block="LINE Beacon"
namespace linebeacon {

    LineBeaconService* _pService = NULL;

    int hexStringToBytes(String strData, uint8_t *data, uint8_t maxlen) {
        
        // https://lancaster-university.github.io/microbit-docs/data-types/string/
        ManagedString m = MSTR(strData);

        int16_t len = m.length();
        if (maxlen * 2 < len) {
            len = maxlen * 2;
        }

        // 16進数以外の文字が含まれていたらパラメーターエラー      
        int i;

        for (i=0; i<len; i++) {
            if (! isxdigit(m.charAt(i))) {
                return MICROBIT_INVALID_PARAMETER;
            }
        }

        for (int16_t i=0; i<len; i+=2) {
            unsigned int x;
            
            sscanf(m.substring(i,2).toCharArray(), "%02x", &x);
            data[i/2] = (uint8_t) x;
        }

        return MICROBIT_OK; 
    }

    //%
    void startWithDeviceMessage(String hwid, String message) {

        ManagedString h = MSTR(hwid);
        ManagedString m = MSTR(message);

        if (h.length() != 10) {
            uBit.display.clear();
            uBit.display.print("LINE Beacon HWID is invalid.");
            return;
        }

        if (m.length() > 26 || m.length() % 2 != 0) {
            uBit.display.clear();
            uBit.display.print("LINE Beacon Message is invalid.");
            return;
        }

        if (NULL == _pService) {
#if MICROBIT_CODAL
            _pService = new LineBeaconService();
#else
            _pService = new LineBeaconService(*uBit.ble);
#endif
        }

        uint8_t hwidBytes[5];
        if (hexStringToBytes(hwid, hwidBytes, 5) != MICROBIT_OK) {
            uBit.display.clear();
            uBit.display.print("LINE Beacon HWID is invalid.");               
        }

        uint8_t msglen = m.length() / 2;

        // DeviceMessage は、1byte以上、13byte以下        
        if (msglen > 13) msglen = 13;
        uint8_t messageBytes[msglen];
        if (hexStringToBytes(message, messageBytes, msglen) != MICROBIT_OK) {
            uBit.display.clear();
            uBit.display.print("LINE Beacon Message is invalid.");               
        }

        _pService->start(hwidBytes, messageBytes, msglen);
    }


    //% 
    void stop() {        
        // ここ //% の直前に、丁寧にコメントブロック書いたら
        // 挙動がおかしくなったよ。気を付けよう。
        if (NULL != _pService) {
            _pService->stop();
        }        

        // これでもよさそう
        // uBit.bleManager.stopAdvertising();  
    }   

}
