#pragma once

#include "Road.hpp"
#include "TrafficLight.hpp"

#include <vector>

namespace cityflow {

class Simulation {
private:
    int currentStep;
    int nextVehicleId;

    Road northRoad;
    Road eastRoad;

    TrafficLight northSouthLight;
    TrafficLight eastWestLight;

    int arrivedVehicles;
    int totalWaitingTime;
    int totalTravelTime;

public:
    Simulation();

    void start();
    void step();
    void printStatus() const;
    void printStatistics() const;

private:
    void generateVehicles();
    void updateTrafficLights();
    void moveVehicles();
};

}