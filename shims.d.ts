// Auto-generated. Do not edit.


    /**
     * Support for LINE Beacon.
     */

declare namespace linebeacon {

    /**
     *  LINE Beacon Start with Device Message. 1 byte to 13 bytes.
     * @param hwid hex HWID, eg: "0f0f0f0f0f"
     * @param message hex Device Message 1byte to 13byte, eg: "1a2b3c4d5e6f70809010a0b0c0"
     */
    //% blockId=linebeacon_start_with_devicemessage block="LINE Beacon start HWID is %hwid|with Device Message %message"
    //% shim=linebeacon::startWithDeviceMessage
    //% blockGap=8 weight=55 blockExternalInputs=1 shim=linebeacon::startWithDeviceMessage
    function startWithDeviceMessage(hwid: string, message: string): void;

    /**
     *  LINE Beacon Stop
     */
    //% blockId=linebeacon_stop block="LINE Beacon stop"
    //% shim=linebeacon::stop
    //% blockGap=8 weight=20 shim=linebeacon::stop
    function stop(): void;
}

// Auto-generated. Do not edit. Really.
