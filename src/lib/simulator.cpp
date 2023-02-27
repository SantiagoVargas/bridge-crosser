#include "simulator.h"
#include "structs.h"

#include <queue>
#include <vector>

// Returns a vector of minutes taken to cross each Bridge
std::vector<double> simulateBridgeCrossings(std::vector<Bridge> bridges)
{
    // Approach Iterate bridges in order and maintain:
    // 1. Max priority queue of hikers ordered by speed
    // - PQueue allows fast insert of new hikers to sorted list
    // - PQueue allows iterating sorted hikers to calculate time taken when crossing bridges
    // 2. Running count of time taken to cross current bridge

    std::vector<double> crossingTimes;

    std::priority_queue<double, std::vector<double>> sortedHikers;
    double totalTime = 0;

    for (int i = 0; i < bridges.size(); i++)
    {
        auto currentBridge = bridges[i];
        // For each new hiker, add the hiker speed to list of hikers
        for (Hiker h : currentBridge.newHikers)
        {
            sortedHikers.push(h.speedFtPerMin);
        }

        // Copy Pqueue of hikers in order to iterate for current bridge calculations
        auto hikersCopy = sortedHikers;
        // Now that all hikers are added, simulate the optimal crossing
        double bridgeTimeTaken = 0;
        // Optimal Crossing Strategy: Since backtracking may be needed because of one torch,
        // the optimatl strategy is fastest hiker carrying the torch and bringing other hikers
        // across the bridges in order to minimize backtracking time
        if (hikersCopy.size())
        {
            double fastestHikerSpeed = hikersCopy.top();
            double fastestHikerTimeTaken = currentBridge.lengthFt / fastestHikerSpeed;
            hikersCopy.pop();

            // If the size > 1, then need to backtrack
            while (hikersCopy.size() > 1)
            {
                auto currentHikerSpeed = hikersCopy.top();
                hikersCopy.pop();

                // Add slower hiker time
                bridgeTimeTaken += currentBridge.lengthFt / currentHikerSpeed;
                // Add backtrack time
                bridgeTimeTaken += fastestHikerTimeTaken;
            }

            // Check if one slow hiker still left
            if (hikersCopy.size())
            {
                auto currentHikerSpeed = hikersCopy.top();
                hikersCopy.pop();
                // Add slower hiker time with no need to backtrack
                bridgeTimeTaken += currentBridge.lengthFt / currentHikerSpeed;
            }
            else if (!bridgeTimeTaken)
            { // If only fast hiker, include his time
                bridgeTimeTaken += fastestHikerTimeTaken;
            }
        }

        crossingTimes.push_back(bridgeTimeTaken);
    }

    return crossingTimes;
}