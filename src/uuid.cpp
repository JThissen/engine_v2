#include "uuid.hpp"
#include "utils.hpp"

namespace engine {
  std::string UUID::create() {
    static std::random_device randomDevice;
    static std::mt19937 rng32;
    std::uniform_int_distribution<int> dist(0, 15);
    std::string chars = "0123456789abcdef";
    std::array<bool, 16> dash = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0 };
    std::string result;
    for(int i = 0; i < dash.size(); i++) {
      if(dash[i] == 1) {
        result += "-";
      }
      result += chars[dist(rng32)];
      result += chars[dist(rng32)];
    }
    return result;
  }

  int UUID::createInt() {
    //we stay below 2^32 = 4294967296
    static std::random_device randomDevice;
    static std::mt19937 rng32;
    std::string chars = "123456789";
    std::uniform_int_distribution<int> dist(0, 8);
    std::string result;
    for(int i = 0; i < 9; i++) {
      result += chars[dist(rng32)];
    }
    return std::stoi(result);
  }
}