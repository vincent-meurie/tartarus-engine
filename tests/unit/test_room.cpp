#include <gtest/gtest.h>

#include "core/Biome.h"
#include "core/Room.h"

/**
 * Test Suite: Room
 * Testing the basic Room class functionality
 */

TEST(RoomTest, CanCreateBasicRoom) {
  Room room("room_01", Room::Type::Combat);

  EXPECT_EQ(room.GetId(), "room_01");
  EXPECT_EQ(room.GetType(), Room::Type::Combat);
}

TEST(RoomTest, ThrowsOnEmptyId) {
  EXPECT_THROW(Room("", Room::Type::Combat), std::invalid_argument);
}

TEST(RoomTest, TypeToStringWorks) {
  EXPECT_STREQ(Room::TypeToString(Room::Type::Combat), "Combat");
  EXPECT_STREQ(Room::TypeToString(Room::Type::Boss), "Boss");
  EXPECT_STREQ(Room::TypeToString(Room::Type::Shop), "Shop");
}

TEST(RoomExitTest, CanAddSingleExit) {
  Room room("room_01", Room::Type::Combat);
  room.AddExit({10.0f, 0.0f}, Room::Direction::North);

  EXPECT_EQ(room.GetExitCount(), 1);
  EXPECT_TRUE(room.HasExit(Room::Direction::North));
}

TEST(RoomExitTest, CanAddMultipleExits) {
  Room room("room_01", Room::Type::Combat);
  room.AddExit({10.0f, 0.0f}, Room::Direction::North);
  room.AddExit({20.0f, 0.0f}, Room::Direction::North);

  EXPECT_EQ(room.GetExitCount(), 2);
}

TEST(RoomExitTest, ExitPositionsAreStored) {
  Room room("room_01", Room::Type::Combat);
  room.AddExit({10.0f, 5.0f}, Room::Direction::North);

  auto exits = room.GetExits();
  ASSERT_EQ(exits.size(), 1);
  EXPECT_FLOAT_EQ(exits[0].position.x, 10.0f);
  EXPECT_FLOAT_EQ(exits[0].position.y, 5.0f);
  EXPECT_EQ(exits[0].direction, Room::Direction::North);
}

TEST(RoomExitTest, CannotExceedMaxExits) {
  Room room("room_01", Room::Type::Combat);

  // Add maximum allowed exits (4)
  room.AddExit({10.0f, 0.0f}, Room::Direction::North);
  room.AddExit({15.0f, 0.0f}, Room::Direction::North);
  room.AddExit({20.0f, 0.0f}, Room::Direction::East);
  room.AddExit({25.0f, 0.0f}, Room::Direction::West);

  // Fifth exit should throw
  EXPECT_THROW(room.AddExit({30.0f, 0.0f}, Room::Direction::South), std::runtime_error);
}

/**
 * Test Suite: Room Metadata
 * Testing biome, difficultym and other room properties
 */

TEST(RoomMetadataTest, CanAssignBiome) {
  Room room("room_01", Room::Type::Combat);
  room.SetBiome(Biome::Type::Tartarus);

  EXPECT_EQ(room.GetBiome(), Biome::Type::Tartarus);
}

TEST(RoomMetadataTest, DefaultBiomeIsTartarus) {
  Room room("room_01", Room::Type::Combat);

  EXPECT_EQ(room.GetBiome(), Biome::Type::Tartarus);
}

TEST(RoomMetadataTest, HasDifficultyRating) {
  Room room("room_01", Room::Type::Combat);
  room.SetDifficulty(1.5f);

  EXPECT_FLOAT_EQ(room.GetDifficulty(), 1.5f);
}

TEST(RoomMetadataTest, DefaultDifficultyIsOne) {
  Room room("room_01", Room::Type::Combat);

  EXPECT_FLOAT_EQ(room.GetDifficulty(), 1.0f);
}