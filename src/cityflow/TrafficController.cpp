#include "TrafficController.hpp"

namespace cityflow {

TrafficController::TrafficController(int greenDuration, int yellowDuration)
    : phase(SignalPhase::NorthSouthGreen),
      mode(ControllerMode::Fixed),
      timer(0),
      greenDuration(greenDuration),
      yellowDuration(yellowDuration),
      maxAdaptiveGreenDuration(greenDuration + 4) {}

void TrafficController::update(int northQueueSize, int eastQueueSize) {
    ++timer;

    if (mode == ControllerMode::Fixed) {
        updateFixedMode();
    } else {
        updateAdaptiveMode(northQueueSize, eastQueueSize);
    }
}

void TrafficController::updateFixedMode() {
    switch (phase) {
        case SignalPhase::NorthSouthGreen:
        case SignalPhase::EastWestGreen:
            if (timer >= greenDuration) {
                switchToNextPhase();
            }
            break;

        case SignalPhase::NorthSouthYellow:
        case SignalPhase::EastWestYellow:
            if (timer >= yellowDuration) {
                switchToNextPhase();
            }
            break;
    }
}

void TrafficController::updateAdaptiveMode(int northQueueSize, int eastQueueSize) {
    switch (phase) {
        case SignalPhase::NorthSouthGreen:
            if (timer < greenDuration) {
                return;
            }

            if ((northQueueSize == 0 && eastQueueSize > 0) ||
                eastQueueSize > northQueueSize ||
                timer >= maxAdaptiveGreenDuration) {
                switchToNextPhase();
            }
            break;

        case SignalPhase::EastWestGreen:
            if (timer < greenDuration) {
                return;
            }

            if ((eastQueueSize == 0 && northQueueSize > 0) ||
                northQueueSize > eastQueueSize ||
                timer >= maxAdaptiveGreenDuration) {
                switchToNextPhase();
            }
            break;

        case SignalPhase::NorthSouthYellow:
        case SignalPhase::EastWestYellow:
            if (timer >= yellowDuration) {
                switchToNextPhase();
            }
            break;
    }
}

void TrafficController::setMode(ControllerMode newMode) {
    mode = newMode;
}

ControllerMode TrafficController::getMode() const {
    return mode;
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

std::string TrafficController::getModeName() const {
    if (mode == ControllerMode::Fixed) {
        return "Fixed";
    }

    return "Adaptive";
}

}