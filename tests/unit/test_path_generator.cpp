#include <gtest/gtest.h>

#include "../test_utils.h"
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