#if !defined(TRAFFIC_SYSTEM)
#define TRAFFIC_SYSTEM

#include "Arduino.h"
#include "Traffic.hpp"

class TrafficSystem
{
private:
    Traffic* rightTraffic;
    Traffic* leftTraffic;

public:
    TrafficSystem(/* args */);
    ~TrafficSystem();

    void setup();
    void loop();
    
};

TrafficSystem::TrafficSystem(/* args */)
{
}

TrafficSystem::~TrafficSystem()
{
}


#endif // TRAFFIC_SYSTEM
