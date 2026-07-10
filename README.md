# CityFlow – Traffic Flow Simulator with Adaptive Traffic Lights

CityFlow is a C++ traffic flow simulation project.  
It simulates vehicles moving through a small city road network and compares two traffic light strategies:

- Fixed traffic light control
- Adaptive traffic light control

The focus of the project is not graphical visualization, but realistic simulation logic, routing, statistics, and performance measurement.

---

## Project Idea

The city is modeled as a graph:

- Intersections are graph nodes
- Roads are graph edges
- Vehicles have a start point and a destination
- Routes are calculated automatically using Dijkstra's algorithm
- Traffic lights control whether vehicles can pass
- The simulation measures waiting time, travel time, congestion events, and throughput

The adaptive traffic light mode reacts to the current traffic situation and gives priority to roads with higher vehicle load.

---

## Main Features

- Graph-based city road network
- Dijkstra shortest path routing
- Vehicles with planned routes
- Fixed and adaptive traffic light control
- Step-by-step simulation mode
- Road closures and alternative routing
- Statistics calculation
- Fixed vs adaptive comparison
- Benchmarking with `std::chrono`
- CSV export of simulation results

---

## Technologies Used

- C++20
- CMake
- STL containers:
  - `vector`
  - `map`
  - `queue`
  - `priority_queue`
- Object-oriented programming
- Dijkstra algorithm
- File output with CSV
- Runtime measurement with `chrono`

---

## Build and Run

The project can be built with CMake.

Example run command on Windows:

```powershell
.\build\bin\Debug\cityflow.exe
```

---

## Available Commands

After starting the program, the following commands can be used:

```txt
HELP       - Show available commands
START      - Start the simulation
STEP       - Run one simulation step
RUN        - Run multiple simulation steps
STATS      - Show simulation statistics
FIXED      - Use fixed traffic light control
ADAPT      - Use adaptive traffic light control
COMPARE    - Compare fixed and adaptive traffic light control
BENCHMARK  - Measure runtime of fixed and adaptive simulations
EXPORT     - Export comparison results to CSV
GRAPH      - Show the city graph
ROUTE      - Show shortest route example
CLOSE      - Close a road and force alternative routing
OPEN       - Reopen the closed road
EXIT       - Close the program
```

---

## Example: Fixed vs Adaptive Comparison

Example output after 30 simulation steps:

```txt
Fixed mode result:
Steps: 30
Arrived vehicles: 20
Average waiting time: 3.25
Average travel time: 7
Total congestion events: 0

Adaptive mode result:
Steps: 30
Arrived vehicles: 22
Average waiting time: 2.59091
Average travel time: 6.72727
Total congestion events: 0

Adaptive improvement summary:
Throughput improvement: 10.00%
Waiting time reduction: 20.28%
Travel time reduction: 3.90%
```

This shows that the adaptive strategy improves traffic throughput and reduces waiting time.

---

## Benchmark Example

Example benchmark with 5000 simulation steps:

```txt
Fixed mode runtime: 5888 ms
Adaptive mode runtime: 2029 ms

Fixed mode result:
Arrived vehicles: 3540
Average waiting time: 332.508
Average travel time: 6.94124

Adaptive mode result:
Arrived vehicles: 3956
Average waiting time: 126.728
Average travel time: 6.78969

Adaptive improvement summary:
Throughput improvement: 11.75%
Waiting time reduction: 61.89%
Travel time reduction: 2.18%
```

---

## CSV Export

The `EXPORT` command writes simulation results to:

```txt
data/simulation_results.csv
```

The CSV file contains:

```txt
mode,steps,arrived_vehicles,average_waiting_time,average_travel_time,total_congestion_events
```

---

## Project Structure

```txt
src/cityflow/
├── main.cpp
├── Vehicle.hpp
├── Vehicle.cpp
├── Road.hpp
├── Road.cpp
├── TrafficLight.hpp
├── TrafficLight.cpp
├── TrafficController.hpp
├── TrafficController.cpp
├── Simulation.hpp
├── Simulation.cpp
├── CityGraph.hpp
└── CityGraph.cpp

data/
└── simulation_results.csv
```

---

## C++ Concepts Demonstrated

This project demonstrates:

- Object-oriented design
- Encapsulation with classes
- Graph modeling
- Shortest path calculation with Dijkstra
- State-based traffic light control
- Queue-based vehicle movement
- Simulation with discrete time steps
- Statistics calculation
- Benchmarking with `std::chrono`
- CSV file export

---

## Conclusion

CityFlow demonstrates how adaptive traffic light control can improve traffic flow compared to a fixed traffic light cycle.

The simulation results show that adaptive control can increase the number of arrived vehicles and reduce average waiting time.