// #include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEServer.h>
// #include <BLE2902.h>
// #include <Arduino.h>

// #define SERVICE_UUID "00001111-0000-1000-8000-00805F9B34FB"
// #define CHARACTERISTIC_UUID_TX "c0de0002-feed-f00d-c0ff-eeb3d05ebeef"
// #define CHARACTERISTIC_UUID_RX "c0de0003-feed-f00d-c0ff-eeb3d05ebeef"

// bool deviceConnected = false;
// bool messageReceivedComplete = false;

// class EchoServerCallbacks : public BLEServerCallbacks
// {
//     void onConnect(BLEServer *pServer)
//     {
//         deviceConnected = true;
//         //stop advt?
//         Serial.println("Connected!");
//     };

//     void onDisconnect(BLEServer *pServer)
//     {
//         //restart advt?
//         deviceConnected = false;
//         Serial.println("Disconnected!");
//         pServer->getAdvertising()->start();
//     }
// };

// class ServerReadCallbacks : public BLECharacteristicCallbacks
// {
//     void onWrite(BLECharacteristic *pCharacteristic)
//     {
//         std::string rxValue = pCharacteristic->getValue();
//         Serial.println("*********");
//         Serial.print("Received Value: ");
//         for (int i = 0; i < rxValue.length(); i++)
//         {
//             Serial.print(rxValue[i]);
//         }
//         Serial.println();

//         //add to message (as of now just one packet)
//         message = rxValue;

//         //once you think all packets are received. As of now one packet
//         messageReceivedComplete = true;
//     }
// };

// BLECharacteristic pCharacteristicRX(
//     "00002222-0000-1000-8000-00805F9B34FB",
//     BLECharacteristic::PROPERTY_WRITE);

// BLECharacteristic pCharacteristicTX(
//     "00007777-0000-1000-8000-00805F9B34FB",
//     BLECharacteristic::PROPERTY_READ);

// int echoNumber = 0;
// std::string message;

// void respond(std::string send_message)
// {
//     Serial.println("inside send_message");
//     pCharacteristicTX.setValue(send_message);
//     pCharacteristicTX.notify();
//     Serial.println("sent send_message");
// }

// // //This call back happens when the android client writes

// void setup()
// {
//     Serial.begin(115200);
//     Serial.println("Starting BLE work!");

//     BLEDevice::init("ESP32BLE");
//     BLEServer *pServer = BLEDevice::createServer();
//     pServer->setCallbacks(new EchoServerCallbacks());

//     BLEService *pService = pServer->createService(BLEUUID((uint16_t)0x1700)); //  A random ID has been selected

//     pService->addCharacteristic(&pCharacteristicTX);
//     pService->addCharacteristic(&pCharacteristicRX);

//     pCharacteristicRX->addDescriptor(new BLE2902());
//     pCharacteristicRX->setCallbacks(new ServerReadCallbacks());

//     pCharacteristicTX->addDescriptor(new BLE2902());
//     pCharacteristicRX->addDescriptor(new BLE2902());

//     pServer->getAdvertising()->addServiceUUID(serviceID);

//     // Start the service
//     pService->start();

//     // Start the Server/Advertising
//     pServer->getAdvertising()->start();

//     Serial.println("Waiting for a Client to connect...");
//     pCharacteristicRX.setValue("essa");
// }

// void loop()
// {
//     // some delay before running repeatedly
//     delay(1000);

//     // if device is connected and all packets are received, then respond
//     if (deviceConnected && messageReceivedComplete)
//     {
//         messageReceivedComplete = false;
//         if (String("hello").c_str() == message)
//         {
//             respond(String("world").c_str());
//             Serial.println("sent world");
//         }
//         else
//         {
//             respond(message);
//             Serial.println("echoed");
//         }
//     }
// }