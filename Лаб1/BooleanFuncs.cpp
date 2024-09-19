#include "BooleanFuncs.h"

bool isInteger(const std::string& str) {
    if (str.empty()) {
        return false;
    }

    size_t startIndex = 0;

    for (size_t i = startIndex; i < str.length(); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }

    return true;
}