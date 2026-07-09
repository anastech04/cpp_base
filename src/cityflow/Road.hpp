#pragma once

#include "Vehicle.hpp"

#include <optional>
#include <queue>
#include <string>

namespace cityflow {

class Road {
private:
    std::string name;
    std::string fromNode;
    std::string toNode;
    int capacity;
    std::queue<Vehicle> vehicles;
    int passedVehicles;
    int congestionEvents;

    void updateWaitingTimes();

public:
    Road(std::string name, std::string fromNode, std::string toNode, int capacity);

    void addVehicle(const Vehicle& vehicle);
    std::optional<Vehicle> step(bool canPass);

    const std::string& getName() const;
    int getVehicleCount() const;
    int getPassedVehicles() const;
    int getCongestionEvents() const;
};

}