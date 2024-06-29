#if !defined(TRAFFIC_SYSTEM)
#define TRAFFIC_SYSTEM
#define MAX_GO_TIME 7000
#define MAX_WAIT_TIME 7000

#include "Traffic.hpp"
#include "IrTraffic.hpp"

class TrafficSystem {
private:
    Traffic* rightTraffic;
    IrTraffic* leftTraffic;

public:
    TrafficSystem() {};
    ~TrafficSystem();

    void setup();
    void loop();


};

#endif // TRAFFIC_SYSTEM
