#include "TrafficSystem.hpp"

void TrafficSystem::setup() {
    TrafficData rightData;
    rightData.triggerPin = 2;
    // rightData.echoPin = 3;
    rightData.humanButton = 3;


    rightData.redPin = 4;
    rightData.bluePin = 5;
    rightData.greenPin = 6;

    TrafficData leftData;
    leftData.triggerPin = 9;
    leftData.humanButton = 8;

    leftData.redPin = 10;
    leftData.greenPin = 11;
    leftData.bluePin = 12;


    TrafficData topData;

    this->rightTraffic = new IrTraffic(rightData);
    this->leftTraffic = new IrTraffic(leftData);

    this->rightTraffic->setup();
    this->leftTraffic->setup();
    Serial.begin(9600);
    Serial.println("Connected");
    emergencyTime = millis();
    this->cmd = "";
}

void TrafficSystem::loop() {
    Traffic::Time currentMillis = millis();
    this->rightTraffic->loop();
    this->leftTraffic->loop();

    char cmd = this->readCommand();

    if (cmd == NULL) {
        // checking right traffic
        bool isRCrossing = this->rightTraffic->isHumanCrossing();
        if (this->rightTraffic->isIncoming() && !isRCrossing) {
            this->analiseRightTraffic(currentMillis);
        }
        else {
            if (isRCrossing) {
                this->rightTraffic->switchState(Traffic::HUMAN);
                this->sendMessage(*this->rightTraffic, TrafficState::RHUMAN);
            }
            else {
                this->rightTraffic->switchState(Traffic::RED);
                this->sendMessage(*this->rightTraffic, TrafficState::NORHUMAN);
            }
            this->rightTraffic->goTime = currentMillis;
            this->rightTraffic->waitTime = currentMillis;
        }

        // cheching left traffic
        bool isLCrossing = this->leftTraffic->isHumanCrossing();
        if (this->leftTraffic->isIncoming() && !isLCrossing) {
            this->analiseLeftTraffic(currentMillis);
        }
        else {
            if (isLCrossing) {
                this->leftTraffic->switchState(Traffic::HUMAN);
                this->sendMessage(*this->leftTraffic, TrafficState::LHUMAN);
            }
            else {
                this->leftTraffic->switchState(Traffic::RED);
                this->sendMessage(*this->leftTraffic, TrafficState::NOLHUMAN);
            }
            this->leftTraffic->goTime = currentMillis;
            this->leftTraffic->waitTime = currentMillis;
        }
    }
    else  {
            this->analiseSerialCommand(cmd, currentMillis);
        }
}


char TrafficSystem::readCommand() {
    char cmd;
    while (Serial.available()) {
        cmd = Serial.read();
    }
    return cmd;
}

void TrafficSystem::sendMessage(IrTraffic& traffic, TrafficState state) {
    if (traffic.getPrevState() != traffic.getState()) {
        Serial.print(state);
        traffic.updateState();
    }
}

void TrafficSystem::analiseRightTraffic(Traffic::Time currentMillis) {
    switch (this->leftTraffic->getState()) {
    case Traffic::RED:
        if (this->rightTraffic->getState() == Traffic::RED || (currentMillis - this->rightTraffic->goTime <= YELLOW_WAIT_TIME)) {
            this->rightTraffic->switchState(Traffic::YELLOW);
            this->sendMessage(*this->rightTraffic, TrafficState::RYELLOW);
        }
        else if ((currentMillis - this->rightTraffic->goTime > YELLOW_WAIT_TIME) && (currentMillis - this->leftTraffic->waitTime <= MAX_WAIT_TIME)) {
            this->rightTraffic->switchState(Traffic::GREEN);
            this->sendMessage(*this->rightTraffic, TrafficState::RGREEN);
            this->rightTraffic->waitTime = currentMillis;
        }
        else {
            this->rightTraffic->switchState(Traffic::RED);
            this->sendMessage(*this->rightTraffic, TrafficState::RRED);
            this->rightTraffic->goTime = currentMillis;
        }
        break;
    case Traffic::YELLOW:
        this->rightTraffic->switchState(Traffic::RED);
        this->sendMessage(*this->rightTraffic, TrafficState::RRED);
        this->rightTraffic->goTime = currentMillis;
        break;
    default:
        this->rightTraffic->switchState(Traffic::RED);
        this->sendMessage(*this->rightTraffic, TrafficState::RRED);
        this->rightTraffic->goTime = currentMillis;
        break;
    }
}

void TrafficSystem::analiseLeftTraffic(Traffic::Time currentMillis) {
    switch (this->rightTraffic->getState()) {
    case Traffic::RED:
        if (this->leftTraffic->getState() == Traffic::RED || (currentMillis - this->leftTraffic->goTime <= YELLOW_WAIT_TIME)) {
            this->leftTraffic->switchState(Traffic::YELLOW);
            this->sendMessage(*this->leftTraffic, TrafficState::LYELLOW);

        }
        else if ((currentMillis - this->leftTraffic->goTime > YELLOW_WAIT_TIME) && (currentMillis - this->rightTraffic->waitTime <= MAX_WAIT_TIME)) {
            this->leftTraffic->switchState(Traffic::GREEN);
            this->sendMessage(*this->leftTraffic, TrafficState::LGREEN);
            this->leftTraffic->waitTime = currentMillis;
        }
        else {
            this->leftTraffic->switchState(Traffic::RED);
            this->sendMessage(*this->leftTraffic, TrafficState::LRED);
            this->leftTraffic->goTime = currentMillis;
        }
        break;
    case Traffic::YELLOW:
        this->leftTraffic->switchState(Traffic::RED);
        this->sendMessage(*this->leftTraffic, TrafficState::LRED);
        this->leftTraffic->goTime = currentMillis;
        break;
    default:
        this->leftTraffic->switchState(Traffic::RED);
        this->sendMessage(*this->leftTraffic, TrafficState::LRED);
        this->leftTraffic->goTime = currentMillis;
        break;
    }
}

void TrafficSystem::analiseSerialCommand(int cmd, Traffic::Time currentMillis) {
    switch (cmd) {
    case TrafficState::RRED:
        this->rightTraffic->switchState(Traffic::RED);
        this->rightTraffic->goTime = currentMillis;
        break;
    case TrafficState::RGREEN:
        this->rightTraffic->switchState(Traffic::GREEN);
        this->rightTraffic->waitTime = currentMillis;
        break;
    case TrafficState::LRED:
        this->leftTraffic->switchState(Traffic::RED);
        this->leftTraffic->goTime = currentMillis;
        break;
    case TrafficState::LGREEN:
        this->leftTraffic->switchState(Traffic::GREEN);
        this->leftTraffic->waitTime = currentMillis;
        break;
    default:
        break;
    }
}