/**
 * @file INIReaderVec.cpp
 * @author mohamed.ghita@radalytica.com
 * @copyright radalytica
 * @date 02.06.2019
 */

#include "INIReaderVec.h"
#include <algorithm>
#include <regex>

namespace inih::extended {

INIReaderVec::INIReaderVec(const std::string& fileName) : INIReader(fileName) {}

INIReaderVec::~INIReaderVec() {}

std::vector<long> INIReaderVec::GetIntegerVector(const std::string& section, const std::string& name) const {
    return this->GetVector<long>(section, name);
}

std::vector<double> INIReaderVec::GetRealVector(const std::string& section, const std::string& name) const {
    return this->GetVector<double>(section, name);
}

std::vector<std::string> INIReaderVec::GetStringVector(const std::string& section, const std::string& name) const {
    return this->GetVector<std::string>(section, name);
}

std::vector<bool> INIReaderVec::GetBooleanVector(const std::string& section, const std::string& name) const {
    return this->GetVector<bool>(section, name);
}

template <typename T>
std::vector<T> INIReaderVec::GetVector(const std::string& section, const std::string& name) const {
    std::vector<T> valuesVector;
    std::string stringValue = this->Get(section, name, "[]");
    // get the values between [.+]
    std::smatch results;
    if (!std::regex_match(stringValue, results, std::regex("\\[(.+)\\]"))) return valuesVector;
    std::string arrayValues = results[1].str();
    // parse elements
    std::size_t posI = 0;
    for (;;) {
        auto posF = arrayValues.find_first_of(',', posI);
        std::size_t count = posF - posI;
        if (posF == std::string::npos) count = std::string::npos;
        auto value = arrayValues.substr(posI, count);
        posI = posF + 1;

        try {
            if constexpr (std::is_same<T, bool>::value) {
                INIReaderVec::trim(value);
                std::transform(value.begin(), value.end(), value.begin(), ::tolower);
                if (value == "true" || value == "yes" || value == "on" || value == "1")
                    valuesVector.push_back(true);
                else if (value == "false" || value == "no" || value == "off" || value == "0")
                    valuesVector.push_back(false);
            } else if constexpr (std::numeric_limits<T>::is_integer)
                valuesVector.push_back(std::stol(value));
            else if constexpr (std::is_floating_point<T>::value)
                valuesVector.push_back(std::stod(value));
            else if constexpr (std::is_same<T, std::string>::value)
                valuesVector.push_back(value);
        } catch (...) {}
        if (posF == std::string::npos) break;
    }
    return valuesVector;
}

void INIReaderVec::trim(std::string& s) {
    rtrim(s);
    ltrim(s);
}

void INIReaderVec::ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](const char& ch) { return !std::isspace(ch); }));  // ltrim
}

void INIReaderVec::rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](const char& ch) { return !std::isspace(ch); }).base(), s.end());  // rtime
}

}  // namespace inih::extended
