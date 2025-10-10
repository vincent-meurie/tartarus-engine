#pragma once

#include <memory>
#include <vector>

#include "Room.h"

/**
 * Directed Acyclic Graph (DAG) representing a dungeon run
 *
 * Structure:
 * - Nodes contain rooms
 * - Edges represent possible paths
 * - One start node, one or more end nodes (boss)
 * - No cycles (can't go backwards)
 */
class RunGraph {
 public:
  /**
   * Node in the graph, wrapping a Room
   */
  class Node {
   public:
    explicit Node(std::unique_ptr<Room> room);

    // Connections
    void AddConnection(Node* next);
    const std::vector<Node*>& GetNextRooms() const { return next_; }

    // Metadata
    void SetDepth(int depth) { depth_ = depth; }
    int GetDepth() const { return depth_; }

    void SetOnCriticalPath(bool onPath) { onCriticalPath_ = onPath; }
    bool IsOnCriticalPath() const { return onCriticalPath_; }

    // Room access
    const Room* GetRoom() const { return room_.get(); }
    Room* GetRoom() { return room_.get(); }

   private:
    std::unique_ptr<Room> room_;
    std::vector<Node*> next_;
    int depth_ = 0;
    bool onCriticalPath_ = false;
  };

  RunGraph() = default;
  ~RunGraph() = default;

  RunGraph(const RunGraph&) = delete;
  RunGraph& operator=(const RunGraph&) = delete;

  // Default move operations ( will move unique ptrs correctly )
  RunGraph(RunGraph&&) noexcept = default;
  RunGraph& operator=(const RunGraph&&) = delete;

  // Graph construction
  Node* AddRoom(std::string id, Room::Type type);
  Node* AddRoom(std::unique_ptr<Room> room);
  void Connect(Node* from, Node* to);

  // Graph properties
  size_t GetNodeCount() const { return nodes_.size(); }
  Node* GetStartNode() const { return startNode_; }
  void SetStartNode(Node* node) { startNode_ = node; }

  // Graph traversal
  std::vector<Node*> GetAllNodes();
  std::vector<const Node*> GetAllNodes() const;

 private:
  std::vector<std::unique_ptr<Node>> nodes_;
  Node* startNode_ = nullptr;
};