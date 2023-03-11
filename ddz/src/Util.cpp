#include "Util.hpp"

ddz::StringRef ddz::util::getTimeAsString() {
	time_t now_time = time(NULL);
	tm* t_tm = localtime(&now_time);
	return asctime(t_tm);
}
