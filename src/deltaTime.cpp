#include "deltatime.hpp"

namespace engine {
  DeltaTime::DeltaTime(float time) 
    : time(time) {}


  float DeltaTime::seconds() {
    return time;
  }

  float DeltaTime::milliseconds() {
    return time * 1000.0f;
  }
}
