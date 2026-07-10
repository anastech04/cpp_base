#pragma once

#include <map>
#include <string>
#include <vector>

namespace cityflow {

struct RoadConnection {
    std::string target;
    int travelTime;
    bool closed;
};

struct RouteResult {
    std::vector<std::string> path;
    int totalTravelTime = 0;
    bool found = false;
};

class CityGraph {
private:
    std::map<std::string, std::vector<RoadConnection>> adjacencyList;

public:
    void addIntersection(const std::string& name);
    void addRoad(const std::string& from, const std::string& to, int travelTime);
    void addBidirectionalRoad(const std::string& a, const std::string& b, int travelTime);

    void closeRoad(const std::string& from, const std::string& to);
    void openRoad(const std::string& from, const std::string& to);

    RouteResult findShortestPath(const std::string& start, const std::string& destination) const;
    void printGraph() const;
};

}