#ifndef DELTA_TIME_H
#define DELTA_TIME_H

namespace engine {
  class DeltaTime {
  private:
    float time;
  public:
    DeltaTime(float time = 0.0f);
    float seconds();
    float milliseconds();
    operator float() { return time; }
  };
}

#endif
