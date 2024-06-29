#if !defined(TRAFFIC)
#define TRAFFIC

#define MAX_DISTANCE 10

#include "Arduino.h"

struct TrafficData {
    int triggerPin;
    int echoPin;
    int redPin;
    int bluePin;
    int greenPin;
};


class Traffic {
public:
    enum State {
        RED,
        YELLOW,
        GREEN
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

    // State
    State state;

    // Incoming
    bool incoming;


public:
    Time goTime;
    Time waitTime;
    Traffic(){};


    Traffic(const TrafficData& data) {
        this->triggerPin = data.triggerPin;
        this->echoPin = data.echoPin;
        this->redPin = data.redPin;
        this->bluePin = data.bluePin;
        this->greenPin = data.greenPin;
        this->state = RED;
        this->incoming = false;
        this->goTime = 0;
        this->waitTime = 0;
    }
    ~Traffic();

    void setup();
    void loop();
    void switchState(const State state);
    bool isIncoming() {
        return this->incoming;
    };
    Traffic::State getState() {
        return this->state;
    };
};

#endif // TRAFFIC
