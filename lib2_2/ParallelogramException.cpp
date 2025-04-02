#include "ParallelogramException.h"

const char* ParallelogramException::what() const noexcept
{
    return message.c_str();
}
