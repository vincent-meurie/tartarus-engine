#pragma once
#include <random>

#include "core/RunGraph.h"

/**
 * Generates critical paths and branhing structures for dungeon runs
 */

class PathGenerator {
 public:
  /**
   * Configuration for path generation
   */
  struct Config {
    int minRooms = 40;
    int maxRooms = 50;
    float branchProbability = 0.3f;
    int miniBossInterval = 10;
    int guaranteedShops = 2;
    int guaranteedFountains = 3;
  };

  explicit PathGenerator(std::mt19937& rng);

  // Config
  void SetConfig(const Config& config) { config_ = config; }
  const Config& GetConfig() const { return config_; }
  RunGraph GeneratePath();

 private:
  std::mt19937& rng_;
  Config config_;
  Room::Type SelectRoomType(int depth, int totalRooms);
  std::string GenerateRoomId(int index);
};