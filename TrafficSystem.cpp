#include "TrafficSystem.hpp"


void TrafficSystem::setup() {
    TrafficData rightData;
    rightData.triggerPin = 2;
    rightData.echoPin = 3;

    rightData.redPin = 4;
    rightData.bluePin = 5;
    rightData.greenPin = 6;
    rightData.humanButton = 12;

    TrafficData leftData;
    leftData.triggerPin = 9;
    leftData.echoPin = 7;

    leftData.redPin = 8;
    leftData.bluePin = 10;
    leftData.greenPin = 11;

    TrafficData topData;

    this->rightTraffic = new IrTraffic(rightData);
    this->leftTraffic = new IrTraffic(leftData);

    this->rightTraffic->setup();
    this->leftTraffic->setup();
    Serial.begin(115200);
    Serial.println("SYSTEM STARTING");
}

void TrafficSystem::loop() {
    Traffic::Time currentMillis = millis();
    this->rightTraffic->loop();
    this->leftTraffic->loop();

    bool rightHumanCrossing = this->rightTraffic->isHumanCrossing();
    Serial.println(rightHumanCrossing);

    // checking right traffic
    if (this->rightTraffic->isIncoming() && !this->rightTraffic->isHumanCrossing()) {
        Serial.println("incoming at right...");
        
        switch (this->leftTraffic->getState()) {
        case Traffic::RED:
            if (this->rightTraffic->getState() == Traffic::RED || (currentMillis - this->rightTraffic->goTime <= YELLOW_WAIT_TIME)) {
                this->rightTraffic->switchState(Traffic::YELLOW);
            }
            else if ((currentMillis - this->rightTraffic->goTime > YELLOW_WAIT_TIME) && (currentMillis - this->leftTraffic->waitTime <= MAX_WAIT_TIME)) {
                this->rightTraffic->switchState(Traffic::GREEN);
                this->rightTraffic->waitTime = currentMillis;
            }
            else {
                this->rightTraffic->switchState(Traffic::RED);
                this->rightTraffic->goTime = currentMillis;
            }
            break;
        case Traffic::YELLOW:
            this->rightTraffic->switchState(Traffic::RED);
            this->rightTraffic->goTime = currentMillis;
            break;
        default:
            this->rightTraffic->switchState(Traffic::RED);
            this->rightTraffic->goTime = currentMillis;
            break;
        }
    }
    else {
        this->rightTraffic->switchState(Traffic::RED);
        this->rightTraffic->goTime = currentMillis;
        this->rightTraffic->waitTime = currentMillis;
    }

    // cheching left traffic
    if (this->leftTraffic->isIncoming() && !this->leftTraffic->isHumanCrossing()) {
        // Serial.println("incoming at left...");
        switch (this->rightTraffic->getState()) {
        case Traffic::RED:
            // Serial.println("No car at right traffic yet!!!");
            // Serial.println("Get ready...");
            if (this->leftTraffic->getState() == Traffic::RED || (currentMillis - this->leftTraffic->goTime <= YELLOW_WAIT_TIME)) {
                this->leftTraffic->switchState(Traffic::YELLOW);
            }
            else if ((currentMillis - this->leftTraffic->goTime > YELLOW_WAIT_TIME) && (currentMillis - this->rightTraffic->waitTime <= MAX_WAIT_TIME)) {
                this->leftTraffic->switchState(Traffic::GREEN);
                this->leftTraffic->waitTime = currentMillis;
            }
            else {
                this->leftTraffic->switchState(Traffic::RED);
                this->leftTraffic->goTime = currentMillis;
            }
            break;
        case Traffic::YELLOW:
            this->leftTraffic->switchState(Traffic::RED);
            this->leftTraffic->goTime = currentMillis;
            break;
        default:
            this->leftTraffic->switchState(Traffic::RED);
            this->leftTraffic->goTime = currentMillis;
            break;
        }
    }
    else {
        this->leftTraffic->switchState(Traffic::RED);
        this->leftTraffic->goTime = currentMillis;
        this->leftTraffic->waitTime = currentMillis;
    }

}