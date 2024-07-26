#if !defined(TRAFFIC_SYSTEM)
#define TRAFFIC_SYSTEM
#define MAX_GO_TIME 7000
#define MAX_WAIT_TIME 7000
#define YELLOW_WAIT_TIME 2000

#include "Traffic.hpp"
#include "IrTraffic.hpp"

enum TrafficState {
    RRED, RYELLOW, RGREEN, LRED, LYELLOW, LGREEN, RHUMAN, LHUMAN, NORHUMAN, NOLHUMAN
};

class TrafficSystem {
private:
    IrTraffic* rightTraffic;
    IrTraffic* leftTraffic;
    char cmd;

    // methods
    void analiseLeftTraffic(Traffic::Time currentMilis);
    void analiseRightTraffic(Traffic::Time currentMilie);
    char readCommand();
    void sendMessage(IrTraffic& traffic, TrafficState state);
    void analizeSerialCommand();


public:
    TrafficSystem() {};
    ~TrafficSystem();

    void setup();
    void loop();
};

#endif // TRAFFIC_SYSTEM
