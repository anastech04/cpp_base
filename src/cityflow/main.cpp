#include "Simulation.hpp"

#include <iostream>
#include <string>

void printComparisonResult(const std::string& name, const cityflow::SimulationStats& stats) {
    std::cout << "\n" << name << " mode result:\n";
    std::cout << "Steps: " << stats.steps << "\n";
    std::cout << "Arrived vehicles: " << stats.arrivedVehicles << "\n";
    std::cout << "Average waiting time: " << stats.averageWaitingTime << "\n";
    std::cout << "Average travel time: " << stats.averageTravelTime << "\n";
    std::cout << "Total congestion events: "
              << stats.northCongestionEvents + stats.eastCongestionEvents << "\n";
}

int main() {
    cityflow::Simulation simulation;

    std::cout << "CityFlow - Traffic Flow Simulator\n";
    std::cout << "Focus: simulation logic, traffic lights, waiting times, congestion.\n";
    std::cout << "Type HELP to see commands.\n";

    std::string command;

    while (true) {
        std::cout << "\nCityFlow> ";
        std::getline(std::cin, command);

        if (command == "EXIT" || command == "exit") {
            std::cout << "Simulation closed.\n";
            break;
        }

        if (command == "HELP" || command == "help") {
            std::cout << "Available commands:\n";
            std::cout << "  HELP     - Show commands\n";
            std::cout << "  START    - Start simulation\n";
            std::cout << "  STEP     - Run one simulation step\n";
            std::cout << "  STATUS   - Show current traffic status\n";
            std::cout << "  STATS    - Show simulation statistics\n";
            std::cout << "  FIXED    - Use fixed traffic light timing\n";
            std::cout << "  ADAPT    - Use adaptive traffic light timing\n";
            std::cout << "  COMPARE  - Compare fixed and adaptive mode\n";
            std::cout << "  EXIT     - Close program\n";
            continue;
        }

        if (command == "START" || command == "start") {
            simulation.start();
            continue;
        }

        if (command == "STEP" || command == "step") {
            simulation.step();
            continue;
        }

        if (command == "STATUS" || command == "status") {
            simulation.printStatus();
            continue;
        }

        if (command == "STATS" || command == "stats") {
            simulation.printStatistics();
            continue;
        }

        if (command == "FIXED" || command == "fixed") {
            simulation.useFixedMode();
            continue;
        }

        if (command == "ADAPT" || command == "adapt" ||
            command == "ADAPTIVE" || command == "adaptive") {
            simulation.useAdaptiveMode();
            continue;
        }

        if (command == "COMPARE" || command == "compare") {
            const int comparisonSteps = 30;

            cityflow::Simulation fixedSimulation;
            fixedSimulation.useFixedMode(false);
            fixedSimulation.runSteps(comparisonSteps, false);

            cityflow::Simulation adaptiveSimulation;
            adaptiveSimulation.useAdaptiveMode(false);
            adaptiveSimulation.runSteps(comparisonSteps, false);

            std::cout << "\nComparison after " << comparisonSteps << " simulation steps:\n";
            printComparisonResult("Fixed", fixedSimulation.getStatistics());
            printComparisonResult("Adaptive", adaptiveSimulation.getStatistics());

            continue;
        }

        std::cout << "Unknown command: " << command << "\n";
    }

    return 0;
}