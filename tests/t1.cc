#include "../varsetter.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

std::string ReadTestFile(const int& n) {
    std::string path = "./t"+std::to_string(n)+".txt";
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file)
        throw std::runtime_error("No se pudo abrir el archivo: " + path);

    std::ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}

std::string btos(bool value){
    std::string r;
    if (value == true) r = "true"; else r="false";
    return r;
}
int main() {
    Env env;
    interpret_text(&env, ReadTestFile(1));
    std::cout << "x = " << getDouble(&env, "x") << "\n";
    std::cout << "y = " << getDouble(&env, "y") << "\n";
    std::cout << "z = " << getDouble(&env, "z") << "\n";
    std::cout << "msg = " << '"' << getStr(&env, "msg") << '"' << "\n";
    std::cout << "flag = " << btos(getBool(&env, "flag")) << "\n";
}
