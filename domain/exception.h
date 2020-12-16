//
// Created by laugh on 2020/12/15.
//

#ifndef DESIGN_1_EXCEPTION_H
#define DESIGN_1_EXCEPTION_H

#include <string>
#include <stdexcept>

class StoneException: public std::runtime_error{
public:
    explicit StoneException(const std::string & msg): std::runtime_error(msg){}
};

#endif //DESIGN_1_EXCEPTION_H
