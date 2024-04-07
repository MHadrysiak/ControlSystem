#include <BLEServer.h>
#include <BLEUtils.h>

extern bool deviceConnected;

class EchoServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        deviceConnected = true;
        pServer->getAdvertising()->stop();
        Serial.println("Connected!");
    };

    void onDisconnect(BLEServer *pServer)
    {
        deviceConnected = false;
        Serial.println("Disconnected!");
        pServer->getAdvertising()->start();
    }
};