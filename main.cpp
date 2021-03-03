#include <iostream>
#include "lib/xpp/include/xpp/window.hpp"

class connection;

class window : public xpp::window<connection&> {

};

int main() {

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
