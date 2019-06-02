#include <INIReaderVec.h>
#include <iostream>

template <typename T>
void printVector(const std::vector<T>& vec) {
    std::cout << "vector: [";
    for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
        std::cout << *iter << ((iter < vec.end() - 1) ? ", " : "");
    }
    std::cout << "]" << std::endl;
}

int main(int argc, char const* argv[]) {
    inih::extended::INIReaderVec reader("./vector_test.ini");
    std::cout << "parse error: " << reader.ParseError() << std::endl;

    auto boolVector = reader.GetBooleanVector("vector", "boolean_array_2");
    std::cout << "boolean_array_2 = " << reader.Get("vector", "boolean_array_2", "NONE") << ". ";
    printVector(boolVector);

    auto intVector = reader.GetIntegerVector("vector", "integer_array");
    std::cout << "integer_array = " << reader.Get("vector", "integer_array", "NONE") << ". ";
    printVector(intVector);

    auto doubleVector = reader.GetRealVector("vector", "real_array_2");
    std::cout << "real_array_2 = " << reader.Get("vector", "real_array_2", "NONE") << ". ";
    printVector(doubleVector);

    auto stringVector = reader.GetStringVector("vector", "string_array");
    std::cout << "string_array = " << reader.Get("vector", "string_array", "NONE") << ". ";
    printVector(stringVector);

    auto notArray = reader.GetStringVector("vector", "not_array");
    std::cout << "string_array = " << reader.Get("vector", "not_array", "NONE") << ". ";
    printVector(notArray);

    return 0;
}
