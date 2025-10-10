#include <gtest/gtest.h>

#include "../test_utils.h"
#include "core/GraphValidator.h"
#include "generation/PathGenerator.h"

/**
 * Test Suite: PathGenerator Creation
 * Testing basic path generator setup and configuration
 */

TEST(PathGeneratorTest, CanCreateGenerator) {
  TestUtils::SeededRandom rng(42);
  PathGenerator generator(rng.GetEngine());

  // Just verify it constructs without errors
  SUCCEED();
}

TEST(PathGeneratorTest, HasDefaultConfiguration) {
  TestUtils::SeededRandom rng(42);
  PathGenerator generator(rng.GetEngine());

  auto config = generator.GetConfig();

  // Hades has roughly 40-50 rooms per run
  EXPECT_GE(config.minRooms, 30);
  EXPECT_LE(config.maxRooms, 60);
  EXPECT_GT(config.branchProbability, 0.0f);
  EXPECT_LT(config.branchProbability, 1.0f);
}

TEST(PathGeneratorTest, CanSetCustomConfiguration) {
  TestUtils::SeededRandom rng(42);
  PathGenerator generator(rng.GetEngine());

  PathGenerator::Config customConfig;
  customConfig.minRooms = 10;
  customConfig.maxRooms = 15;
  customConfig.branchProbability = 0.5f;

  generator.SetConfig(customConfig);

  auto retrievedConfig = generator.GetConfig();
  EXPECT_EQ(retrievedConfig.minRooms, 10);
  EXPECT_EQ(retrievedConfig.maxRooms, 15);
  EXPECT_FLOAT_EQ(retrievedConfig.branchProbability, 0.5f);
}

/**
 * Test Suite: Linear Path Generation
 * Testing simple straight-line path generation
 */

TEST(PathGeneratorTest, GeneratesLinearPath) {
  TestUtils::SeededRandom rng(42);
  PathGenerator generator(rng.GetEngine());

  PathGenerator::Config config;
  config.minRooms = 10;
  config.maxRooms = 10;
  config.branchProbability = 0.0f;

  generator.SetConfig(config);

  auto graph = generator.GeneratePath();

  EXPECT_EQ(graph.GetNodeCount(), 10);
  EXPECT_NE(graph.GetStartNode(), nullptr);
}

TEST(PathGeneratorTest, LinearPathEndsWithBoss) {
  TestUtils::SeededRandom rng(42);
  PathGenerator generator(rng.GetEngine());

  PathGenerator::Config config;
  config.minRooms = 5;
  config.maxRooms = 5;
  config.branchProbability = 0.0f;

  generator.SetConfig(config);

  auto graph = generator.GeneratePath();

  // Find the last node (should be boss)
  auto nodes = graph.GetAllNodes();
  bool foundBoss = false;
  for (const auto* node : nodes) {
    if (node->GetRoom()->GetType() == Room::Type::Boss) {
      foundBoss = true;
      // Boss should have no exits
      EXPECT_EQ(node->GetNextRooms().size(), 0);
    }
  }

  EXPECT_TRUE(foundBoss) << "Path must end with a boss";
}

TEST(PathGeneratorTest, LinearPathIsConnected) {
  TestUtils::SeededRandom rng(42);
  PathGenerator generator(rng.GetEngine());

  PathGenerator::Config config;
  config.minRooms = 8;
  config.maxRooms = 8;
  config.branchProbability = 0.0f;

  generator.SetConfig(config);

  auto graph = generator.GeneratePath();

  // Validate graph is well-formed
  GraphValidator validator;
  auto result = validator.Validate(graph);

  EXPECT_TRUE(result.isValid) << "Generated path must be valid";
}

TEST(PathGeneratorTest, PathDepthsAreCorrect) {
  TestUtils::SeededRandom rng(42);
  PathGenerator generator(rng.GetEngine());

  PathGenerator::Config config;
  config.minRooms = 5;
  config.maxRooms = 5;
  config.branchProbability = 0.0f;

  generator.SetConfig(config);

  auto graph = generator.GeneratePath();

  // Start node should be depth 0
  EXPECT_EQ(graph.GetStartNode()->GetDepth(), 0);

  // Walk the path and verify depth increase
  auto* current = graph.GetStartNode();
  int expectedDepth = 0;

  while (!current->GetNextRooms().empty()) {
    EXPECT_EQ(current->GetDepth(), expectedDepth);
    current = current->GetNExtRooms()[0];
    expectedDepth++;
  }
}