#pragma once
#include <glm/glm.hpp>
#include <stdexcept>
#include <string>
#include <vector>

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
   * Exit direction (Which wall the exit is on)
   */

  enum class Direction { North, South, East, West };

  /**
   * Represents an exit point in the room
   */
  struct Exit {
    glm::vec2 position;   // Position in room coordinates
    Direction direction;  // Which wall/direction
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
  static const char* TypeToString(Type type);

  // Exit management
  void AddExit(glm::vec2 position, Direction direction);
  size_t GetExitCount() const { return exits_.size(); }
  bool HasExit(Direction direction) const;
  const std::vector<Exit>& GetExits() const { return exits_; }

  // Maximum exits per room (based on 4 cardinal directions)
  static constexpr size_t MAX_EXITS = 4;

 private:
  std::string id_;
  Type type_;
  std::vector<Exit> exits_;
};