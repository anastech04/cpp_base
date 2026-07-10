#pragma once

#include <string>

namespace cityflow {

enum class SignalPhase {
    NorthSouthGreen,
    NorthSouthYellow,
    EastWestGreen,
    EastWestYellow
};

enum class ControllerMode {
    Fixed,
    Adaptive
};

class TrafficController {
private:
    SignalPhase phase;
    ControllerMode mode;

    int timer;
    int greenDuration;
    int yellowDuration;
    int maxAdaptiveGreenDuration;

public:
    TrafficController(int greenDuration, int yellowDuration);

    void update(int northQueueSize, int eastQueueSize);

    void setMode(ControllerMode newMode);
    ControllerMode getMode() const;

    bool canNorthSouthPass() const;
    bool canEastWestPass() const;

    std::string getNorthSouthLightState() const;
    std::string getEastWestLightState() const;
    std::string getCurrentPhaseName() const;
    std::string getModeName() const;

private:
    void updateFixedMode();
    void updateAdaptiveMode(int northQueueSize, int eastQueueSize);
    void switchToNextPhase();
};

}