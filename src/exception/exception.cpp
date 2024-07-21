
#include "exception.h"

namespace skate 
{
    Exception::Exception(const char* message_) : message(message_) {}

    Exception::Exception(const std::string& message_) : message(message_) {}

    const char* Exception::what() const noexcept 
    {
        return message.c_str();
    }
}
