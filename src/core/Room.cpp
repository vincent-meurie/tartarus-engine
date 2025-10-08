#include "Room.h"

Room::Room(std::string id, Type type) : id_(std::move(id)), type_(type) {
  if (id_.empty()) {
    throw std::invalid_argument("Room ID cannot be empty");
  }
}

const char* Room::TypeToString(Type type) {
  switch (type) {
    case Type::Combat:
      return "Combat";
    case Type::Elite:
      return "Elite";
    case Type::MiniBoss:
      return "MiniBoss";
    case Type::Treasure:
      return "Treasure";
    case Type::Shop:
      return "Shop";
    case Type::Fountain:
      return "Fountain";
    case Type::Story:
      return "Story";
    case Type::Boss:
      return "Boss";
    default:
      return "Unknown";
  }
}

void Room::AddExit(glm::vec2 position, Direction direction) {
  if (exits_.size() >= MAX_EXITS) {
    throw std::runtime_error("Cannot exceed maximum exit count of " + std::to_string(MAX_EXITS));
  }
  exits_.push_back({position, direction});
}

bool Room::HasExit(Direction direction) const {
  for (const auto& exit : exits_) {
    if (exit.direction == direction) {
      return true;
    }
  }
  return false;
}