#pragma once
#include <stdexcept>
#include <string>

/**
 * Represents a single room in the dungeon run
 *
 * Each room has:
 * - Unique identifier
 * - Type (Combat, Elite, Boss, etc.)
 * - Connections to other rooms (exits)
 * - Metadata (biome, difficulty, rewards)
 */
class Room {
 public:
  enum class Type {
    Combat,    // Standard enemy encounter
    Elite,     // Tougher enemies, better rewards
    MiniBoss,  // Mid-level boss fight
    Treasure,  // Guaranteed reward room
    Shop,      // Charon's shop
    Fountain,  // Health restoration
    Story,     // Narrative/character moment
    Boss       // Biome boss (Meg, Hydra, etc.)
  };

  /**
   * Constructor
   * @param id Unique room identifier
   * @param type Room type
   * @throws std::invalid_argument if id is empty
   */
  Room(std::string id, Type type);

  // Getters
  const std::string& GetId() const { return id_; }
  Type GetType() const { return type_; }

 private:
  std::string id_;
  Type type_;
};