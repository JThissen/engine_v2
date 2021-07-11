#ifndef EVENT_BUS_THREAD_H
#define EVENT_BUS_THREAD_H

#include "headers.hpp"

namespace engine {
  class EventBusThread {
    public:
    EventBusThread() = default;
    ~EventBusThread();
    void attach(std::thread&& th);
    void detach();
    
    private:
    std::thread thread;
  };
}

#endif
