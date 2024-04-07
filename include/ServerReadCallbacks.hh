#include <BLEServer.h>
#include <BLEUtils.h>

extern std::string message;
extern QueueHandle_t comQueue;
extern QueueHandle_t respondQueue;

static bool messageReceivedComplete;

class ServerReadCallbacks : public BLECharacteristicCallbacks
{
public:
        void onWrite(BLECharacteristic *pCharacteristic)
    {
        std::string rxValue = pCharacteristic->getValue();
        Serial.println("*********");
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++)
        {
            Serial.print(rxValue[i]);
        }
        Serial.println();
        message = rxValue;
        
        xQueueSend(comQueue, &message, portMAX_DELAY);
        messageReceivedComplete = true;
    }
};