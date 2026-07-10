#pragma once

#include "Road.hpp"
#include "TrafficController.hpp"

namespace cityflow {

struct SimulationStats {
    int steps = 0;
    int arrivedVehicles = 0;
    int northCongestionEvents = 0;
    int eastCongestionEvents = 0;
    double averageWaitingTime = 0.0;
    double averageTravelTime = 0.0;
};

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
    void step(bool verbose = true);
    void runSteps(int numberOfSteps, bool verbose = false);

    void printStatus() const;
    void printStatistics() const;
    SimulationStats getStatistics() const;

    void useFixedMode(bool verbose = true);
    void useAdaptiveMode(bool verbose = true);

private:
    void generateVehicles(bool verbose);
    void updateTrafficLights();
    void moveVehicles(bool verbose);
};

}