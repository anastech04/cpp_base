#include "TrafficController.hpp"

namespace cityflow {

TrafficController::TrafficController(int greenDuration, int yellowDuration)
    : phase(SignalPhase::NorthSouthGreen),
      timer(0),
      greenDuration(greenDuration),
      yellowDuration(yellowDuration) {}

void TrafficController::update(int northQueueSize, int eastQueueSize) {
    (void)northQueueSize;
    (void)eastQueueSize;

    ++timer;

    switch (phase) {
        case SignalPhase::NorthSouthGreen:
            if (timer >= greenDuration) {
                switchToNextPhase();
            }
            break;

        case SignalPhase::NorthSouthYellow:
            if (timer >= yellowDuration) {
                switchToNextPhase();
            }
            break;

        case SignalPhase::EastWestGreen:
            if (timer >= greenDuration) {
                switchToNextPhase();
            }
            break;

        case SignalPhase::EastWestYellow:
            if (timer >= yellowDuration) {
                switchToNextPhase();
            }
            break;
    }
}

void TrafficController::switchToNextPhase() {
    timer = 0;

    switch (phase) {
        case SignalPhase::NorthSouthGreen:
            phase = SignalPhase::NorthSouthYellow;
            break;

        case SignalPhase::NorthSouthYellow:
            phase = SignalPhase::EastWestGreen;
            break;

        case SignalPhase::EastWestGreen:
            phase = SignalPhase::EastWestYellow;
            break;

        case SignalPhase::EastWestYellow:
            phase = SignalPhase::NorthSouthGreen;
            break;
    }
}

bool TrafficController::canNorthSouthPass() const {
    return phase == SignalPhase::NorthSouthGreen;
}

bool TrafficController::canEastWestPass() const {
    return phase == SignalPhase::EastWestGreen;
}

std::string TrafficController::getNorthSouthLightState() const {
    if (phase == SignalPhase::NorthSouthGreen) {
        return "Green";
    }

    if (phase == SignalPhase::NorthSouthYellow) {
        return "Yellow";
    }

    return "Red";
}

std::string TrafficController::getEastWestLightState() const {
    if (phase == SignalPhase::EastWestGreen) {
        return "Green";
    }

    if (phase == SignalPhase::EastWestYellow) {
        return "Yellow";
    }

    return "Red";
}

std::string TrafficController::getCurrentPhaseName() const {
    switch (phase) {
        case SignalPhase::NorthSouthGreen:
            return "North-South Green";
        case SignalPhase::NorthSouthYellow:
            return "North-South Yellow";
        case SignalPhase::EastWestGreen:
            return "East-West Green";
        case SignalPhase::EastWestYellow:
            return "East-West Yellow";
    }

    return "Unknown";
}

}