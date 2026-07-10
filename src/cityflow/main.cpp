#include "Simulation.hpp"
#include "CityGraph.hpp"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

cityflow::CityGraph createSampleCityGraph() {
    cityflow::CityGraph graph;

    graph.addBidirectionalRoad("North", "Center", 3);
    graph.addBidirectionalRoad("East", "Center", 4);
    graph.addBidirectionalRoad("South", "Center", 3);
    graph.addBidirectionalRoad("West", "Center", 4);

    graph.addBidirectionalRoad("North", "East", 6);
    graph.addBidirectionalRoad("East", "South", 5);
    graph.addBidirectionalRoad("South", "West", 6);
    graph.addBidirectionalRoad("West", "North", 5);

    return graph;
}

void printComparisonResult(const std::string& name, const cityflow::SimulationStats& stats) {
    std::cout << "\n" << name << " mode result:\n";
    std::cout << "Steps: " << stats.steps << "\n";
    std::cout << "Arrived vehicles: " << stats.arrivedVehicles << "\n";
    std::cout << "Average waiting time: " << stats.averageWaitingTime << "\n";
    std::cout << "Average travel time: " << stats.averageTravelTime << "\n";
    std::cout << "Total congestion events: "
              << stats.northCongestionEvents + stats.eastCongestionEvents << "\n";
}
void printImprovementSummary(const cityflow::SimulationStats& fixedStats,
                             const cityflow::SimulationStats& adaptiveStats) {
    const double throughputImprovement =
        fixedStats.arrivedVehicles == 0
            ? 0.0
            : ((adaptiveStats.arrivedVehicles - fixedStats.arrivedVehicles) * 100.0)
                / fixedStats.arrivedVehicles;

    const double waitingTimeReduction =
        fixedStats.averageWaitingTime == 0
            ? 0.0
            : ((fixedStats.averageWaitingTime - adaptiveStats.averageWaitingTime) * 100.0)
                / fixedStats.averageWaitingTime;

    const double travelTimeReduction =
        fixedStats.averageTravelTime == 0
            ? 0.0
            : ((fixedStats.averageTravelTime - adaptiveStats.averageTravelTime) * 100.0)
                / fixedStats.averageTravelTime;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nAdaptive improvement summary:\n";
    std::cout << "Throughput improvement: " << throughputImprovement << "%\n";
    std::cout << "Waiting time reduction: " << waitingTimeReduction << "%\n";
    std::cout << "Travel time reduction: " << travelTimeReduction << "%\n";
    std::cout << std::defaultfloat << std::setprecision(6);
}
void exportComparisonResultsToCsv(const std::string& fileName,
                                  const cityflow::SimulationStats& fixedStats,
                                  const cityflow::SimulationStats& adaptiveStats) {
    std::ofstream file(fileName);

    if (!file) {
        std::cout << "Could not write CSV file: " << fileName << "\n";
        return;
    }

    file << "mode,steps,arrived_vehicles,average_waiting_time,average_travel_time,total_congestion_events\n";

    file << "Fixed,"
         << fixedStats.steps << ","
         << fixedStats.arrivedVehicles << ","
         << fixedStats.averageWaitingTime << ","
         << fixedStats.averageTravelTime << ","
         << fixedStats.northCongestionEvents + fixedStats.eastCongestionEvents << "\n";

    file << "Adaptive,"
         << adaptiveStats.steps << ","
         << adaptiveStats.arrivedVehicles << ","
         << adaptiveStats.averageWaitingTime << ","
         << adaptiveStats.averageTravelTime << ","
         << adaptiveStats.northCongestionEvents + adaptiveStats.eastCongestionEvents << "\n";

    std::cout << "\nCSV export written to: " << fileName << "\n";
}

