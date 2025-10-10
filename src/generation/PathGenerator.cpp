#include "generation/PathGenerator.h"

#include <sstream>

PathGenerator::PathGenerator(std::mt19937& rng) : rng_(rng) {}

RunGraph PathGenerator::GeneratePath() {
  RunGraph graph;

  // Determine path length
  std::uniform_int_distribution<int> lengthDist(config_.minRooms, config_.maxRooms);
  int totalRooms = lengthDist(rng_);

  RunGraph::Node* previousNode = nullptr;

  for (int i = 0; i < totalRooms; ++i) {
    // Select room type
    Room::Type roomType = SelectRoomType(i, totalRooms);

    // Create room
    auto* node = graph.AddRoom(GenerateRoomId(i), roomType);
    node->SetDepth(i);

    // Set start node
    if (i == 0) {
      graph.SetStartNode(node);
    }

    // Connect to previous node
    if (previousNode) {
      graph.Connect(previousNode, node);
    }

    previousNode = node;
  }

  return graph;
}

Room::Type PathGenerator::SelectRoomType(int depth, int totalRooms) {
  // Last room is always boss
  if (depth == totalRooms - 1) {
    return Room::Type::Boss;
  }

  // First room is always combat
  if (depth == 0) {
    return Room::Type::Combat;
  }

  // Place mini-boss at intervals
  if (config_.miniBossInterval > 0 && depth > 0 && depth % config_.miniBossInterval == 0) {
    return Room::Type::MiniBoss;
  }

  // Weighted random selection for variety
  std::uniform_int_distribution<int> typeDist(0, 100);
  int roll = typeDist(rng_);

  if (roll < 60) {
    return Room::Type::Combat;  // 60% combat
  } else if (roll < 75) {
    return Room::Type::Elite;  // 15% elite
  } else if (roll < 85) {
    return Room::Type::Treasure;  // 10% treasure
  } else if (roll < 92) {
    return Room::Type::Shop;  // 7% shop
  } else {
    return Room::Type::Fountain;  // 8 % fountain
  }
}

std::string PathGenerator::GenerateRoomId(int index) {
  std::ostringstream oss;
  oss << "room_" << (index + 1);
  return oss.str();
}