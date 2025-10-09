#include "Reward.h"

const char* Reward::ToString(Reward::Type type) {
  switch (type) {
    case Type::Boon:
      return "Boon";
    case Type::Pom:
      return "Pom";
    case Type::Gold:
      return "Gold";
    case Type::CentaurHeart:
      return "Centaur Heart";
    case Type::Hammer:
      return "Hammer";
    case Type::Hermes:
      return "Hermes";
    case Type::Darkness:
      return "Darkness";
    case Type::Gemstone:
      return "Gemstone";
    case Type::Nectar:
      return "Nectar";
    case Type::Key:
      return "Key";
    case Type::ErebusGate:
      return "Erebus Gate";
    case Type::ChaosGate:
      return "Chaos Gate";
    default:
      return "Unknown";
  }
}