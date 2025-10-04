#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>
#include <map>
#include <fstream>
#include <sstream>
#include "Vector.h"

namespace PhysicsConstants {
    constexpr double G = 6.67430e-11; // m^3 kg^-1 s^-2
}
namespace Utils {
inline bool isEqual(double a, double b, double epsilon = 1e-3) {
    return std::fabs(a - b) < epsilon;
}
} 

static inline std::map<std::string, std::string> parseConfig(const std::string &filename) {
    std::ifstream file(filename);
    std::map<std::string, std::string> config;
    std::string line;
    while(std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        auto pos = line.find('=');
        if (pos == std::string::npos) continue;
        auto key = line.substr(0, pos);
        auto val = line.substr(pos + 1);
        config[key] = val;
    }
    return config;
    }

inline Vector parseOriginVector(const std::string &str) {
    std::istringstream iss(str);
    double x, y;
    char comma;
    if (!(iss >> x >> comma >> y)) {
        throw std::runtime_error("Invalid vector format");
    }
    return Vector(x, y);
}




#endif