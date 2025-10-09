#pragma once
#include <string>

/**
 * Reward types available in Hades
 * These appear after clearing a riim
 */

namespace Reward {
enum class Type {
  Boon,          // God blessing (Zeus, Athena, etc.)
  Pom,           // Pomegranate - upgrade existing boon
  Gold,          // Obols (currency)
  CentaurHeart,  // Max health increase
  Hammer,        // Daedalus Hammer - weapon upgrade
  Hermes,        // Hermes boon (always good)
  Darkness,      // Mirror of Night currency
  Gemstone,      // House contractor currency
  Nectar,        // Gift for characters
  Key,           // Chtonic Key for weapons
  ErebusGate,    // Challenge gate (not reard, but a choice)
  ChaosGate      // Chaos boon opportunity
};

/**
 * Reward data with type and optional metadata
 */
struct Data {
  Type type;
  std::string godName;  // For boons (eg Zeus, Athena)
  int quantity = 1;     // For stackable rewards (gold, gems)

  Data(Type t) : type(t) {}
  Data(Type t, std::string god) : type(t), godName(std::move(god)) {}
  Data(Type t, int qty) : type(t), quantity(qty) {}
};

const char* ToString(Type type);
}  // namespace Reward