#include <stdexcept>

class BadFileFormatException : public std::runtime_error {
    public:
        BadFileFormatException() : std::runtime_error("Bad file format") {}
};
