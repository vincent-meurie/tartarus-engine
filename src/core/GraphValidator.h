#pragma once
#include <string>
#include <vector>

#include "core/RunGraph.h"

/**
 * Validates RunGraph structure for correctness
 *
 * Ensures:
 * - No cycles (DAG property)
 * - All nodes are reachable from start
 * - Boss room exists and is reachable
 * - No disconnecte components
 */
class GraphValidator {
 public:
  enum class ValidationError {
    NoStartNode,
    NoBossRoom,
    DisconnectedNode,
    CycleDetected,
    UnreachableBoss,
    MultipleStartNodes,
    DeadEnd  // Non-boss node with no exits
  };

  struct ValidationResult {
    bool isValid = true;
    std::vector<ValidationError> errors;
    std::vector<std::string> errorMessages;

    bool HasError(ValidationError error) const;
    void AddError(ValidationError error, const std::string& message);
  };

  ValidationResult Validate(const RunGraph& graph);

 private:
  bool HasCycles(const RunGraph& graph);
  bool AllNodesReachable(const RunGraph& graph);
  bool HasBossRoom(const RunGraph& graph);
  bool HasDeadEnds(const RunGraph& graph);

  bool HasCyclesHelper(const RunGraph::Node* node, std::vector<const RunGraph::Node*>& visited,
                       std::vector<const RunGraph::Node*>& recursionStack);
};