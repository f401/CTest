#ifndef __DDZ_LOG_HPP__
#define __DDZ_LOG_HPP__

#include "StringRef.hpp"
#include "platform/SysFuncs.hpp"

namespace ddz::log {

class LogBuffer {
public:
	virtual void writeTo(const ::ddz::StringRef &ref) const = 0;
};

class Logger {
public:
	const LogBuffer& buffer;
	Logger(const LogBuffer &buffer): buffer(buffer) {}

	void info(const ::ddz::StringRef& ref);
};

};

#endif /* end of include guard: __DDZ_LOG_HPP__ */
