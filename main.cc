#include <iostream>
#include "md5.hh"


int main(){
    std::cout << "Hello world!!" << std::endl;
    Md5 md;
    std::cout << md.encrypt("Hello world!!") << std::endl;
    std::cout << "1d94dd7dfd050410185a535b9575e184" << std::endl;
    /*std::cout << md.encrypt("Hello world!!") << std::endl;
    std::cout << md.encrypt("Hello world!!") << std::endl;*/
    return 0;
}