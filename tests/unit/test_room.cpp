#include <gtest/gtest.h>

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