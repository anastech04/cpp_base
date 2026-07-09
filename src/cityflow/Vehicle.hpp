#pragma once

#include <string>

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
    int waitingTime;
    int travelTime;
    VehicleState state;

public:
    Vehicle(int id, std::string startNode, std::string destinationNode);

    int getId() const;
    int getWaitingTime() const;
    int getTravelTime() const;
    VehicleState getState() const;

    void addWaitingTime();
    void addTravelTime();
    void markArrived();

    std::string stateToString() const;
};

}