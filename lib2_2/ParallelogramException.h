#pragma once
#include <exception>
#include <string>

class ParallelogramException : public std::exception
{
private:
	std::string message;
public:
    explicit ParallelogramException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override;
};


