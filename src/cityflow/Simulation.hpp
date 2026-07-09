#pragma once

#include "Road.hpp"
#include "TrafficController.hpp"

#include <vector>

namespace cityflow {

class Simulation {
private:
    int currentStep;
    int nextVehicleId;

    Road northRoad;
    Road eastRoad;

    TrafficController trafficController;

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