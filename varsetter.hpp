#pragma once
#include <unordered_map>
#include <variant>
#include <string>
#include <vector>
#include <functional>

struct Env;

using Function = std::function<double(const std::vector<double>&)>;

using Value = std::variant<
    double,
    std::string,
    bool,
    Function
>;

struct Var {
    std::string type;
    Value value;
};

struct Env {
    std::unordered_map<std::string, Var> vars;
};

void interpret_line(Env* env, const std::string& line);
void interpret_text(Env* env, const std::string& text);

double getDouble(Env* env, const std::string& k);
std::string getStr(Env* env, const std::string& k);
bool getBool(Env* env, const std::string& k);
Function getFunc(Env* env, const std::string& k);
