#ifndef DELTATIME_H
#define DELTATIME_H

namespace engine {
  class DeltaTime {
  private:
    float time;
  public:
    DeltaTime(float time = 0.0f);
    operator float();
    float seconds();
    float milliseconds();
  };
}

#endif