int main() {
    cityflow::Simulation simulation;
    cityflow::CityGraph graph = createSampleCityGraph();

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
    std::cout << "  HELP      - Show available commands\n";
    std::cout << "  START     - Start simulation\n";
    std::cout << "  STEP      - Run one simulation step\n";
    std::cout << "  RUN       - Run multiple simulation steps\n";
    std::cout << "  STATUS    - Show current traffic status\n";
    std::cout << "  STATS     - Show simulation statistics\n";
    std::cout << "  FIXED     - Use fixed traffic light timing\n";
    std::cout << "  ADAPT     - Use adaptive traffic light timing\n";
    std::cout << "  COMPARE   - Compare fixed and adaptive mode\n";
    std::cout << "  BENCHMARK - Measure fixed and adaptive runtime\n";
    std::cout << "  EXPORT    - Export comparison results to CSV\n";
    std::cout << "  GRAPH     - Show road network\n";
    std::cout << "  ROUTE     - Calculate shortest route with Dijkstra\n";
    std::cout << "  CLOSE     - Close road North <-> Center\n";
    std::cout << "  OPEN      - Open road North <-> Center\n";
    std::cout << "  EXIT      - Close program\n";
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

            printImprovementSummary(fixedSimulation.getStatistics(),
                        adaptiveSimulation.getStatistics());

            continue;
        }
        if (command == "GRAPH" || command == "graph") {
    graph.printGraph();
    continue;
}

if (command == "ROUTE" || command == "route") {
    const auto route = graph.findShortestPath("North", "South");

    if (!route.found) {
        std::cout << "No route found.\n";
        continue;
    }

    std::cout << "\nShortest route from North to South:\n";

    for (size_t i = 0; i < route.path.size(); ++i) {
        std::cout << route.path[i];

        if (i + 1 < route.path.size()) {
            std::cout << " -> ";
        }
    }

    std::cout << "\nTotal travel time: " << route.totalTravelTime << "\n";
    continue;
}
if (command == "CLOSE" || command == "close") {
    graph.closeRoad("North", "Center");
    graph.closeRoad("Center", "North");

    std::cout << "Road between North and Center has been closed.\n";
    continue;
}

if (command == "OPEN" || command == "open") {
    graph.openRoad("North", "Center");
    graph.openRoad("Center", "North");

    std::cout << "Road between North and Center has been opened.\n";
    continue;
}
if (command == "BENCHMARK" || command == "benchmark") {
    const int benchmarkSteps = 5000;

    auto fixedStart = std::chrono::high_resolution_clock::now();

    cityflow::Simulation fixedSimulation;
    fixedSimulation.useFixedMode(false);
    fixedSimulation.runSteps(benchmarkSteps, false);

    auto fixedEnd = std::chrono::high_resolution_clock::now();

    auto adaptiveStart = std::chrono::high_resolution_clock::now();

    cityflow::Simulation adaptiveSimulation;
    adaptiveSimulation.useAdaptiveMode(false);
    adaptiveSimulation.runSteps(benchmarkSteps, false);

    auto adaptiveEnd = std::chrono::high_resolution_clock::now();

    const auto fixedDuration =
        std::chrono::duration_cast<std::chrono::milliseconds>(fixedEnd - fixedStart).count();

    const auto adaptiveDuration =
        std::chrono::duration_cast<std::chrono::milliseconds>(adaptiveEnd - adaptiveStart).count();

    std::cout << "\nBenchmark after " << benchmarkSteps << " simulation steps:\n";
    std::cout << "Fixed mode runtime: " << fixedDuration << " ms\n";
    std::cout << "Adaptive mode runtime: " << adaptiveDuration << " ms\n";

    printComparisonResult("Fixed", fixedSimulation.getStatistics());
    printComparisonResult("Adaptive", adaptiveSimulation.getStatistics());
    
    printImprovementSummary(fixedSimulation.getStatistics(),
                        adaptiveSimulation.getStatistics());

    continue;
}
if (command == "EXPORT" || command == "export") {
    cityflow::Simulation fixedSimulation;
    fixedSimulation.useFixedMode(false);
    fixedSimulation.runSteps(30, false);

    cityflow::Simulation adaptiveSimulation;
    adaptiveSimulation.useAdaptiveMode(false);
    adaptiveSimulation.runSteps(30, false);

    const auto fixedStats = fixedSimulation.getStatistics();
    const auto adaptiveStats = adaptiveSimulation.getStatistics();

    std::cout << "\nExport comparison after 30 simulation steps:\n";

    printComparisonResult("Fixed", fixedStats);
    printComparisonResult("Adaptive", adaptiveStats);

    printImprovementSummary(fixedStats, adaptiveStats);

    exportComparisonResultsToCsv("data/simulation_results.csv",
                                 fixedStats,
                                 adaptiveStats);

    continue;
}

        std::cout << "Unknown command: " << command << "\n";
    }

    return 0;
}