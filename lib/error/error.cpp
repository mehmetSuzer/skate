
#include "error.h"

Error::Error(const char* message_) : message(message_) {}

Error::Error(const std::string& message_) : message(message_) {}

const char* Error::what() const noexcept {
    return message.c_str();
}
