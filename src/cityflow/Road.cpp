#include "Road.hpp"

#include <iostream>
#include <utility>

namespace cityflow {

Road::Road(std::string name, std::string fromNode, std::string toNode, int capacity)
    : name(std::move(name)),
      fromNode(std::move(fromNode)),
      toNode(std::move(toNode)),
      capacity(capacity),
      passedVehicles(0),
      congestionEvents(0) {}

void Road::addVehicle(const Vehicle& vehicle) {
    if (static_cast<int>(vehicles.size()) >= capacity) {
        ++congestionEvents;
    }

    vehicles.push(vehicle);
}

std::optional<Vehicle> Road::step(bool canPass) {
    if (vehicles.empty()) {
        return std::nullopt;
    }

    if (!canPass) {
        updateWaitingTimes();
        return std::nullopt;
    }

    Vehicle vehicle = vehicles.front();
    vehicles.pop();

    vehicle.addTravelTime(vehicle.getPlannedTravelTime());
    vehicle.markArrived();

    ++passedVehicles;

    updateWaitingTimes();

    return vehicle;
}

void Road::updateWaitingTimes() {
    std::queue<Vehicle> updatedQueue;

    while (!vehicles.empty()) {
        Vehicle vehicle = vehicles.front();
        vehicles.pop();

        vehicle.addWaitingTime();
        updatedQueue.push(vehicle);
    }

    vehicles = std::move(updatedQueue);
}

const std::string& Road::getName() const {
    return name;
}

int Road::getVehicleCount() const {
    return static_cast<int>(vehicles.size());
}

int Road::getPassedVehicles() const {
    return passedVehicles;
}

int Road::getCongestionEvents() const {
    return congestionEvents;
}

}