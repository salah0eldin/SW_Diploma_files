#include "Configuration.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

Configuration::Configuration(const std::string& filePath) : configFilePath(filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open configuration file: " + filePath);
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        lineNumber++;
        try {
            parseLine(line);
        } catch (const std::exception& e) {
            std::cerr << "Warning: Error parsing line " << lineNumber << ": " << e.what() << '\n';
        }
    }

    file.close();

    if (configMap.empty()) {
        throw std::runtime_error("Configuration file is empty or contains no valid entries: " + filePath);
    }
}

std::string Configuration::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

void Configuration::parseLine(const std::string& line) {
    std::string trimmedLine = trim(line);

    // Skip empty lines and comments
    if (trimmedLine.empty() || trimmedLine[0] == '#') {
        return;
    }

    // Find the '=' delimiter
    size_t delimiterPos = trimmedLine.find('=');
    if (delimiterPos == std::string::npos) {
        // Line doesn't contain '=', skip it
        return;
    }

    // Extract key and value
    std::string key = trim(trimmedLine.substr(0, delimiterPos));
    std::string value = trim(trimmedLine.substr(delimiterPos + 1));

    if (key.empty()) {
        throw std::runtime_error("Invalid configuration line: key is empty");
    }

    // Store in the map
    configMap[key] = value;
}

std::string Configuration::getOption(const std::string& key) const {
    auto it = configMap.find(key);
    if (it == configMap.end()) {
        throw std::runtime_error("Configuration key not found: " + key);
    }
    return it->second;
}

std::string Configuration::getOption(const std::string& key, const std::string& defaultValue) const {
    auto it = configMap.find(key);
    if (it == configMap.end()) {
        return defaultValue;
    }
    return it->second;
}

bool Configuration::hasOption(const std::string& key) const {
    return configMap.find(key) != configMap.end();
}

void Configuration::printAll() const {
    std::cout << "Configuration options from: " << configFilePath << '\n';
    std::cout << "------------------------------------\n";
    for (const auto& pair : configMap) {
        std::cout << pair.first << " = " << pair.second << '\n';
    }
    std::cout << "------------------------------------\n";
}
