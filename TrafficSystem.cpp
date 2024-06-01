#include "TrafficSystem.hpp"

void TrafficSystem::setup() {
    TrafficData rightData;
    rightData.triggerPin = 2;
    rightData.echoPin = 3;
    rightData.redPin = 4;
    rightData.yellowPin = 5;
    rightData.greenPin = 6;

    TrafficData leftData;
    leftData.triggerPin = 7;
    leftData.echoPin = 8;
    leftData.redPin = 9;
    leftData.yellowPin = 10;
    leftData.greenPin = 11;

    this->rightTraffic = new Traffic(rightData);
    this->leftTraffic = new Traffic(leftData);

    this->rightTraffic->setup();
    this->leftTraffic->setup();
}

void TrafficSystem::loop() {
    this->rightTraffic->loop();
    this->leftTraffic->loop();

    if (this->rightTraffic->isIncoming()) {
        switch (this->leftTraffic->getState())
        {
        case Traffic::RED:
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
    } else if(this->leftTraffic->isIncoming()) {
        switch (this->rightTraffic->getState())
        {
        case Traffic::RED:
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

}