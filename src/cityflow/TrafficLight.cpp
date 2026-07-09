#include "TrafficLight.hpp"

namespace cityflow {

TrafficLight::TrafficLight(int greenDuration, int yellowDuration, int redDuration)
    : state(LightState::Green),
      timer(0),
      greenDuration(greenDuration),
      yellowDuration(yellowDuration),
      redDuration(redDuration) {}

void TrafficLight::update() {
    ++timer;

    if (state == LightState::Green && timer >= greenDuration) {
        state = LightState::Yellow;
        timer = 0;
    } else if (state == LightState::Yellow && timer >= yellowDuration) {
        state = LightState::Red;
        timer = 0;
    } else if (state == LightState::Red && timer >= redDuration) {
        state = LightState::Green;
        timer = 0;
    }
}

LightState TrafficLight::getState() const {
    return state;
}

bool TrafficLight::isGreen() const {
    return state == LightState::Green;
}

std::string TrafficLight::stateToString() const {
    switch (state) {
        case LightState::Green:
            return "Green";
        case LightState::Yellow:
            return "Yellow";
        case LightState::Red:
            return "Red";
    }

    return "Unknown";
}

}