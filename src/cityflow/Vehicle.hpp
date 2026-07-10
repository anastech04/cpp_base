#pragma once

#include <string>
#include <vector>

namespace cityflow {

enum class VehicleState {
    Waiting,
    Driving,
    Arrived
};

class Vehicle {
private:
    int id;
    std::string startNode;
    std::string destinationNode;
    std::vector<std::string> route;
    int plannedTravelTime;
    int waitingTime;
    int travelTime;
    VehicleState state;

public:
    Vehicle(int id,
            std::string startNode,
            std::string destinationNode,
            std::vector<std::string> route = {},
            int plannedTravelTime = 1);

    int getId() const;
    int getWaitingTime() const;
    int getTravelTime() const;
    int getPlannedTravelTime() const;
    VehicleState getState() const;

    const std::vector<std::string>& getRoute() const;

    void addWaitingTime();
    void addTravelTime(int amount = 1);
    void markArrived();

    std::string stateToString() const;
    std::string routeToString() const;
};

}