#include "yaml-parser.h"
#include "structs.h"

#include "yaml-cpp/yaml.h"

void operator>>(const YAML::Node &node, Bridge &bridge)
{
    bridge.lengthFt = node["bridgeLengthFt"].as<double>();
    const YAML::Node &hikers = node["newHikers"];
    for (int i = 0; i < hikers.size(); i++)
    {
        Hiker hiker;
        hiker.speedFtPerMin = hikers[i]["speedFtPerMinute"].as<double>();
        bridge.newHikers.push_back(hiker);
    }
}

std::vector<Bridge> parseYaml(std::string filename)
{
    // Parse input file using yaml-cpp
    YAML::Node doc = YAML::LoadFile(filename);

    // Create vector of bridges (ordered based on YAML file)
    std::vector<Bridge> bridges;
    for (int i = 0; i < doc.size(); i++)
    {
        Bridge bridge;
        doc[i] >> bridge;
        // std::cout << "Bridge " << i + 1 << ": " << bridge.lengthFt
        //   << "ft with " << bridge.newHikers.size() << " new hiker(s) \n";
        bridges.push_back(bridge);
    }

    return bridges;
}
