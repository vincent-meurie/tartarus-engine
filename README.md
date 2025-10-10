# Tartarus Engine

A Hades-inspired procedural level generatir built in C++ using Test-Driven Development.

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![Tests](https://img.shields.io/badge/tests-43%20passing-brightgreen)
![Coverage](https://img.shields.io/badge/coverage-~85%25-green)
![C++](https://img.shields.io/badge/C%2B%2B-20-blue)
![CMake](https://img.shields.io/badge/CMake-3.15%2B-blue)

## 🎯 Project Goals

This project demonstrates:
- Modern C++ (C++20) best practices
- Test-Driven Development methodology
- Procedural generation algorithms
- Graph-based level design
- Professional software engineering workflow

## 🏗️ Architecture

The engine generates roguelike runs with:
- Graph-based room connections
- Biome-specific content (Tartarus, Asphodel, Elysium, Styx)
- Intelligent reward distribution
- Guaranteed critical paths with optional branches
- Data-driven room templates

## 🔧 Tech Stack

- **Language:** C++20
- **Build System:** CMake 3.15+
- **Testing:** Google Test
- **Dependencies:** GLM (mathematics), nlohmann/json (data)

### ✅ Completed Features (Week 1-2)

#### Core Systems
- **Room System** - Rooms with types, exits, metadata, and rewards
  - 8 room types (Combat, Elite, MiniBoss, Boss, Treasure, Shop, Fountain, Story)
  - Directional exits with position data
  - Biome assignment (Tartarus, Asphodel, Elysium, Styx)
  - Difficulty ratings
  - Multiple reward types (Boons, Poms, Gold, Hammers, etc.)

- **Graph Structure** - Directed Acyclic Graph for run representation
  - Node system wrapping rooms
  - Connection management
  - Depth tracking
  - Critical path marking
  - Move semantics for efficient ownership transfer

- **Graph Validation** - Ensures structural correctness
  - Cycle detection
  - Reachability analysis
  - Dead-end detection
  - Boss room verification
  - Detailed error reporting

- **Path Generation** - Procedural run creation
  - Configurable run length (40-50 rooms typical)
  - Linear path generation
  - Room type variety with weighted distribution
  - Mini-boss placement at intervals
  - Deterministic generation with seeded RNG

#### Reward System
- 12 reward types matching Hades gameplay
- Reward metadata (god names, quantities)
- Per-room reward management

### 🚧 In Progress (Week 2)

- [ ] Branching path generation
- [ ] Special room placement rules (shops, fountains)
- [ ] Biome-specific room templates
- [ ] Reward distribution algorithms
- [ ] Run statistics and metrics

### 📋 Planned Features

- [ ] Complete run generator (4 biomes, 45 rooms)
- [ ] Constraint satisfaction for room placement
- [ ] Data-driven room template loading (JSON)
- [ ] Serialization/deserialization
- [ ] Visualization system (ImGui-based)
- [ ] Advanced metrics and analytics

## 📊 Development Progress

**Current Status:** Week 2, Day 1 - Path Generation Foundation

| Component | Status | Tests |
|-----------|--------|-------|
| Room System | ✅ Complete | 16 |
| Graph Structure | ✅ Complete | 11 |
| Graph Validation | ✅ Complete | 7 |
| Path Generator | 🚧 In Progress | 9 |
| **Total** | **40 tests** | **43/43 passing** |

### Commit History Highlights
- 20 commits with clear TDD progression
- Each commit shows RED → GREEN → REFACTOR cycle
- Incremental feature development
- Professional commit messages

## 🚀 Building
```bash
# Configure
cmake -B build

# Build
cmake --build build

# Run tests
cd build
ctest --output-on-failure