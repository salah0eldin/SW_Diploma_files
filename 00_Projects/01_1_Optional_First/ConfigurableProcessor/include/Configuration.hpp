#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>
#include <map>
#include <fstream>
#include <stdexcept>

/**
 * @class Configuration
 * @brief Handles reading and parsing configuration files with nested dot notation support
 * 
 * This class reads a configuration file and parses key-value pairs.
 * It supports nested structures using dot notation (e.g., "Processor.Options.Type")
 * and ignores comments (lines starting with #).
 */
class Configuration {
private:
    std::map<std::string, std::string> configMap;
    std::string configFilePath;

    /**
     * @brief Trims whitespace from both ends of a string
     * @param str The string to trim
     * @return Trimmed string
     */
    std::string trim(const std::string& str);

    /**
     * @brief Parses a single line from the configuration file
     * @param line The line to parse
     */
    void parseLine(const std::string& line);

public:
    /**
     * @brief Constructor that loads and parses the configuration file
     * @param filePath Path to the configuration file
     * @throws std::runtime_error if file cannot be opened
     */
    Configuration(const std::string& filePath);

    /**
     * @brief Retrieves a configuration option by key
     * @param key The key in dot notation (e.g., "Processor.Options.Type")
     * @return The value associated with the key
     * @throws std::runtime_error if key is not found
     */
    std::string getOption(const std::string& key) const;

    /**
     * @brief Retrieves a configuration option with a default value
     * @param key The key in dot notation
     * @param defaultValue The default value to return if key is not found
     * @return The value associated with the key or defaultValue
     */
    std::string getOption(const std::string& key, const std::string& defaultValue) const;

    /**
     * @brief Checks if a configuration key exists
     * @param key The key to check
     * @return true if the key exists, false otherwise
     */
    bool hasOption(const std::string& key) const;

    /**
     * @brief Prints all configuration options (useful for debugging)
     */
    void printAll() const;
};

#endif // CONFIGURATION_HPP
