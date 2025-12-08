#include "ProcessorFactory.hpp"
#include "Configuration.hpp"
#include "Utilities.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

/**
 * @brief Main function demonstrating the Configurable Data Processing System
 * 
 * This program demonstrates:
 * - Reading configuration from a file
 * - Using the Factory pattern to create processors dynamically
 * - Processing different types of data (Text, Numeric, Image, Audio)
 * - Robust exception handling
 * - STL usage (vector, map)
 */
int main() {
    Utilities::printBanner("Configurable Data Processing System");

    try {
        // Step 1: Load configuration from file
        std::cout << "Loading configuration from config/settings.txt...\n";
        Configuration config("config/settings.txt");
        
        // Optional: Print all configuration options for debugging
        // config.printAll();
        
        // Step 2: Get the processor type from configuration
        std::string processorType = config.getOption("Processor.Options.Type");
        std::cout << "Selected Processor Type: " << processorType << '\n';
        
        // Step 3: Get optional configuration values
        std::string threshold = config.getOption("Processor.Options.Threshold", "N/A");
        std::string maxRetries = config.getOption("Processor.Options.MaxRetries", "N/A");
        
        std::cout << "Configuration Options:\n";
        std::cout << "  - Threshold: " << threshold << '\n';
        std::cout << "  - Max Retries: " << maxRetries << '\n';
        std::cout << '\n';
        
        // Step 4: Create processor using Factory pattern
        std::cout << "Creating processor...\n";
        std::unique_ptr<Processor> processor(ProcessorFactory::createProcessor(processorType));
        std::cout << "Processor created successfully: " << processor->getType() << "Processor\n\n";
        
        // Step 5: Prepare sample data based on processor type
        std::vector<std::string> data;
        std::string lowerType = processorType;
        std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);
        
        if (lowerType == "text") {
            data = {"Hello World", "C++ Programming", "Design Patterns", "STL Containers"};
        } else if (lowerType == "numeric") {
            data = {"42", "3.14159", "100", "2.71828", "invalid", "256"};
        } else if (lowerType == "image") {
            data = {"image001.jpg", "photo_sunset.png", "portrait.bmp"};
        } else if (lowerType == "audio") {
            data = {"song01.mp3", "podcast_episode.wav", "soundeffect.ogg"};
        } else {
            data = {"Sample1", "Sample2", "Sample3"};
        }
        
        // Step 6: Process the data
        Utilities::printBanner("Processing Data");
        processor->process(data);
        
        // Success message
        std::cout << "\n";
        Utilities::printBanner("Processing Completed Successfully");
        
    } catch (const std::invalid_argument& e) {
        std::cerr << "\n[CONFIGURATION ERROR] " << e.what() << '\n';
        std::cerr << "Please check your configuration file and processor type.\n";
        return 1;
    } catch (const std::runtime_error& e) {
        std::cerr << "\n[RUNTIME ERROR] " << e.what() << '\n';
        std::cerr << "Please ensure the configuration file exists and is properly formatted.\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "\n[UNEXPECTED ERROR] " << e.what() << '\n';
        return 1;
    }

    return 0;
}
