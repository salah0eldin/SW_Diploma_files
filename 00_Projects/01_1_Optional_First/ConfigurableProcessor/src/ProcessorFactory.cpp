#include "ProcessorFactory.hpp"
#include <algorithm>
#include <stdexcept>
#include <cctype>

Processor* ProcessorFactory::createProcessor(const std::string& type) {
    std::string lowerType = toLower(type);

    if (lowerType == "text") {
        return new TextProcessor();
    } else if (lowerType == "numeric") {
        return new NumericProcessor();
    } else if (lowerType == "image") {
        return new ImageProcessor();
    } else if (lowerType == "audio") {
        return new AudioProcessor();
    } else {
        throw std::invalid_argument("Unsupported processor type: " + type + 
                                    "\nSupported types are: Text, Numeric, Image, Audio");
    }
}

std::unique_ptr<Processor> ProcessorFactory::createProcessorUnique(const std::string& type) {
    return std::unique_ptr<Processor>(createProcessor(type));
}

std::string ProcessorFactory::toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), 
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}
