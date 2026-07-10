#include "CityGraph.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <set>

namespace cityflow {

void CityGraph::addIntersection(const std::string& name) {
    if (!adjacencyList.contains(name)) {
        adjacencyList[name] = {};
    }
}

void CityGraph::addRoad(const std::string& from, const std::string& to, int travelTime) {
    addIntersection(from);
    addIntersection(to);

    adjacencyList[from].push_back(RoadConnection{to, travelTime, false});
}

void CityGraph::addBidirectionalRoad(const std::string& a, const std::string& b, int travelTime) {
    addRoad(a, b, travelTime);
    addRoad(b, a, travelTime);
}

void CityGraph::closeRoad(const std::string& from, const std::string& to) {
    for (auto& road : adjacencyList[from]) {
        if (road.target == to) {
            road.closed = true;
        }
    }
}

void CityGraph::openRoad(const std::string& from, const std::string& to) {
    for (auto& road : adjacencyList[from]) {
        if (road.target == to) {
            road.closed = false;
        }
    }
}

RouteResult CityGraph::findShortestPath(const std::string& start,
                                        const std::string& destination) const {
    const int infinity = std::numeric_limits<int>::max();

    std::map<std::string, int> distances;
    std::map<std::string, std::string> previous;
    std::set<std::string> visited;

    for (const auto& [node, roads] : adjacencyList) {
        distances[node] = infinity;
    }

    if (!adjacencyList.contains(start) || !adjacencyList.contains(destination)) {
        return {};
    }

    using QueueEntry = std::pair<int, std::string>;
    std::priority_queue<QueueEntry, std::vector<QueueEntry>, std::greater<>> queue;

    distances[start] = 0;
    queue.push({0, start});

    while (!queue.empty()) {
        auto [currentDistance, currentNode] = queue.top();
        queue.pop();

        if (visited.contains(currentNode)) {
            continue;
        }

        visited.insert(currentNode);

        if (currentNode == destination) {
            break;
        }

        for (const auto& road : adjacencyList.at(currentNode)) {
            if (road.closed) {
                continue;
            }

            int newDistance = currentDistance + road.travelTime;

            if (newDistance < distances[road.target]) {
                distances[road.target] = newDistance;
                previous[road.target] = currentNode;
                queue.push({newDistance, road.target});
            }
        }
    }

    if (distances[destination] == infinity) {
        return {};
    }

    std::vector<std::string> path;
    std::string current = destination;

    while (current != start) {
        path.push_back(current);
        current = previous[current];
    }

    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return RouteResult{path, distances[destination], true};
}

void CityGraph::printGraph() const {
    std::cout << "\nCity graph:\n";

    for (const auto& [intersection, roads] : adjacencyList) {
        std::cout << intersection << " -> ";

        for (const auto& road : roads) {
            std::cout << road.target << "(" << road.travelTime;

            if (road.closed) {
                std::cout << ", closed";
            }

            std::cout << ") ";
        }

        std::cout << "\n";
    }
}

}