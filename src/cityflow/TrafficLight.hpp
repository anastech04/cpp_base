#pragma once

#include <string>

namespace cityflow {

enum class LightState {
    Green,
    Yellow,
    Red
};

class TrafficLight {
private:
    LightState state;
    int timer;
    int greenDuration;
    int yellowDuration;
    int redDuration;

public:
    TrafficLight(int greenDuration, int yellowDuration, int redDuration);

    void update();

    LightState getState() const;
    bool isGreen() const;

    std::string stateToString() const;
};

}