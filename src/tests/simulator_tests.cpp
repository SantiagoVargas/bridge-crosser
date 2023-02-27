#include "simulator.h"

#include <gtest/gtest.h>
#include <vector>

TEST(SimulatorTest, NoBridges)
{
  std::vector<Bridge> emptyInput;
  std::vector<double> result = simulateBridgeCrossings(emptyInput);

  EXPECT_EQ(result.size(), 0);
}

TEST(SimulatorTest, OneBridgeOneHiker)
{
  Hiker hiker1 = {
      .speedFtPerMin = 5};
  std::vector<Hiker> hikers;
  hikers.push_back(hiker1);
  Bridge bridge1 = {
      .lengthFt = 10,
      .newHikers = hikers};
  std::vector<Bridge> input;
  input.push_back(bridge1);

  std::vector<double> result = simulateBridgeCrossings(input);

  EXPECT_EQ(result.size(), 1); // Check that 1 bridge is crossed
  EXPECT_EQ(result[0], 2);     // Check it takes the hiker 2 minutes
}

TEST(SimulatorTest, MultipleBridgesNoHikers)
{
  Bridge bridge1 = {
      .lengthFt = 10};
  Bridge bridge2 = {
      .lengthFt = 20};
  Bridge bridge3 = {
      .lengthFt = 50};
  std::vector<Bridge> input;
  input.push_back(bridge1);
  input.push_back(bridge2);
  input.push_back(bridge3);

  std::vector<double> result = simulateBridgeCrossings(input);

  EXPECT_EQ(result.size(), 3); // Check that 3 bridges are crossed
  // Check that no time is taken to cross the bridges
  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 0);
  EXPECT_EQ(result[2], 0); 
}

TEST(SimulatorTest, MultipleBridgesOneHiker)
{
  Hiker hiker1 = {
      .speedFtPerMin = 5};
  std::vector<Hiker> hikers;
  hikers.push_back(hiker1);
  Bridge bridge1 = {
      .lengthFt = 10,
      .newHikers = hikers};
  Bridge bridge2 = {
      .lengthFt = 20};
  Bridge bridge3 = {
      .lengthFt = 50};
  std::vector<Bridge> input;
  input.push_back(bridge1);
  input.push_back(bridge2);
  input.push_back(bridge3);

  std::vector<double> result = simulateBridgeCrossings(input);

  EXPECT_EQ(result.size(), 3); // Check that 3 bridges are crossed
  EXPECT_EQ(result[0], 2);     // Check it takes the hiker 2 minutes for bridge 1
  EXPECT_EQ(result[1], 4);     // Check it takes the hiker 4 minutes for bridge 2
  EXPECT_EQ(result[2], 10);    // Check it takes the hiker 10 minutes for bridge 3
}

TEST(SimulatorTest, MultipleBridgesTwoHikers)
{
  Hiker hiker1 = {
      .speedFtPerMin = 5};
  Hiker hiker2 = {
      .speedFtPerMin = 10};
  std::vector<Hiker> hikers;
  hikers.push_back(hiker1);
  hikers.push_back(hiker2);
  Bridge bridge1 = {
      .lengthFt = 10,
      .newHikers = hikers};
  Bridge bridge2 = {
      .lengthFt = 20};
  Bridge bridge3 = {
      .lengthFt = 50};
  std::vector<Bridge> input;
  input.push_back(bridge1);
  input.push_back(bridge2);
  input.push_back(bridge3);

  std::vector<double> result = simulateBridgeCrossings(input);

  EXPECT_EQ(result.size(), 3); // Check that 3 bridges are crossed
  EXPECT_EQ(result[0], 2);     // Check it takes the hikers 2 minutes for bridge 1
  EXPECT_EQ(result[1], 4);     // Check it takes the hikers 4 minutes for bridge 2
  EXPECT_EQ(result[2], 10);    // Check it takes the hikers 10 minutes for bridge 3
}

TEST(SimulatorTest, MultipleBridgesThreeHikers)  // Tests backtracking
{
  Hiker hiker1 = {
      .speedFtPerMin = 5};
  Hiker hiker2 = {
      .speedFtPerMin = 10};
  Hiker hiker3 = {
      .speedFtPerMin = 20};
  std::vector<Hiker> hikers;
  hikers.push_back(hiker1);
  hikers.push_back(hiker2);
  hikers.push_back(hiker3);
  Bridge bridge1 = {
      .lengthFt = 10,
      .newHikers = hikers};
  Bridge bridge2 = {
      .lengthFt = 20};
  Bridge bridge3 = {
      .lengthFt = 50};
  std::vector<Bridge> input;
  input.push_back(bridge1);
  input.push_back(bridge2);
  input.push_back(bridge3);

  std::vector<double> result = simulateBridgeCrossings(input);

  EXPECT_EQ(result.size(), 3); // Check that 3 bridges are crossed
  EXPECT_EQ(result[0], 3.5);
  EXPECT_EQ(result[1], 7);
  EXPECT_EQ(result[2], 17.5);
}

TEST(SimulatorTest, MultipleBridgesStaggeredHikers)
{
  Hiker hiker1 = {
      .speedFtPerMin = 5};
  Hiker hiker2 = {
      .speedFtPerMin = 10};
  Hiker hiker3 = {
      .speedFtPerMin = 20};
  std::vector<Hiker> hikerGroup1;
  std::vector<Hiker> hikerGroup2;
  // Hikers added in reverse speed
  hikerGroup1.push_back(hiker1);
  hikerGroup1.push_back(hiker2);
  hikerGroup2.push_back(hiker3);
  Bridge bridge1 = {
      .lengthFt = 10,
      .newHikers = hikerGroup1};
  Bridge bridge2 = {
      .lengthFt = 20,
      .newHikers = hikerGroup2};
  Bridge bridge3 = {
      .lengthFt = 50};
  std::vector<Bridge> input;
  input.push_back(bridge1);
  input.push_back(bridge2);
  input.push_back(bridge3);

  std::vector<double> result = simulateBridgeCrossings(input);

  EXPECT_EQ(result.size(), 3); // Check that 3 bridges are crossed
  EXPECT_EQ(result[0], 2);
  EXPECT_EQ(result[1], 7);
  EXPECT_EQ(result[2], 17.5);
}
