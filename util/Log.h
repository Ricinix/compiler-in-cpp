//
// Created by laugh on 2020/12/14.
//

#ifndef DESIGN_1_LOG_H
#define DESIGN_1_LOG_H

#include <string>
#include <iostream>

namespace Log {
    template<typename V>
    void error(const V &value) {
        using namespace std;
        cerr << "ERROR:" << endl << value << endl;
    }

    template<typename V>
    void info(const V &value) {
        using namespace std;
        cout << "INFO:" << endl << value << endl;
    }

    template<typename V>
    void warm(const V &value) {
        using namespace std;
        cout << "WARM: " << endl << value << endl;
    }

}

#endif //DESIGN_1_LOG_H
