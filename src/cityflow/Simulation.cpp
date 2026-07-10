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

void Simulation::useFixedMode(bool verbose) {
    trafficController.setMode(ControllerMode::Fixed);

    if (verbose) {
        std::cout << "Traffic controller mode set to FIXED.\n";
    }
}

void Simulation::useAdaptiveMode(bool verbose) {
    trafficController.setMode(ControllerMode::Adaptive);

    if (verbose) {
        std::cout << "Traffic controller mode set to ADAPTIVE.\n";
    }
}

void Simulation::step(bool verbose) {
    ++currentStep;

    if (verbose) {
        std::cout << "\n--- Simulation step " << currentStep << " ---\n";
    }

    generateVehicles(verbose);
    updateTrafficLights();
    moveVehicles(verbose);

    if (verbose) {
        printStatus();
    }
}

void Simulation::runSteps(int numberOfSteps, bool verbose) {
    for (int i = 0; i < numberOfSteps; ++i) {
        step(verbose);
    }
}

void Simulation::generateVehicles(bool verbose) {
    if (currentStep % 2 == 0) {
        northRoad.addVehicle(Vehicle(nextVehicleId++, "North", "Center"));

        if (verbose) {
            std::cout << "New vehicle added to North Road.\n";
        }
    }

    if (currentStep % 3 == 0) {
        eastRoad.addVehicle(Vehicle(nextVehicleId++, "East", "Center"));

        if (verbose) {
            std::cout << "New vehicle added to East Road.\n";
        }
    }
}

void Simulation::updateTrafficLights() {
    trafficController.update(northRoad.getVehicleCount(), eastRoad.getVehicleCount());
}

void Simulation::moveVehicles(bool verbose) {
    auto northVehicle = northRoad.step(trafficController.canNorthSouthPass());

    if (northVehicle.has_value()) {
        ++arrivedVehicles;
        totalWaitingTime += northVehicle->getWaitingTime();
        totalTravelTime += northVehicle->getTravelTime();

        if (verbose) {
            std::cout << "Vehicle passed from North Road.\n";
        }
    }

    auto eastVehicle = eastRoad.step(trafficController.canEastWestPass());

    if (eastVehicle.has_value()) {
        ++arrivedVehicles;
        totalWaitingTime += eastVehicle->getWaitingTime();
        totalTravelTime += eastVehicle->getTravelTime();

        if (verbose) {
            std::cout << "Vehicle passed from East Road.\n";
        }
    }
}

void Simulation::printStatus() const {
    std::cout << "\nCurrent status:\n";
    std::cout << "Controller mode: " << trafficController.getModeName() << "\n";
    std::cout << "Current phase: " << trafficController.getCurrentPhaseName() << "\n";
    std::cout << "North-South light: " << trafficController.getNorthSouthLightState() << "\n";
    std::cout << "East-West light: " << trafficController.getEastWestLightState() << "\n";

    std::cout << "Vehicles waiting on North Road: " << northRoad.getVehicleCount() << "\n";
    std::cout << "Vehicles waiting on East Road: " << eastRoad.getVehicleCount() << "\n";
}

SimulationStats Simulation::getStatistics() const {
    SimulationStats stats;

    stats.steps = currentStep;
    stats.arrivedVehicles = arrivedVehicles;
    stats.northCongestionEvents = northRoad.getCongestionEvents();
    stats.eastCongestionEvents = eastRoad.getCongestionEvents();

    if (arrivedVehicles > 0) {
        stats.averageWaitingTime = static_cast<double>(totalWaitingTime) / arrivedVehicles;
        stats.averageTravelTime = static_cast<double>(totalTravelTime) / arrivedVehicles;
    }

    return stats;
}

void Simulation::printStatistics() const {
    const SimulationStats stats = getStatistics();

    std::cout << "\nSimulation statistics:\n";
    std::cout << "Current step: " << stats.steps << "\n";
    std::cout << "Arrived vehicles: " << stats.arrivedVehicles << "\n";
    std::cout << "North Road congestion events: " << stats.northCongestionEvents << "\n";
    std::cout << "East Road congestion events: " << stats.eastCongestionEvents << "\n";
    std::cout << "Average waiting time: " << stats.averageWaitingTime << "\n";
    std::cout << "Average travel time: " << stats.averageTravelTime << "\n";
}

}