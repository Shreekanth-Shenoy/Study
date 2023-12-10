#include <iostream>

// Subject Interface
class BookParser {
public:
    virtual void parse() = 0;
};

// Real Subject
class RealBookParser : public BookParser {
public:
    RealBookParser(const std::string& book) : bookName(book) {
        // Simulate the expensive parsing operation
        std::cout << "RealBookParser: Parsing the book \"" << bookName << "\" (expensive operation).\n";
    }

    void parse() override {
        std::cout << "RealBookParser: Parsing the book \"" << bookName << "\".\n";
        // Actual parsing logic
    }

private:
    std::string bookName;
};

// Proxy
class LazyProxyBookParser : public BookParser {
private:
    RealBookParser* realBookParser;  

    std::string bookName;

public:
    LazyProxyBookParser(const std::string& book) : bookName(book), realBookParser(nullptr) {}

    void parse() override {
        if (!realBookParser) {
            realBookParser = new RealBookParser(bookName);
        }

        // Additional functionality before delegating to the real object
        std::cout << "LazyProxyBookParser: Checking permissions.\n";

        realBookParser->parse();

        // Additional functionality after delegating to the real object
        std::cout << "LazyProxyBookParser: Logging the parsing activity.\n";
    }

    ~LazyProxyBookParser() {
        // Clean up the real object in the destructor
        delete realBookParser;
    }
};

int main() {
    // Using the proxy for book parsing
    LazyProxyBookParser proxy("The Art of Programming");
    proxy.parse();  // The real object is loaded here

    std::cout<<std::endl;
    // Using the proxy again (no reloading of the real object)
    proxy.parse();

    return 0;
}
