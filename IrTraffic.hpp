#if !defined(IR_TRAFFIC)
#define IR_TRAFFIC

#include "Traffic.hpp"

class IrTraffic : public Traffic {
private:
    int irSensorPin;
    int sensorStatus;

public:
    IrTraffic(const TrafficData& data) {
        this->bluePin = data.bluePin;
        this->redPin = data.redPin;
        this->greenPin = data.greenPin;
        this->irSensorPin = data.triggerPin;
        this->humanButton = data.humanButton;
        this->state = RED;
        this->incoming = false;
        this->goTime = 0;
        this->waitTime = 0;
        this->humanCrossTime = 0;
    };

    void setup();
    void loop();
};

#endif // IR_TRAFFIC
