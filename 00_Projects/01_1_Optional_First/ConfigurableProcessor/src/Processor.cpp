#include "Processor.hpp"
#include <algorithm>
#include <numeric>
#include <sstream>
#include <cctype>

// ====================== TextProcessor Implementation ======================

void TextProcessor::process(const std::vector<std::string>& data) {
    std::cout << "TextProcessor: Processing " << data.size() << " text items\n";
    std::cout << "------------------------------------\n";
    
    int totalWords = 0;
    int totalChars = 0;
    
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << "Item " << (i + 1) << ": ";
        processSingle(data[i]);
        totalWords += wordCount(data[i]);
        totalChars += data[i].length();
    }
    
    std::cout << "------------------------------------\n";
    std::cout << "Summary: Total words = " << totalWords 
              << ", Total characters = " << totalChars << '\n';
}

void TextProcessor::processSingle(const std::string& item) {
    int words = wordCount(item);
    std::string upper = toUpperCase(item);
    std::cout << "\"" << item << "\" -> " 
              << words << " word(s), Uppercase: \"" << upper << "\"\n";
}

std::string TextProcessor::getType() const {
    return "Text";
}

int TextProcessor::wordCount(const std::string& text) const {
    if (text.empty()) return 0;
    
    std::istringstream iss(text);
    int count = 0;
    std::string word;
    while (iss >> word) {
        count++;
    }
    return count;
}

std::string TextProcessor::toUpperCase(const std::string& text) const {
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// ====================== NumericProcessor Implementation ======================

void NumericProcessor::process(const std::vector<std::string>& data) {
    std::cout << "NumericProcessor: Processing " << data.size() << " numeric items\n";
    std::cout << "------------------------------------\n";
    
    std::vector<double> numbers;
    
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << "Item " << (i + 1) << ": ";
        processSingle(data[i]);
        
        if (isNumeric(data[i])) {
            numbers.push_back(parseDouble(data[i]));
        }
    }
    
    if (!numbers.empty()) {
        double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
        double avg = sum / numbers.size();
        double minVal = *std::min_element(numbers.begin(), numbers.end());
        double maxVal = *std::max_element(numbers.begin(), numbers.end());
        
        std::cout << "------------------------------------\n";
        std::cout << "Statistics: Sum = " << sum 
                  << ", Average = " << avg 
                  << ", Min = " << minVal 
                  << ", Max = " << maxVal << '\n';
    }
}

void NumericProcessor::processSingle(const std::string& item) {
    if (isNumeric(item)) {
        double value = parseDouble(item);
        std::cout << "\"" << item << "\" -> Numeric value: " << value 
                  << ", Squared: " << (value * value) << '\n';
    } else {
        std::cout << "\"" << item << "\" -> Not a valid number\n";
    }
}

std::string NumericProcessor::getType() const {
    return "Numeric";
}

bool NumericProcessor::isNumeric(const std::string& str) const {
    if (str.empty()) return false;
    
    std::istringstream iss(str);
    double d;
    iss >> std::noskipws >> d;
    return iss.eof() && !iss.fail();
}

double NumericProcessor::parseDouble(const std::string& str) const {
    return std::stod(str);
}

// ====================== ImageProcessor Implementation ======================

void ImageProcessor::process(const std::vector<std::string>& data) {
    std::cout << "ImageProcessor: Processing " << data.size() << " image items\n";
    std::cout << "------------------------------------\n";
    
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << "Image " << (i + 1) << ": ";
        processSingle(data[i]);
    }
    
    std::cout << "------------------------------------\n";
    std::cout << "Image processing complete\n";
}

void ImageProcessor::processSingle(const std::string& item) {
    std::cout << "Processing image data: \"" << item << "\"\n";
    applyFilter(item);
}

std::string ImageProcessor::getType() const {
    return "Image";
}

void ImageProcessor::applyFilter(const std::string& imageData) const {
    std::cout << "  -> Applying filters to image\n";
    std::cout << "  -> Adjusting brightness and contrast\n";
    std::cout << "  -> Applying threshold\n";
    std::cout << "  -> Image processed successfully\n";
}

// ====================== AudioProcessor Implementation ======================

void AudioProcessor::process(const std::vector<std::string>& data) {
    std::cout << "AudioProcessor: Processing " << data.size() << " audio items\n";
    std::cout << "------------------------------------\n";
    
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << "Audio " << (i + 1) << ": ";
        processSingle(data[i]);
    }
    
    std::cout << "------------------------------------\n";
    std::cout << "Audio processing complete\n";
}

void AudioProcessor::processSingle(const std::string& item) {
    std::cout << "Processing audio data: \"" << item << "\"\n";
    normalizeAudio(item);
}

std::string AudioProcessor::getType() const {
    return "Audio";
}

void AudioProcessor::normalizeAudio(const std::string& audioData) const {
    std::cout << "  -> Normalizing audio levels\n";
    std::cout << "  -> Applying noise reduction\n";
    std::cout << "  -> Converting audio format\n";
    std::cout << "  -> Audio processed successfully\n";
}
