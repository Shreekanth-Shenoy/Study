#include <iostream>
#include <string>

// Implementor interface
class ContentFormatter {
public:
    virtual std::string formatShort() const = 0;
    virtual std::string formatLong() const = 0;
};

// Concrete Implementors
class AudioFormatter : public ContentFormatter {
public:
    std::string formatShort() const override {
        return "Short-form Audio";
    }

    std::string formatLong() const override {
        return "Long-form Audio";
    }
};

class VideoFormatter : public ContentFormatter {
public:
    std::string formatShort() const override {
        return "Short-form Video";
    }

    std::string formatLong() const override {
        return "Long-form Video";
    }
};

// Abstraction
class MediaType {
protected:
    ContentFormatter* formatter;

public:
    MediaType(ContentFormatter* formatter) : formatter(formatter) {}

    virtual void displayShort() const {
        std::cout << "Short: " << formatter->formatShort() << std::endl;
    }

    virtual void displayLong() const {
        std::cout << "Long: " << formatter->formatLong() << std::endl;
    }
};

// Refined Abstractions
class AudioMedia : public MediaType {
public:
    AudioMedia(ContentFormatter* formatter) : MediaType(formatter) {}
};

class VideoMedia : public MediaType {
public:
    VideoMedia(ContentFormatter* formatter) : MediaType(formatter) {}
};

int main() {
    AudioFormatter audioFormatter;
    VideoFormatter videoFormatter;

    AudioMedia shortAudio(&audioFormatter);
    AudioMedia longAudio(&audioFormatter);

    VideoMedia shortVideo(&videoFormatter);
    VideoMedia longVideo(&videoFormatter);

    shortAudio.displayShort();  // Output: Short: Short-form Audio
    longAudio.displayLong();    // Output: Long: Long-form Audio

    shortVideo.displayShort();  // Output: Short: Short-form Video
    longVideo.displayLong();    // Output: Long: Long-form Video

    return 0;
}
