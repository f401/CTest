#include "Log.hpp"
#include "Util.hpp"

#error "Did not finish"

using namespace ddz;
using ddz::StringRef;
using std::string;

const static string Base = "[" + util::getTimeAsString().cppStr() + "]" + " " +
                           std::to_string(platform::get_pid()) + "/" +
                           std::to_string(platform::get_tid()) + " ";

void ddz::log::Logger::info(const StringRef &ref) {
}
