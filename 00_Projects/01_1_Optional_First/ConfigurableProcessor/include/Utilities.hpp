#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <vector>

/**
 * @namespace Utilities
 * @brief Collection of utility functions for the project
 */
namespace Utilities {

    /**
     * @brief Splits a string by a delimiter
     * @param str The string to split
     * @param delimiter The delimiter character
     * @return Vector of string tokens
     */
    std::vector<std::string> split(const std::string& str, char delimiter);

    /**
     * @brief Joins a vector of strings with a delimiter
     * @param strings The vector of strings to join
     * @param delimiter The delimiter string
     * @return Joined string
     */
    std::string join(const std::vector<std::string>& strings, const std::string& delimiter);

    /**
     * @brief Checks if a string starts with a specific prefix
     * @param str The string to check
     * @param prefix The prefix to look for
     * @return true if str starts with prefix, false otherwise
     */
    bool startsWith(const std::string& str, const std::string& prefix);

    /**
     * @brief Checks if a string ends with a specific suffix
     * @param str The string to check
     * @param suffix The suffix to look for
     * @return true if str ends with suffix, false otherwise
     */
    bool endsWith(const std::string& str, const std::string& suffix);

    /**
     * @brief Replaces all occurrences of a substring in a string
     * @param str The original string
     * @param from The substring to replace
     * @param to The replacement substring
     * @return String with all replacements made
     */
    std::string replaceAll(std::string str, const std::string& from, const std::string& to);

    /**
     * @brief Prints a banner message with decorative borders
     * @param message The message to display
     */
    void printBanner(const std::string& message);

    /**
     * @brief Prints a separator line
     * @param length The length of the separator
     * @param character The character to use for the separator
     */
    void printSeparator(int length = 50, char character = '-');

}

#endif // UTILITIES_HPP
