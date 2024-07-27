#if !defined(TRAFFIC)
#define TRAFFIC

#define MAX_DISTANCE 10
#define HUMAN_CROSS_TIME 5000

#include "Arduino.h"

struct TrafficData {
    int triggerPin;
    int echoPin;
    int redPin;
    int bluePin;
    int greenPin;
    int humanButton;
};


class Traffic {
public:
    enum State {
        RED,
        YELLOW,
        GREEN,
        HUMAN,
        NOHUMAN,
    };
    typedef unsigned long Time;

private:
    // Pins
    int triggerPin;
    int echoPin;

protected:
    int redPin;
    int bluePin;
    int greenPin;
    int humanButton;

    // State
    State state;
    State prevState;

    // Incoming
    bool incoming;

    // human crossing time
    Time humanCrossTime;


public:
    Time goTime;
    Time waitTime;
    Traffic() {};


    Traffic(const TrafficData& data) {
        this->triggerPin = data.triggerPin;
        this->echoPin = data.echoPin;
        this->redPin = data.redPin;
        this->bluePin = data.bluePin;
        this->greenPin = data.greenPin;
        this->humanButton = data.humanButton;
        this->state = RED;
        this->prevState = RED;
        this->incoming = false;
        this->goTime = 0;
        this->waitTime = 0;
        this->humanCrossTime = 0;
    }
    ~Traffic();

    void setup();
    void loop();
    bool isHumanCrossing();

    void switchState(const State state);
    bool isIncoming() {
        return this->incoming;
    };
    Traffic::State getState() {
        return this->state;
    };

    Traffic::State getPrevState() {
        return this->prevState;
    }
    void updateState() {
        this->prevState = this->state;
    }
};

#endif // TRAFFIC
