#if !defined(TRAFFIC)
#define TRAFFIC

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
    Traffic(/* args */) {};
    Traffic(int triggerPin, int echoPin, int redPin, int yellowPin, int greenPin) {
        this->triggerPin = triggerPin;
        this->echoPin = echoPin;
        this->redPin = redPin;
        this->yellowPin = yellowPin;
        this->greenPin = greenPin;
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
