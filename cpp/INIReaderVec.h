/**
 * @file INIReaderVec.h
 * @author mohamed.ghita@radalytica.com
 * @copyright radalytica
 * @date 02.06.2019
 */

#ifndef INIREADERVEC_H_
#define INIREADERVEC_H_

#include "./INIReader.h"
#include <string>
#include <vector>

namespace inih::extended {

/**
 * @brief INIReaderVec
 * support arrays of string, integer, boolean, and real. For example:
 * real_array = [0.0, 1.1, -1.1]
 * integer_array = [0, 1, -1]
 * boolean_array = [false, true]
 * string_array = [hello, array]
 *
 * Error handling
 * real_array = [1.1, false, 3.3] # the none real values will be discarded.
 * returns [1.1, 3.3] real_array = not an array # returns empty array []
 *
 * if the requested variable or section do not exist, an empty array is
 * returned.
 */
class INIReaderVec : public INIReader {
   public:
    INIReaderVec(const std::string& fileName);
    virtual ~INIReaderVec();

    std::vector<std::string> GetStringVector(const std::string& section, const std::string& name) const;
    std::vector<long> GetIntegerVector(const std::string& section, const std::string& name) const;
    std::vector<double> GetRealVector(const std::string& section, const std::string& name) const;
    std::vector<bool> GetBooleanVector(const std::string& section, const std::string& name) const;

   private:
    template <typename T>
    std::vector<T> GetVector(const std::string& section, const std::string& name) const;
    static void trim(std::string& value);
    static void rtrim(std::string& value);
    static void ltrim(std::string& value);

};  // class INIReaderVec
}  // namespace inih::extended

#endif
