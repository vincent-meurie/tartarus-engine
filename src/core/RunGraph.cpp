#include "RunGraph.h"

// Node implementation
RunGraph::Node::Node(std::unique_ptr<Room> room) : room_(std::move(room)) {}

void RunGraph::Node::AddConnection(Node* next) {
  if (next) {
    next_.push_back(next);
  }
}

// RunGraph implementation
RunGraph::Node* RunGraph::AddRoom(std::string id, Room::Type type) {
  auto room = std::make_unique<Room>(std::move(id), type);
  return AddRoom(std::move(room));
}

RunGraph::Node* RunGraph::AddRoom(std::unique_ptr<Room> room) {
  auto node = std::make_unique<Node>(std::move(room));
  Node* nodePtr = node.get();
  nodes_.push_back(std::move(node));
  return nodePtr;
}

void RunGraph::Connect(Node* from, Node* to) {
  if (from && to) {
    from->AddConnection(to);
  }
}

std::vector<RunGraph::Node*> RunGraph::GetAllNodes() {
  std::vector<Node*> result;
  result.reserve(nodes_.size());
  for (auto& node : nodes_) {
    result.push_back(node.get());
  }
  return result;
}

std::vector<const RunGraph::Node*> RunGraph::GetAllNodes() const {
  std::vector<const Node*> result;
  result.reserve(nodes_.size());
  for (const auto& node : nodes_) {
    result.push_back(node.get());
  }
  return result;
}