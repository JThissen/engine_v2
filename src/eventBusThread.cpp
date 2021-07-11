#include "eventBusThread.hpp"

namespace engine {
  EventBusThread::~EventBusThread() {
    detach();
  }

  void EventBusThread::attach(std::thread&& th) {
    thread = std::forward<std::thread&&>(th);
  }

  void EventBusThread::detach() {
    if(thread.joinable()) {
        thread.join();
    }
  }
}
