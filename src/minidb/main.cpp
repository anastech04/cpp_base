#include <iostream>
#include <string>

int main() {
    std::cout << "MiniDB-Cpp started successfully.\n";
    std::cout << "Type HELP to see available commands.\n";

    std::string command;

    while (true) {
        std::cout << "\nMiniDB> ";
        std::getline(std::cin, command);

        if (command == "EXIT" || command == "exit") {
            std::cout << "Goodbye!\n";
            break;
        }

        if (command == "HELP" || command == "help") {
            std::cout << "Available commands:\n";
            std::cout << "  HELP  - Show commands\n";
            std::cout << "  EXIT  - Close the program\n";
            continue;
        }

        std::cout << "Unknown command: " << command << "\n";
    }

    return 0;
}
