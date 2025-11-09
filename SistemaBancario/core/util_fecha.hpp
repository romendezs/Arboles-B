#pragma once

#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

namespace util {

inline std::string fechaActual() {
    std::time_t ahora = std::time(nullptr);
    std::tm* tiempoLocal = std::localtime(&ahora);
    std::ostringstream ss;
    ss << std::put_time(tiempoLocal, "%Y-%m-%d");
    return ss.str();
}

}  // namespace util

