#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <string>
#include <vector>
#include <iostream>

/**
 * @class Processor
 * @brief Abstract base class for all processors
 * 
 * This class defines the interface for all processor types.
 * Derived classes must implement the process methods for specific data types.
 */
class Processor {
public:
    virtual ~Processor() = default;

    /**
     * @brief Process a collection of string data
     * @param data Vector of strings to process
     */
    virtual void process(const std::vector<std::string>& data) = 0;

    /**
     * @brief Process a single string item
     * @param item Single string to process
     */
    virtual void processSingle(const std::string& item) = 0;

    /**
     * @brief Get the processor type name
     * @return String representing the processor type
     */
    virtual std::string getType() const = 0;
};

/**
 * @class TextProcessor
 * @brief Processor specialized for text data
 * 
 * Handles text processing operations such as case conversion,
 * word counting, and text transformations.
 */
class TextProcessor : public Processor {
public:
    void process(const std::vector<std::string>& data) override;
    void processSingle(const std::string& item) override;
    std::string getType() const override;

private:
    int wordCount(const std::string& text) const;
    std::string toUpperCase(const std::string& text) const;
};

/**
 * @class NumericProcessor
 * @brief Processor specialized for numeric data
 * 
 * Handles numeric operations such as sum, average, min, and max calculations.
 */
class NumericProcessor : public Processor {
public:
    void process(const std::vector<std::string>& data) override;
    void processSingle(const std::string& item) override;
    std::string getType() const override;

private:
    bool isNumeric(const std::string& str) const;
    double parseDouble(const std::string& str) const;
};

/**
 * @class ImageProcessor
 * @brief Processor specialized for image data
 * 
 * Simulates image processing operations such as filtering,
 * threshold application, and format conversion.
 */
class ImageProcessor : public Processor {
public:
    void process(const std::vector<std::string>& data) override;
    void processSingle(const std::string& item) override;
    std::string getType() const override;

private:
    void applyFilter(const std::string& imageData) const;
};

/**
 * @class AudioProcessor
 * @brief Processor specialized for audio data
 * 
 * Simulates audio processing operations such as normalization,
 * format conversion, and effect application.
 */
class AudioProcessor : public Processor {
public:
    void process(const std::vector<std::string>& data) override;
    void processSingle(const std::string& item) override;
    std::string getType() const override;

private:
    void normalizeAudio(const std::string& audioData) const;
};

#endif // PROCESSOR_HPP
