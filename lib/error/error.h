
#ifndef __ERROR_H__
#define __ERROR_H__

#include <config.h>
#include <exception>
#include <string>

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
