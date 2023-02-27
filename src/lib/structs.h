#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>

struct Hiker
{
    float speedFtPerMin; // Hiker speed in feet/minute
};

struct Bridge
{
    float lengthFt; // Bridge length in feet
    std::vector<Hiker> newHikers;
};

#endif