/// <reference no-default-lib="true"/>
/**
 * Support for LINE Beacon.
 */
//% color=#00c300 weight=100 icon="\uf294" block="LINE Beacon"
namespace linebeacon {

    // TODO: Semantic UI が Font Awesome v5.0.0 に対応したらアイコンを Bluetooth のものから LINE に変更すること
    // color="#00c300" weight=100 icon="\uf3c0"

    /**
    *  LINE Beacon Start
    * @param hwid hex HWID, eg: "0f0f0f0f0f"
    */
    //% blockId=linebeacon_start 
    //% block="LINE Beacon start HWID is %hwid"
    //% block.loc.ja="LINE Beacon の HWID を %hwid にして開始" 
    //% blockGap=8 weight=60
    // //% help=pxt-linebeacon/start 
    // help は省略すると README が表示される。
    // ※ 認証された拡張パッケージのみであることに注意。任意のときは適切に URL など用意すること
    export function start(hwid: string): void {
        if (hwid.length != 10) {
            // TODO: エラーの返し方がいまいちわからない。
            // 16進数の10桁文字列でない場合は、エラーを返したいのだけれど
            // こっちはシミュレーター側。cpp でも、同じようなバリデーションが必要
        }
        return startWithDeviceMessage(hwid, "00");
    }

    /**
    *  LINE Beacon Start with Device Message. 1 byte to 13 bytes.
    * @param hwid hex HWID, eg: "0f0f0f0f0f"
    * @param message hex Device Message 1byte to 13byte, eg: "1a2b3c4d5e6f70809010a0b0c0"
    */
    //% blockId=linebeacon_start_with_devicemessage
    //% block="LINE Beacon start HWID is %hwid|with Device Message %message"
    //% block.loc.ja="LINE Beacon の HWID を %hwid|デバイスメッセージを %message にして開始" 
    //% shim=linebeacon::startWithDeviceMessage
    //% blockGap=8 weight=55 blockExternalInputs=1
    // //% help=pxt-linebeacon/start-with-device-message
    export function startWithDeviceMessage(hwid: string, message: string): void {
        if (hwid.length != 10) {
            // TODO: エラーの返し方がいまいちわからない。Display 使う
            basic.clearScreen();
            basic.showString("HWID is invalid.");

        }
        if (message.length > 26 || message.length % 2 != 0) {
            // TODO: エラーの返し方がいまいちわからない。Display 使う
            basic.clearScreen();
            basic.showString("Massage is invalid.");
        }
        return;
    }


    /**
     * Stops advertising LINE Beacon end points
     */
    //% blockId=linebeacon_stop
    //% block="LINE Beacon stop"
    //% block.loc.ja="LINE Beacon を停止"
    //% shim=linebeacon::stop
    //% weight=10 blockGap=8 advanced=true
    export function stop() {
        return;
    };

//     /**
//      * Stops advertising LINE Beacon end points
//      */
//     //% blockId=linebeacon_central
//     //% block="LINE Beacon central"
//     //% block.loc.ja="LINE Beacon を受信"
//     //% weight=10 blockGap=8 advanced=true
//     //% group="micro:bit (V2)"
//     export function onCentralEvent() {
//         #if MICROBIT_CODAL
//         registerWithDal(uBit.logo.id, action, body);
// #else
//         target_panic(PANIC_VARIANT_NOT_SUPPORTED);
// #endif
//         return;
//     };
}