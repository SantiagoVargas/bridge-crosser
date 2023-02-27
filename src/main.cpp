#include "simulator.h"
#include "structs.h"
#include "yaml-parser.h"

#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    // TODO: Retrieve input filename from command line params
    // Extract bridge information from YAML file
    std::vector<Bridge> bridges = parseYaml("examples/input.yaml");

    // Simulate optimal crossings
    std::vector<double> crossingMinutes = simulateBridgeCrossings(bridges);

    // Reporting
    for (int i = 0; i < crossingMinutes.size(); i++)
    {
        std::cout << "Bridge " << i + 1 << " crossed in " << crossingMinutes[i] << " minutes.\n";
    }
    double totalTime = std::accumulate(crossingMinutes.begin(), crossingMinutes.end(), 0);
    std::cout << "Total Journey Time: " << totalTime << " minutes.\n";

    return 0;
}