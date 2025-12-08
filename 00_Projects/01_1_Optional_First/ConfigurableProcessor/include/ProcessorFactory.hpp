#ifndef PROCESSORFACTORY_HPP
#define PROCESSORFACTORY_HPP

#include "Processor.hpp"
#include <string>
#include <memory>

/**
 * @class ProcessorFactory
 * @brief Factory class for creating processor objects
 * 
 * Implements the Factory Design Pattern to create appropriate
 * processor instances based on the provided type string.
 * This decouples object creation from application logic.
 */
class ProcessorFactory {
public:
    /**
     * @brief Creates a processor based on the specified type
     * @param type The type of processor to create (Text, Numeric, Image, Audio)
     * @return Pointer to the created Processor object
     * @throws std::invalid_argument if the type is not supported
     * 
     * Supported types (case-insensitive):
     * - "Text" or "text" -> TextProcessor
     * - "Numeric" or "numeric" -> NumericProcessor
     * - "Image" or "image" -> ImageProcessor
     * - "Audio" or "audio" -> AudioProcessor
     */
    static Processor* createProcessor(const std::string& type);

    /**
     * @brief Creates a processor with smart pointer management
     * @param type The type of processor to create
     * @return Unique pointer to the created Processor object
     * @throws std::invalid_argument if the type is not supported
     */
    static std::unique_ptr<Processor> createProcessorUnique(const std::string& type);

private:
    /**
     * @brief Converts a string to lowercase for case-insensitive comparison
     * @param str The string to convert
     * @return Lowercase version of the string
     */
    static std::string toLower(const std::string& str);
};

#endif // PROCESSORFACTORY_HPP
