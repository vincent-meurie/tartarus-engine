#include "core/GraphValidator.h"

#include <algorithm>
#include <unordered_set>

bool GraphValidator::ValidationResult::HasError(ValidationError error) const {
  return std::find(errors.begin(), errors.end(), error) != errors.end();
}

void GraphValidator::ValidationResult::AddError(ValidationError error, const std::string& message) {
  errors.push_back(error);
  errorMessages.push_back(message);
  isValid = false;
}

GraphValidator::ValidationResult GraphValidator::Validate(const RunGraph& graph) {
  ValidationResult result;

  // Check for start node
  if (graph.GetStartNode() == nullptr) {
    result.AddError(ValidationError::NoStartNode, "Graph has no start node");
    return result;  // Can't continue without start node
  }

  // Check for boss room
  if (!HasBossRoom(graph)) {
    result.AddError(ValidationError::NoBossRoom, "Graph has no boss room");
  }

  // Check for cycles
  if (HasCycles(graph)) {
    result.AddError(ValidationError::CycleDetected, "Graph contains cycles");
  }

  // Check all nodes are reachable
  if (!AllNodesReachable(graph)) {
    result.AddError(ValidationError::DisconnectedNode,
                    "Some nodes are not reachable from the start");
  }

  // Check for dead ends (non-boss rooms with no exits)
  if (HasDeadEnds(graph)) {
    result.AddError(ValidationError::DeadEnd, "Found dead-end rooms (non-boss with no exits)");
  }

  return result;
}

bool GraphValidator::HasBossRoom(const RunGraph& graph) {
  for (const auto* node : graph.GetAllNodes()) {
    if (node->GetRoom()->GetType() == Room::Type::Boss) {
      return true;
    }
  }
  return false;
}

bool GraphValidator::HasCycles(const RunGraph& graph) {
  std::vector<const RunGraph::Node*> visited;
  std::vector<const RunGraph::Node*> recursionStack;

  return HasCyclesHelper(graph.GetStartNode(), visited, recursionStack);
}

bool GraphValidator::HasCyclesHelper(const RunGraph::Node* node,
                                     std::vector<const RunGraph::Node*>& visited,
                                     std::vector<const RunGraph::Node*>& recursionStack) {
  if (!node) return false;

  // If in recustion stack, we found a cycle
  if (std::find(recursionStack.begin(), recursionStack.end(), node) != recursionStack.end()) {
    return true;
  }

  // If already fully explored, no cycles here
  if (std::find(visited.begin(), visited.end(), node) != visited.end()) {
    return false;
  }

  // Mark as being explored
  recursionStack.push_back(node);

  // Check all children
  for (const auto* next : node->GetNextRooms()) {
    if (HasCyclesHelper(next, visited, recursionStack)) {
      return true;
    }
  }

  // Done exploring this node
  recursionStack.erase(std::remove(recursionStack.begin(), recursionStack.end(), node),
                       recursionStack.end());
  visited.push_back(node);

  return false;
}

bool GraphValidator::AllNodesReachable(const RunGraph& graph) {
  if (graph.GetNodeCount() == 0) return true;
  if (!graph.GetStartNode()) return false;

  std::unordered_set<const RunGraph::Node*> reachable;
  std::vector<const RunGraph::Node*> toVisit;

  toVisit.push_back(graph.GetStartNode());

  while (!toVisit.empty()) {
    const auto* current = toVisit.back();
    toVisit.pop_back();

    if (reachable.count(current)) continue;
    reachable.insert(current);

    for (const auto* next : current->GetNextRooms()) {
      if (!reachable.count(next)) {
        toVisit.push_back(next);
      }
    }
  }

  return reachable.size() == graph.GetNodeCount();
}

bool GraphValidator::HasDeadEnds(const RunGraph& graph) {
  for (const auto* node : graph.GetAllNodes()) {
    // Boss rooms are allowed to have no exits
    if (node->GetRoom()->GetType() == Room::Type::Boss) {
      continue;
    }

    // Non-boss rooms must have at least one exit
    if (node->GetNextRooms().empty()) {
      return true;
    }
  }
  return false;
}