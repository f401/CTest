#ifndef __DDZ_EVENT_HPP__
#define __DDZ_EVENT_HPP__ 1

#include "../Collections.hpp"

namespace ddz::event {

template <typename... Params> class Event {
public:
  typedef void (*ListenerFP)(Params...);

  virtual bool subscribe(ListenerFP handle) {
    __listeners.push_back(handle);
    return true;
  }

  virtual void push(Params... params) {
    for (const ListenerFP &receiver : __listeners) {
      (*receiver)(params...);
    }
    __listeners.clear();
  }

protected:
  ddz::CommonCollections<ListenerFP> __listeners;
};

} // namespace ddz::event

#endif /* end of include guard: __DDZ_EVENT_HPP__ */
