#include "deltatime.hpp"

namespace engine {
  DeltaTime::DeltaTime(float time) 
    : time(time) {}

  DeltaTime::operator float() {
    return time;
  }

  float DeltaTime::seconds() {
    return time;
  }

  float DeltaTime::milliseconds() {
    return time * 1000.0f;
  }
}
