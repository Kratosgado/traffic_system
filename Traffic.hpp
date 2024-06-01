#if !defined(TRAFFIC)
#define TRAFFIC

#include "Arduino.h"

struct TrafficData
{
    int triggerPin;
    int echoPin;
    int redPin;
    int yellowPin;
    int greenPin;
};


class Traffic {
public:
    enum State {
        RED,
        YELLOW,
        GREEN
     };
     
private:
    int triggerPin;
    int echoPin;
    int redPin;
    int yellowPin;
    int greenPin;

    State state;

    bool incoming;

public:
    Traffic(const TrafficData data) {
        this->triggerPin = data.triggerPin;
        this->echoPin = data.echoPin;
        this->redPin = data.redPin;
        this->yellowPin = data.yellowPin;
        this->greenPin = data.greenPin;
        this->state = RED;
        this->incoming = false;
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
