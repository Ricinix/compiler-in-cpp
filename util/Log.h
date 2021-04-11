//
// Created by laugh on 2020/12/14.
//

#ifndef DESIGN_1_LOG_H
#define DESIGN_1_LOG_H

#include <string>
#include <iostream>

namespace Log {
    template<typename V>
    void _error(const V &value, const char *fileName, const int line, const char *funcName) {
        using namespace std;
        cerr << "[ERROR]" << fileName << "  line " << line << "  " << funcName << endl << value << endl;
    }

    #define error(v) _error(v, __FILE__, __LINE__, __FUNCTION__)

    template<typename V>
    void info(const V &value) {
        using namespace std;
        cout << "[INFO]" << endl << value << endl;
    }

    template<typename V>
    void warm(const V &value) {
        using namespace std;
        cout << "[WARM]" << endl << value << endl;
    }

}

#endif //DESIGN_1_LOG_H
