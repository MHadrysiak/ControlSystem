#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>
#include <ServerReadCallbacks.hh>
#include <EchoServerCallbacks.hh>

#ifndef BLUETOOTH_LE_READY_LIB
#define BLUETOOTH_LE_READY_LIB

#define serviceID "00001111-0000-1000-8000-00805F9B34FB"
#define SERVICE_UUID "00001111-0000-1000-8000-00805F9B34FB"
// #define CHARACTERISTIC_UUID_TX "c0de0002-feed-f00d-c0ff-eeb3d05ebeef"
// #define CHARACTERISTIC_UUID_RX "c0de0003-feed-f00d-c0ff-eeb3d05ebeef"




extern std::string message;

static BLECharacteristic pCharacteristicRX(
    "00002222-0000-1000-8000-00805F9B34FB",
    BLECharacteristic::PROPERTY_WRITE);

static BLECharacteristic pCharacteristicTX(
    "00007777-0000-1000-8000-00805F9B34FB",
    BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_NOTIFY);

class ESP32_blelib
{
public:
    // static BLEServer *pServer;
    // static BLEService *pService;
    static std::string prevMessege;
    static void init(BLECharacteristic *pCharacteristicTX, BLECharacteristic *pCharacteristicRX);

private:
    ESP32_blelib() {}
};

#endif


