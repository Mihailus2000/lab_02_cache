//
// Created by mihailus on 22.09.2019.
//

#ifndef ANALYSECACHE_ANASYSISEXCEPTIONS_H
#define ANALYSECACHE_ANASYSISEXCEPTIONS_H

#include <exception>
#include <string>

class AnalysisExceptions : public std::exception {
public:
    AnalysisExceptions(std::string const &message) : message_(message) {}

    virtual ~AnalysisExceptions() = default;

    virtual char const *what() const noexcept {
        return message_.c_str();
    }

private:
    std::string message_;
};
#endif //ANALYSECACHE_ANASYSISEXCEPTIONS_H
