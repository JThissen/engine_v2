#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include "headers.hpp"
#include "eventBusThread.hpp"

namespace engine {
  class EventBus {
    public:
    EventBus() = default;
    ~EventBus();
    void post(std::function<void()> func, bool flush = false);
    void start();
    void stop();
    bool running = false;
    std::mutex mutex;
    std::queue<std::function<void()>> queue;
    EventBusThread eventBusThread;

    private:
    void entry();
  };
}

#endif
