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

  /**
   * Everything is combat for now
   * variety will be added later
   */
  return Room::Type::Combat;
}

std::string PathGenerator::GenerateRoomId(int index) {
  std::ostringstream oss;
  oss << "room_" << (index + 1);
  return oss.str();
}