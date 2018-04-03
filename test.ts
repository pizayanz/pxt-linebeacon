linebeacon.start("0f0f0f0f0f"); // this is fake HWID

linebeacon.stop();

linebeacon.startWithDeviceMessage(
    "0f0f0f0f0f",   // this is also fake HWID
    "1a2b3c4d5e6f70809010a0b0c0"
);

linebeacon.stop();
