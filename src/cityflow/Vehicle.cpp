#include "Vehicle.hpp"

#include <sstream>
#include <utility>

namespace cityflow {

Vehicle::Vehicle(int id,
                 std::string startNode,
                 std::string destinationNode,
                 std::vector<std::string> route)
    : id(id),
      startNode(std::move(startNode)),
      destinationNode(std::move(destinationNode)),
      route(std::move(route)),
      waitingTime(0),
      travelTime(0),
      state(VehicleState::Waiting) {
    if (this->route.empty()) {
        this->route.push_back(this->startNode);
        this->route.push_back(this->destinationNode);
    }
}

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

const std::vector<std::string>& Vehicle::getRoute() const {
    return route;
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

std::string Vehicle::routeToString() const {
    std::ostringstream output;

    for (size_t i = 0; i < route.size(); ++i) {
        output << route[i];

        if (i + 1 < route.size()) {
            output << " -> ";
        }
    }

    return output.str();
}

}