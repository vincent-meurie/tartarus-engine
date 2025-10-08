#include "Biome.h"

const char* Biome::ToString(Biome::Type type) {
  switch (type) {
    case Type::Tartarus:
      return "Tartarus";
    case Type::Asphodel:
      return "Asphodel";
    case Type::Elysium:
      return "Elysium";
    case Type::Styx:
      return "Styx";
    default:
      return "Unknown";
  }
}