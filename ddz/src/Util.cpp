#include "Util.hpp"

ddz::StringRef ddz::util::getTimeAsString() {
	time_t now_time = time(NULL);
	tm* t_tm = localtime(&now_time);
	return asctime(t_tm);
}

::ddz::StringRef concatString(const char *data1, const char *data2,
                              size_t data1Len, size_t data2Len) {
    char *ndata = (char *)::malloc(data1Len + data2Len + 1);
    ::strncpy(ndata, data1, data1Len);
    ::strncpy(ndata + data1Len, data2, data2Len);
    return ddz::StringRef(ndata, true);
}
