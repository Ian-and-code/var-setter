#include "../varsetter.hpp"
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

int main() {
    Env env;

    interpret_text(&env, readFile("./test.txt"));

    // ===== doubles =====
    assert(getDouble(&env, "a") == 2);
    assert(getDouble(&env, "b") == 3);
    assert(getDouble(&env, "sum") == 5);
    assert(getDouble(&env, "prod") == 6);

    // ===== bool =====
    assert(getBool(&env, "flag") == true);

    // ===== string =====
    assert(getStr(&env, "msg") == "hola");

    // ===== function =====
    auto f = getFunc(&env, "mul");
    assert(f({4, 5}) == 20);
    assert(f({10, 2}) == 20);

    std::cout << "✔ Todos los tests pasaron\n";
    return 0;
}