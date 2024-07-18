#include "IrTraffic.hpp"

void IrTraffic::setup() {
    pinMode(this->redPin, OUTPUT);
    pinMode(this->bluePin, OUTPUT);
    pinMode(this->greenPin, OUTPUT);

    pinMode(this->irSensorPin, INPUT);
    pinMode(this->humanButton, INPUT);

    this->switchState(RED);
}

void IrTraffic::loop() {
    if (digitalRead(irSensorPin) == 0) {
        this->incoming = true;
        return;
    }
    this->incoming = false;

}