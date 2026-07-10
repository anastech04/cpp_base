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
    int waitingTime;
    int travelTime;
    VehicleState state;

public:
    Vehicle(int id,
            std::string startNode,
            std::string destinationNode,
            std::vector<std::string> route = {});

    int getId() const;
    int getWaitingTime() const;
    int getTravelTime() const;
    VehicleState getState() const;

    const std::vector<std::string>& getRoute() const;

    void addWaitingTime();
    void addTravelTime();
    void markArrived();

    std::string stateToString() const;
    std::string routeToString() const;
};

}