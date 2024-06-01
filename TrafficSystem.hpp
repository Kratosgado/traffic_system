#if !defined(TRAFFIC_SYSTEM)
#define TRAFFIC_SYSTEM

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
