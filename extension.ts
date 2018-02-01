/**
 * Support for LINE Beacon.
 */
//% color="#00c300" weight=100 icon="\uf294" block="LINE Beacon"
// TODO: Semantic UI が Font Awesome v5.0.0 に対応したらアイコンを Bluetooth のものから LINE に変更すること
// color="#00c300" weight=100 icon="\uf3c0" block="LINE Beacon"
namespace linebeacon {

    /**
    *  LINE Beacon Start
    * @param hwid hex HWID, eg: "0f0f0f0f0f"
    */
    //% blockId=linebeacon_start block="LINE Beacon start HWID is %hwid"
    //% blockGap=8 weight=60
    export function start(hwid: string) : void {
        if (hwid.length != 10) {
            // TODO: エラーの返し方がいまいちわからない。
            // 16進数の10桁文字列出ない場合は、エラーを返したいのだけれど
            // こっちはシミュレーター側。cpp でも、同じようなバリデーションが必要
        }
        startWithDeviceMessage(hwid, "00")
        return
    }

    /**
    *  LINE Beacon Start with Device Message. 1 byte to 13 bytes.
    * @param hwid hex HWID, eg: "0f0f0f0f0f"
    * @param message hex Device Message 1byte to 13byte, eg: "1a2b3c4d5e6f70809010a0b0c0"
    */
    //% blockId=linebeacon_start_with_devicemessage block="LINE Beacon start HWID is %hwid|with Device Message %message"
    //% shim=linebeacon::startWithDeviceMessage
    //% blockGap=8 weight=55 blockExternalInputs=1
    export function startWithDeviceMessage(hwid: string, message:string) : void {
        if (hwid.length != 10) {
            // TODO: エラーの返し方がいまいちわからない。
        }
        if (message.length > 13) {
            // TODO: エラーの返し方がいまいちわからない。
        }
        return
    }
    
    /**
    *  LINE Beacon Stop
    */
    //% blockId=linebeacon_stop block="LINE Beacon stop"
    //% shim=linebeacon::stop
    //% blockGap=8 weight=20
    export function stop(): void {
        return
    }
}