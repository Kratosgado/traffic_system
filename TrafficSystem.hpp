#if !defined(TRAFFIC_SYSTEM)
#define TRAFFIC_SYSTEM
#define MAX_GO_TIME 7000
#define MAX_WAIT_TIME 7000
#define YELLOW_WAIT_TIME 2000
#define EMERGENCY_WAIT_TIME 5000

#include "Traffic.hpp"
#include "IrTraffic.hpp"

enum TrafficState {
    RRED, RYELLOW, RGREEN, LRED, LYELLOW, LGREEN, RHUMAN, LHUMAN, NORHUMAN, NOLHUMAN
};

class TrafficSystem {
private:
    IrTraffic* rightTraffic;
    IrTraffic* leftTraffic;
    Traffic::Time emergencyTime;
    String cmd;

    // methods
    void analiseLeftTraffic(Traffic::Time currentMilis);
    void analiseRightTraffic(Traffic::Time currentMilie);
    void analiseSerialCommand(int cmd, Traffic::Time currentMillis);
    char readCommand();
    void sendMessage(IrTraffic& traffic, TrafficState state);


public:
    TrafficSystem() {};
    ~TrafficSystem();

    void setup();
    void loop();
};

#endif // TRAFFIC_SYSTEM
