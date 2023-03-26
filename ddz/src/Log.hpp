#ifndef __DDZ_LOG_HPP__
#define __DDZ_LOG_HPP__

#include "StringRef.hpp"
#include "platform/SysFuncs.hpp"

namespace ddz::log {

class LogBuffer {
public:
  virtual void writeTo(const ::ddz::StringRef &ref) const = 0;
  virtual LogBuffer *copy() const = 0;
  virtual ~LogBuffer() {}
};

class BaseBuffer : public LogBuffer {
public:
  virtual void writeTo(const ::ddz::StringRef &ref) const override {
  } // do nothing
  virtual LogBuffer *copy() const override { return new BaseBuffer(); }
};

class Logger {
public:
  virtual ~Logger() { delete buffer; }

  Logger(const LogBuffer &buffer) : buffer(buffer.copy()) {
	GLOBAL_LOGGER = this;
  }

  static Logger* GLOBAL_LOGGER;

  void info(const ::ddz::StringRef &ref);

  DDZ_INLINE LogBuffer &getBuffer() noexcept { return *buffer; }

protected:
  LogBuffer *buffer;
};

}; // namespace ddz::log

#endif /* end of include guard: __DDZ_LOG_HPP__ */
