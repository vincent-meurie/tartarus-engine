# Tartarus Engine

A Hades-inspired procedural level generatir built in C++ using Test-Driven Development.

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

## 📊 Development Progress

![Tests](https://img.shields.io/badge/tests-0%20passing-red)
![Coverage](https://img.shields.io/badge/coverage-0%25-red)

### Current Status: Week 1 - Room System

- [ ] Basic Room class
- [ ] Exit configuration
- [ ] Room metadata (biome, difficulty, rewards)

## 🚀 Building
```bash
# Configure
cmake -B build

# Build
cmake --build build

# Run tests
cd build
ctest --output-on-failure