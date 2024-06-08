#include "TrafficSystem.hpp"

void TrafficSystem::setup() {
    TrafficData rightData;
    rightData.triggerPin = 2;
    rightData.echoPin = 3;
    rightData.redPin = 4;
    rightData.bluePin = 5;
    rightData.greenPin = 6;

    TrafficData leftData;
    leftData.triggerPin = 9;
    leftData.echoPin = 7;
    leftData.redPin = 8;
    leftData.bluePin = 10;
    leftData.greenPin = 11;

    TrafficData topData;

    this->rightTraffic = new Traffic(rightData);
    this->leftTraffic = new IrTraffic(leftData);

    this->rightTraffic->setup();
    this->leftTraffic->setup();
    Serial.begin(115200);
    Serial.println("SYSTEM STARTING");
}

void TrafficSystem::loop() {
    this->rightTraffic->loop();
    this->leftTraffic->loop();

    // checking right traffic
    if (this->rightTraffic->isIncoming()) {
        Serial.println("incoming at right...");
        switch (this->leftTraffic->getState()) {
        case Traffic::RED:
            Serial.println("No car at left traffic yet!!!");
            Serial.println("Get ready...");
            if (this->rightTraffic->getState() == Traffic::RED) {
                this->rightTraffic->switchState(Traffic::YELLOW);
                delay(2000);
            }
            this->rightTraffic->switchState(Traffic::GREEN);
            delay(5000);
            break;
        case Traffic::YELLOW:
            this->rightTraffic->switchState(Traffic::RED);
            break;
        case Traffic::GREEN:
            this->rightTraffic->switchState(Traffic::RED);
        default:
            this->rightTraffic->switchState(Traffic::RED);
            break;
        }
    }
    else {
        this->rightTraffic->switchState(Traffic::RED);
    }

    // cheching left traffic
    if (this->leftTraffic->isIncoming()) {
        Serial.println("incoming at left...");
        switch (this->rightTraffic->getState()) {
        case Traffic::RED:
            Serial.println("No car at right traffic yet!!!");
            Serial.println("Get ready...");
            if (this->leftTraffic->getState() == Traffic::RED) {
                this->leftTraffic->switchState(Traffic::YELLOW);
                delay(2000);
            }
            this->leftTraffic->switchState(Traffic::GREEN);
            delay(5000);
            break;
        case Traffic::YELLOW:
            this->leftTraffic->switchState(Traffic::RED);
            break;
        case Traffic::GREEN:
            this->leftTraffic->switchState(Traffic::RED);
        default:
            this->leftTraffic->switchState(Traffic::RED);
            break;
        }
    }
    else {
        this->leftTraffic->switchState(Traffic::RED);
    }

}