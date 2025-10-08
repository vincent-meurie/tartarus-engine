#pragma once

/**
 * Biomes in Hades, each with distinct visual style and enemy types
 */
namespace Biome {
enum class Type {
  Tartarus,  // First biome (green/red, basic enemies)
  Asphodel,  // Second biome (lava/fire, ranged enemies)
  Elysium,   // Third biome (gold/white, elite enemies)
  Styx       // Final biome (green poison, stealth sections)
};

const char* ToString(Type type);
}  // namespace Biome