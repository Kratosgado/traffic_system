#include "Traffic.hpp"

void Traffic::setup() {
    pinMode(this->redPin, OUTPUT);
    pinMode(this->bluePin, OUTPUT);
    pinMode(this->greenPin, OUTPUT);

    pinMode(this->triggerPin, OUTPUT);
    pinMode(this->echoPin, INPUT);
    pinMode(this->humanButton, INPUT);

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

    if (distance < MAX_DISTANCE and distance > 1) {
        this->incoming = true;
        return;
    }
    this->incoming = false;
}

bool Traffic::isHumanCrossing() {
    Time currentMillis = millis();
    if (digitalRead(this->humanButton) == HIGH) {
        this->humanCrossTime = currentMillis;
        return true;
    }
    return (currentMillis - this->humanCrossTime <= HUMAN_CROSS_TIME);
}

void Traffic::switchState(const State state) {
    digitalWrite(this->redPin, LOW);
    digitalWrite(this->bluePin, LOW);
    digitalWrite(this->greenPin, LOW);

    switch (state) {
    case Human:
    case RED:
        digitalWrite(this->redPin, HIGH);
        break;
    case YELLOW:
        digitalWrite(this->greenPin, HIGH);
        digitalWrite(this->redPin, HIGH);
        break;
    case GREEN:
        digitalWrite(this->greenPin, HIGH);
        break;
    default:
        break;
    }
    this->state = state;
}