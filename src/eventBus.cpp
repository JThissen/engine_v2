#include "eventBus.hpp"

namespace engine {
  EventBus::~EventBus() { stop(); }

  void EventBus::post(std::function<void()> func, bool flush) {
    if(!running) { return; }
    std::lock_guard<std::mutex> lock(mutex);
    if(flush) { queue = std::queue<std::function<void()>>(); }
    queue.push(func);
  }

  void EventBus::start() {
    if(running) { return; }
    queue = std::queue<std::function<void()>>();
    running = true;
    eventBusThread.attach(std::thread([this](){
      entry();
    }));
  }

  void EventBus::stop() {
      running = false;
      post([](){;}, true);
      eventBusThread.detach();
  }

  void EventBus::entry() {
    while(running) {
      if(!queue.empty()) {
        std::function<void()> func = queue.front();
        if(func != nullptr) {
          std::lock_guard<std::mutex> lock(mutex);
          queue.pop();
          func();
        }
      }
    }
  }
}
