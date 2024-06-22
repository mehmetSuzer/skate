
#ifndef __ERROR_H__
#define __ERROR_H__

#include <exception>
#include <string>

// In order to speed up the program and to reduce the size of the executable, you may disable error handlers.
// Disable them, only if you are sure that the code is error-free.
#define COMPILE_ERROR_HANDLERS 1

class Error : public std::exception {
private:
    std::string message;

public:
    explicit Error(const char* message_);
    explicit Error(const std::string& message_);

    ~Error() noexcept override = default;

    const char* what() const noexcept override;
};

#endif // __ERROR_H__
