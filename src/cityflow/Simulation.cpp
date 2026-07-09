#include "Simulation.hpp"

#include <iostream>

namespace cityflow {

Simulation::Simulation()
    : currentStep(0),
      nextVehicleId(1),
      northRoad("North Road", "North", "Center", 5),
      eastRoad("East Road", "East", "Center", 5),
      trafficController(3, 1),
      arrivedVehicles(0),
      totalWaitingTime(0),
      totalTravelTime(0) {}

void Simulation::start() {
    std::cout << "CityFlow simulation started.\n";
    std::cout << "Use STEP to run the simulation step by step.\n";
}

void Simulation::step() {
    ++currentStep;

    std::cout << "\n--- Simulation step " << currentStep << " ---\n";

    generateVehicles();
    updateTrafficLights();
    moveVehicles();
    printStatus();
}

void Simulation::generateVehicles() {
    if (currentStep % 2 == 0) {
        northRoad.addVehicle(Vehicle(nextVehicleId++, "North", "Center"));
        std::cout << "New vehicle added to North Road.\n";
    }

    if (currentStep % 3 == 0) {
        eastRoad.addVehicle(Vehicle(nextVehicleId++, "East", "Center"));
        std::cout << "New vehicle added to East Road.\n";
    }
}

void Simulation::updateTrafficLights() {
    trafficController.update(northRoad.getVehicleCount(), eastRoad.getVehicleCount());
}

void Simulation::moveVehicles() {
    auto northVehicle = northRoad.step(trafficController.canNorthSouthPass());

    if (northVehicle.has_value()) {
        ++arrivedVehicles;
        totalWaitingTime += northVehicle->getWaitingTime();
        totalTravelTime += northVehicle->getTravelTime();
        std::cout << "Vehicle passed from North Road.\n";
    }

    auto eastVehicle = eastRoad.step(trafficController.canEastWestPass());

    if (eastVehicle.has_value()) {
        ++arrivedVehicles;
        totalWaitingTime += eastVehicle->getWaitingTime();
        totalTravelTime += eastVehicle->getTravelTime();
        std::cout << "Vehicle passed from East Road.\n";
    }
}

void Simulation::printStatus() const {
    std::cout << "\nCurrent status:\n";
    std::cout << "Current phase: " << trafficController.getCurrentPhaseName() << "\n";
    std::cout << "North-South light: " << trafficController.getNorthSouthLightState() << "\n";
    std::cout << "East-West light: " << trafficController.getEastWestLightState() << "\n";

    std::cout << "Vehicles waiting on North Road: " << northRoad.getVehicleCount() << "\n";
    std::cout << "Vehicles waiting on East Road: " << eastRoad.getVehicleCount() << "\n";
}

void Simulation::printStatistics() const {
    std::cout << "\nSimulation statistics:\n";
    std::cout << "Current step: " << currentStep << "\n";
    std::cout << "Arrived vehicles: " << arrivedVehicles << "\n";
    std::cout << "North Road congestion events: " << northRoad.getCongestionEvents() << "\n";
    std::cout << "East Road congestion events: " << eastRoad.getCongestionEvents() << "\n";

    if (arrivedVehicles > 0) {
        std::cout << "Average waiting time: "
                  << static_cast<double>(totalWaitingTime) / arrivedVehicles << "\n";
        std::cout << "Average travel time: "
                  << static_cast<double>(totalTravelTime) / arrivedVehicles << "\n";
    } else {
        std::cout << "Average waiting time: 0\n";
        std::cout << "Average travel time: 0\n";
    }
}

}