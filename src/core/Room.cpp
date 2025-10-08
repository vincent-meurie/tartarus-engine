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