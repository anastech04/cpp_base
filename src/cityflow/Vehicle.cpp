#include "Vehicle.hpp"

#include <utility>

namespace cityflow {

Vehicle::Vehicle(int id, std::string startNode, std::string destinationNode)
    : id(id),
      startNode(std::move(startNode)),
      destinationNode(std::move(destinationNode)),
      waitingTime(0),
      travelTime(0),
      state(VehicleState::Waiting) {}

int Vehicle::getId() const {
    return id;
}

int Vehicle::getWaitingTime() const {
    return waitingTime;
}

int Vehicle::getTravelTime() const {
    return travelTime;
}

VehicleState Vehicle::getState() const {
    return state;
}

void Vehicle::addWaitingTime() {
    ++waitingTime;
}

void Vehicle::addTravelTime() {
    ++travelTime;
    state = VehicleState::Driving;
}

void Vehicle::markArrived() {
    state = VehicleState::Arrived;
}

std::string Vehicle::stateToString() const {
    switch (state) {
        case VehicleState::Waiting:
            return "Waiting";
        case VehicleState::Driving:
            return "Driving";
        case VehicleState::Arrived:
            return "Arrived";
    }

    return "Unknown";
}

}