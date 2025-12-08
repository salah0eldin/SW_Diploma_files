# Quick Reference Guide

## Configurable Data Processing System

### Build Commands
```bash
make              # Compile the project
make clean        # Remove build artifacts
make run          # Build and run
make help         # Show available commands
```

### Test Different Processors
```bash
make test-text      # Test with TextProcessor
make test-numeric   # Test with NumericProcessor
make test-image     # Test with ImageProcessor
make test-audio     # Test with AudioProcessor
```

### Manual Configuration
Edit `config/settings.txt` and change the processor type:

**For Text Processing:**
```ini
Processor.Options.Type=Text
```

**For Numeric Processing:**
```ini
Processor.Options.Type=Numeric
```

**For Image Processing:**
```ini
Processor.Options.Type=Image
```

**For Audio Processing:**
```ini
Processor.Options.Type=Audio
```

### Processor Capabilities

#### TextProcessor
- Word counting
- Character counting
- Uppercase conversion
- Text analysis

#### NumericProcessor
- Sum calculation
- Average calculation
- Min/Max detection
- Number validation
- Squared values

#### ImageProcessor
- Filter application
- Brightness/contrast adjustment
- Threshold application
- Image format handling

#### AudioProcessor
- Audio normalization
- Noise reduction
- Format conversion
- Level adjustment

### File Structure
```
ConfigurableProcessor/
├── config/settings.txt    # Edit this to change processor type
├── include/               # Header files
├── src/                   # Source files
├── Makefile              # Build configuration
├── README.md             # Full documentation
└── PROJECT_SUMMARY.md    # Implementation details
```

### Common Issues

**Problem:** `Configuration file not found`
**Solution:** Ensure you're running from the ConfigurableProcessor directory

**Problem:** `Unsupported processor type`
**Solution:** Check spelling in settings.txt (Text, Numeric, Image, or Audio)

**Problem:** Compilation errors
**Solution:** Ensure g++ with C++11 support is installed

### Example Usage Session
```bash
# 1. Build the project
cd ConfigurableProcessor
make

# 2. Run with default settings (Image processor)
./ConfigurableProcessor

# 3. Test different processors
make test-text
make test-numeric

# 4. Clean up
make clean
```

### Adding New Processor Type

1. Add class in `include/Processor.hpp`:
```cpp
class MyProcessor : public Processor {
    // Implement pure virtual methods
};
```

2. Implement in `src/Processor.cpp`

3. Update Factory in `src/ProcessorFactory.cpp`:
```cpp
if (lowerType == "mytype") {
    return new MyProcessor();
}
```

4. Update `config/settings.txt`:
```ini
Processor.Options.Type=MyType
```

### Best Practices
- Always test after modifying configuration
- Use `make clean` before rebuilding if changes don't appear
- Check `make help` for available commands
- Refer to README.md for detailed documentation

---

**Quick Tip:** To see all available make targets, run: `make help`
