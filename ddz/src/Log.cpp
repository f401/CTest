#include "Log.hpp"
#include "Util.hpp"

using namespace ddz;
using ddz::StringRef;
using std::string;

const static string tid = std::to_string(platform::get_tid()),
                    pid = std::to_string(platform::get_pid());

void ddz::log::Logger::info(const StringRef &ref) {
  std::string write = "[" + util::getTimeAsString().cppStr() + " " + pid + "/" +
                      tid + " ] I: " + ref.cppStr();
  buffer->writeTo(write);
}
