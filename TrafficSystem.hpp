#if !defined(TRAFFIC_SYSTEM)
#define TRAFFIC_SYSTEM
#define MAX_GO_TIME 30
#define MAX_WAIT_TIME 30

#include "Traffic.hpp"

class TrafficSystem {
private:
    Traffic* rightTraffic;
    Traffic* leftTraffic;

public:
    TrafficSystem(){};
    ~TrafficSystem();

    void setup();
    void loop();

};

#endif // TRAFFIC_SYSTEM
