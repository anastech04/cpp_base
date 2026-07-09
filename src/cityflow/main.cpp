#include "Simulation.hpp"

#include <iostream>
#include <string>

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
            std::cout << "  HELP    - Show commands\n";
            std::cout << "  START   - Start simulation\n";
            std::cout << "  STEP    - Run one simulation step\n";
            std::cout << "  STATUS  - Show current traffic status\n";
            std::cout << "  STATS   - Show simulation statistics\n";
            std::cout << "  EXIT    - Close program\n";
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

        std::cout << "Unknown command: " << command << "\n";
    }

    return 0;
}