#pragma once

#include <string>

namespace cityflow {

enum class SignalPhase {
    NorthSouthGreen,
    NorthSouthYellow,
    EastWestGreen,
    EastWestYellow
};

class TrafficController {
private:
    SignalPhase phase;
    int timer;
    int greenDuration;
    int yellowDuration;

public:
    TrafficController(int greenDuration, int yellowDuration);

    void update(int northQueueSize, int eastQueueSize);

    bool canNorthSouthPass() const;
    bool canEastWestPass() const;

    std::string getNorthSouthLightState() const;
    std::string getEastWestLightState() const;
    std::string getCurrentPhaseName() const;

private:
    void switchToNextPhase();
};

}