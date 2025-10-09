#include <gtest/gtest.h>

#include "core/RunGraph.h"

/**
 * Test Suite: Graph Node
 * Testing individual node functionality
 */

TEST(GraphNodeTest, CanCreateNode) {
  auto room = std::make_unique<Room>("room_01", Room::Type::Combat);
  RunGraph::Node node(std::move(room));

  EXPECT_EQ(node.GetRoom()->GetId(), "room_01");
  EXPECT_EQ(node.GetDepth(), 0);
  EXPECT_TRUE(node.GetNextRooms().empty());
}

TEST(GraphNodeTest, CanConnectNodes) {
  auto room1 = std::make_unique<Room>("room_01", Room::Type::Combat);
  auto room2 = std::make_unique<Room>("room_02", Room::Type::Combat);

  RunGraph::Node node1(std::move(room1));
  RunGraph::Node node2(std::move(room2));

  node1.AddConnection(&node2);

  EXPECT_EQ(node1.GetNextRooms().size(), 1);
  EXPECT_EQ(node1.GetNextRooms()[0], &node2);
}

TEST(GraphNodeTest, CanSetDepth) {
  auto room = std::make_unique<Room>("room_01", Room::Type::Combat);
  RunGraph::Node node(std::move(room));

  node.SetDepth(5);
  EXPECT_EQ(node.GetDepth(), 5);
}

TEST(GraphNodeTest, CanMarkCriticalPath) {
  auto room = std::make_unique<Room>("room_01", Room::Type::Combat);
  RunGraph::Node node(std::move(room));

  EXPECT_FALSE(node.IsOnCriticalPath());

  node.SetOnCriticalPath(true);
  EXPECT_TRUE(node.IsOnCriticalPath());
}

/**
 * Test Suite: RunGraph
 * Testing graph construction
 */

TEST(RunGraphTest, StartsEmpty) {
  RunGraph graph;

  EXPECT_EQ(graph.GetNodeCount(), 0);
  EXPECT_EQ(graph.GetStartNode(), nullptr);
}

TEST(RunGraphTest, CanAddSingleRoom) {
  RunGraph graph;

  auto* node = graph.AddRoom("room_01", Room::Type::Combat);

  EXPECT_EQ(graph.GetNodeCount(), 1);
  EXPECT_NE(node, nullptr);
  EXPECT_EQ(node->GetRoom()->GetId(), "room_01");
}

TEST(RunGraphTest, CanCreateLinearPath) {
  RunGraph graph;

  auto* start = graph.AddRoom("start", Room::Type::Combat);
  auto* middle = graph.AddRoom("middle", Room::Type::Combat);
  auto* end = graph.AddRoom("end", Room::Type::Boss);

  graph.Connect(start, middle);
  graph.Connect(middle, end);

  EXPECT_EQ(graph.GetNodeCount(), 3);
  EXPECT_EQ(start->GetNextRooms().size(), 1);
  EXPECT_EQ(start->GetNextRooms()[0], middle);
  EXPECT_EQ(middle->GetNextRooms()[0], end);
}

TEST(RunGraphTest, CanSetStartNode) {
  RunGraph graph;

  auto* start = graph.AddRoom("start", Room::Type::Combat);
  graph.SetStartNode(start);

  EXPECT_EQ(graph.GetStartNode(), start);
}

TEST(RunGraphTest, CanCreateBranchingPath) {
  RunGraph graph;

  auto* start = graph.AddRoom("start", Room::Type::Combat);
  auto* branch1 = graph.AddRoom("branch1", Room::Type::Combat);
  auto* branch2 = graph.AddRoom("branch2", Room::Type::Treasure);
  auto* end = graph.AddRoom("end", Room::Type::Boss);

  graph.Connect(start, branch1);
  graph.Connect(start, branch2);
  graph.Connect(branch1, end);
  graph.Connect(branch2, end);

  EXPECT_EQ(start->GetNextRooms().size(), 2);
  EXPECT_EQ(branch1->GetNextRooms().size(), 1);
  EXPECT_EQ(branch2->GetNextRooms().size(), 1);
}

TEST(RunGraphTest, GetAllNodesReturnsAllNodes) {
  RunGraph graph;

  graph.AddRoom("room1", Room::Type::Combat);
  graph.AddRoom("room2", Room::Type::Elite);
  graph.AddRoom("room3", Room::Type::Boss);

  auto nodes = graph.GetAllNodes();
  EXPECT_EQ(nodes.size(), 3);
}