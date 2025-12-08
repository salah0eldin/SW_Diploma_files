#include "Utilities.hpp"
#include <sstream>
#include <iostream>

namespace Utilities {

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    
    while (std::getline(tokenStream, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

std::string join(const std::vector<std::string>& strings, const std::string& delimiter) {
    if (strings.empty()) {
        return "";
    }
    
    std::ostringstream result;
    result << strings[0];
    
    for (size_t i = 1; i < strings.size(); ++i) {
        result << delimiter << strings[i];
    }
    
    return result.str();
}

bool startsWith(const std::string& str, const std::string& prefix) {
    if (prefix.length() > str.length()) {
        return false;
    }
    return str.compare(0, prefix.length(), prefix) == 0;
}

bool endsWith(const std::string& str, const std::string& suffix) {
    if (suffix.length() > str.length()) {
        return false;
    }
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t startPos = 0;
    while ((startPos = str.find(from, startPos)) != std::string::npos) {
        str.replace(startPos, from.length(), to);
        startPos += to.length();
    }
    return str;
}

void printBanner(const std::string& message) {
    int width = message.length() + 4;
    std::string border(width, '=');
    
    std::cout << '\n' << border << '\n';
    std::cout << "  " << message << '\n';
    std::cout << border << '\n' << '\n';
}

void printSeparator(int length, char character) {
    std::cout << std::string(length, character) << '\n';
}

}
