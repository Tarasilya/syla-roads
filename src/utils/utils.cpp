#include "utils.h"

#include <sstream>

namespace utils {

std::string ToStr(int value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

};