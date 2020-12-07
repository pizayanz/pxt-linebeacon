#include "MicroBitConfig.h"
#include "LineBeaconService.h"

//================================================================
#if MICROBIT_CODAL
//================================================================

/**
 * Copyright (c) 2014 - 2020, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 *
 * @defgroup ble_sdk_app_beacon_main main.c
 * @{
 * @ingroup ble_sdk_app_beacon
 * @brief Beacon Transmitter Sample Application main file.
 *
 * This file contains the source code for an Beacon transmitter sample application.
 */

#include <stdbool.h>
#include <stdint.h>
#include "nordic_common.h"
// #include "bsp.h"
#include "nrf_soc.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "ble_advdata.h"
// #include "ble_gap.h"
#include "app_timer.h"
#include "nrf_pwr_mgmt.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


#define APP_BLE_CONN_CFG_TAG            1                                  /**< A tag identifying the SoftDevice BLE configuration. */

#define NON_CONNECTABLE_ADV_INTERVAL    MSEC_TO_UNITS(152.5, UNIT_0_625_MS)  /**< The advertising interval for non-connectable advertisement (100 ms). This value can vary between 100ms to 10.24s). */

static uint8_t              m_adv_handle = BLE_GAP_ADV_SET_HANDLE_NOT_SET; /**< Advertising handle used to identify an advertising set. */
static uint8_t              m_enc_advdata[ BLE_GAP_ADV_SET_DATA_SIZE_MAX];  /**< Buffer for storing an encoded advertising set. */

static uint8_t m_beacon_info[31] = 
{
    0x02,
    0x01,
    0x06,
    0x03,
    0x03,
    0x6f,
    0xfe,
    0x17,
    0x16,
    0x6f,
    0xfe,
    0x02,
    0x01, 0x12, 0x23, 0x34, 0x45, // LINE_BEACON_HWID, 
    0x7f,
    0x01, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9a, 0xab, 0xbc, 0xcd // LINE_BEACON_MESSAGE
};

/**@brief Function for initializing the Advertising functionality.
 *
 * @details Encodes the required advertising data and passes it to the stack.
 *          Also builds a structure to be passed to the stack when starting advertising.
 */
static void advertising_init(const uint8_t *hwid, const uint8_t *message, const uint8_t len)
{

    // uint8_t frameData[ MicroBitEddystone::frameSizeUID]; 組み立てるか。。。それもまたよし。。。
    // m_beacon_info[12] = hwid[0];
    // m_beacon_info[13] = hwid[1];
    // m_beacon_info[14 = hwid[2];
    // m_beacon_info[7] = hwid[3];
    // m_beacon_info[8] = hwid[4];
    m_beacon_info[7] = 10 + len;
    memcpy(&m_beacon_info[12], hwid,sizeof(uint8_t) * 5);

    memset(&m_beacon_info[18], 0, sizeof(uint8_t) * 13);
    memcpy(&m_beacon_info[18], message, len);

    ble_gap_adv_params_t    gap_adv_params;
    memset(&gap_adv_params, 0, sizeof(gap_adv_params));

    gap_adv_params.properties.type  = BLE_GAP_ADV_TYPE_NONCONNECTABLE_NONSCANNABLE_UNDIRECTED; //BLE_GAP_ADV_TYPE_EXTENDED_NONCONNECTABLE_NONSCANNABLE_UNDIRECTED; // BLE_GAP_ADV_TYPE_NONCONNECTABLE_NONSCANNABLE_UNDIRECTED;
    gap_adv_params.p_peer_addr      = NULL;    // Undirected advertisement.
    gap_adv_params.filter_policy    = BLE_GAP_ADV_FP_ANY;
    gap_adv_params.interval         = NON_CONNECTABLE_ADV_INTERVAL;
    gap_adv_params.duration         = 0;       // Never time out.

    gap_adv_params.primary_phy      = BLE_GAP_PHY_1MBPS; // BLE_GAP_PHY_CODED
    gap_adv_params.secondary_phy    = BLE_GAP_PHY_1MBPS; // BLE_GAP_PHY_CODED

    ble_gap_adv_data_t  gap_adv_data;
    memset( &gap_adv_data, 0, sizeof( gap_adv_data));
    gap_adv_data.adv_data.p_data    = m_beacon_info;
    gap_adv_data.adv_data.len       = 18 + len;

    MICROBIT_BLE_ECHK(sd_ble_gap_adv_set_configure(&m_adv_handle, &gap_adv_data, &gap_adv_params));

}


/**@brief Function for starting advertising.
 */
static void advertising_start(void)
{
    MICROBIT_BLE_ECHK(sd_ble_gap_adv_start(m_adv_handle, APP_BLE_CONN_CFG_TAG));
}


/**@brief Function for initializing the BLE stack.
 *
 * @details Initializes the SoftDevice and the BLE event interrupt.
 */
static void ble_stack_init(void)
{
    MICROBIT_BLE_ECHK(nrf_sdh_enable_request());

    // Configure the BLE stack using the default settings.
    // Fetch the start address of the application RAM.
    uint32_t ram_start = 0;
    MICROBIT_BLE_ECHK(nrf_sdh_ble_default_cfg_set(APP_BLE_CONN_CFG_TAG, &ram_start));

    // Enable BLE stack.
    MICROBIT_BLE_ECHK(nrf_sdh_ble_enable(&ram_start));
}


LineBeaconService::LineBeaconService() {
    ble_stack_init();   
}

/**
 * @brief Function for stop advertising.
 */
static void advertising_stop(void) {
    MICROBIT_DEBUG_DMESG("stopAdvertising");
    MICROBIT_BLE_ECHK(sd_ble_gap_adv_stop(m_adv_handle));
}

void LineBeaconService::start(const uint8_t *hwid, const uint8_t *message, const uint8_t len) {

    MICROBIT_DEBUG_DMESG("LineBeaconService::start");
    // uBit.display.print("start");

    advertising_init(hwid, message, len);

    // Start execution.
    // NRF_LOG_INFO("Beacon example started.");
    advertising_start();

}

void LineBeaconService::stop() {
    // uBit.display.print("stop");
    advertising_stop();
}

//================================================================
#else // MICROBIT_CODAL
//================================================================

#include "ble/UUID.h"

/**
 * Constructor.
 * Create a representation of the LineBeaconService
 * @param _ble The instance of a BLE device that we're running on.
 */
LineBeaconService::LineBeaconService(BLEDevice &_ble) : ble(_ble) {}

void LineBeaconService::start(const uint8_t *hwid, const uint8_t *message, const uint8_t len) {
    ble.gap().startAdvertising();

    GapAdvertisingData payload;
    payload.addData(GapAdvertisingData::FLAGS, flags, 1);
    payload.addData(GapAdvertisingData::COMPLETE_LIST_16BIT_SERVICE_IDS, linecorp,
                    sizeof(linecorp));

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

void LineBeaconService::stop() {
    // これだとなぜか止まらない？
    // ble.gap().stopAdvertising();
    uBit.bleManager.stopAdvertising();
}

//================================================================
#endif // MICROBIT_CODAL
//================================================================
