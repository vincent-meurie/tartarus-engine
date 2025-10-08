#pragma once
#include <cmath>
#include <random>

namespace TestUtils {
/**
 * Seeded random number generator for reproducible tests
 */
class SeededRandom {
 public:
  explicit SeededRandom(uint32_t seed = 42) : engine_(seed) {}

  std::mt19937& GetEngine() { return engine_; }

  void SetSeet(uint32_t seed) { engine_.seed(seed); }

  // Helper: random int in range [min, max]
  int RandomInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine_);
  }

  // Helper: random float in range [min, max]
  float RandomDloat(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(engine_);
  }

 private:
  std::mt19937 engine_;
};

/**
 * Helper to compare floats with epsilon tolerance
 */
inline bool ApproxEqual(float a, float b, float epsilon = 0.001f) {
  return std::abs(a - b) < epsilon;
}
}  // namespace TestUtils