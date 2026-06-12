#include <iostream>
#include <string>

int main() {
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
            std::cout << "  HELP   - Show commands\n";
            std::cout << "  START  - Start simulation\n";
            std::cout << "  STEP   - Run one simulation step\n";
            std::cout << "  STATS  - Show statistics\n";
            std::cout << "  EXIT   - Close program\n";
            continue;
        }

        if (command == "START" || command == "start") {
            std::cout << "Traffic simulation started.\n";
            continue;
        }

        if (command == "STEP" || command == "step") {
            std::cout << "Running one simulation step...\n";
            continue;
        }

        if (command == "STATS" || command == "stats") {
            std::cout << "Average travel time: 0\n";
            std::cout << "Average waiting time: 0\n";
            std::cout << "Congestion count: 0\n";
            continue;
        }

        std::cout << "Unknown command: " << command << "\n";
    }

    return 0;
}
