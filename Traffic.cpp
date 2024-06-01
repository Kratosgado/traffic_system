#include "Traffic.hpp"

void Traffic::setup() {
    pinMode(this->redPin, OUTPUT);
    pinMode(this->yellowPin, OUTPUT);
    pinMode(this->greenPin, OUTPUT);

    pinMode(this->triggerPin, OUTPUT);
    pinMode(this->echoPin, INPUT);

    this->switchState(RED);
}

void Traffic::loop() {
    long duration, distance;
    digitalWrite(this->triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(this->triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->triggerPin, LOW);
    duration = pulseIn(this->echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 10) {
        this->incoming = !incoming;
        return;
    }
    this->incoming = !incoming;
}

void Traffic::switchState(const State state) {
    digitalWrite(this->redPin, LOW);
    digitalWrite(this->yellowPin, LOW);
    digitalWrite(this->greenPin, LOW);

    switch (state) {
    case RED:
        digitalWrite(this->redPin, HIGH);
        break;
    case YELLOW:
        digitalWrite(this->yellowPin, HIGH);
        break;
    case GREEN:
        digitalWrite(this->greenPin, HIGH);
        break;
    default:
        break;
    }
    this->state = state;
}