
#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <exception>
#include <string>
#include "config.h"

class Exception : public std::exception {
private:
    std::string message;

public:
    explicit Exception(const char* message_);
    explicit Exception(const std::string& message_);

    ~Exception() noexcept override = default;

    const char* what() const noexcept override;
};

#endif // __EXCEPTION_H__
