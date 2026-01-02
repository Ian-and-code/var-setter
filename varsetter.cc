#include "varsetter.hpp"
#include <iostream>
#include <sstream>
#include <regex>
#include <stdexcept>

/* =========================
   FORWARD DECLARATIONS
   ========================= */

double eval_expr(Env* env, const std::string& expr);

/* =========================
   EXPRESIONES
   ========================= */

double resolve_double(Env* env, const std::string& tok) {
    if (env->vars.count(tok))
        return std::get<double>(env->vars[tok].value);
    return std::stod(tok);
}

double eval_expr(Env* env, const std::string& expr) {
    std::stringstream ss(expr);
    std::string a, op, b;
    ss >> a >> op >> b;

    double x = resolve_double(env, a);
    double y = resolve_double(env, b);

    if (op == "+") return x + y;
    if (op == "-") return x - y;
    if (op == "*") return x * y;
    if (op == "/") return x / y;

    throw std::runtime_error("operador invalido");
}

/* =========================
   FUNCIONES
   ========================= */

Function build_function(const std::string& params,
                        const std::string& body) {
    std::vector<std::string> names;
    std::stringstream ss(params);
    std::string name;

    while (std::getline(ss, name, ','))
        names.push_back(name);

    return [names, body](const std::vector<double>& args) -> double {
        if (args.size() != names.size())
            throw std::runtime_error("arity mismatch");

        Env local;
        for (size_t i = 0; i < args.size(); ++i)
            local.vars[names[i]] = {"double", args[i]};

        return eval_expr(&local, body);
    };
}

/* =========================
   INTERPRETE
   ========================= */

void interpret_line(Env* env, const std::string& line) {
    std::regex re(R"((\w+)\s*:\s*(\w+)\s*=\s*(.+);)");
    std::smatch m;

    if (!std::regex_match(line, m, re))
        throw std::runtime_error("syntax error");

    std::string name = m[1];
    std::string type = m[2];
    std::string expr = m[3];

    if (type == "double") {
        if (expr.find('(') != std::string::npos) {
            std::regex call(R"((\w+)\(([^)]*)\))");
            std::smatch c;
            std::regex_match(expr, c, call);

            auto fn = std::get<Function>(env->vars[c[1]].value);

            std::vector<double> args;
            std::stringstream as(c[2]);
            std::string v;
            while (std::getline(as, v, ','))
                args.push_back(resolve_double(env, v));

            env->vars[name] = {type, fn(args)};
        } else {
            env->vars[name] = {type, eval_expr(env, expr)};
        }
    }
    else if (type == "function") {
        std::regex fre(R"(\(([^)]*)\)\{(.+)\})");
        std::smatch f;
        std::regex_match(expr, f, fre);

        env->vars[name] = {
            type,
            build_function(f[1], f[2])
        };
    }
    else if (type == "str") {
        env->vars[name] = {
            type,
            expr.substr(1, expr.size() - 2)
        };
    }
    else if (type == "bool") {
        env->vars[name] = {
            type,
            expr == "true"
        };
    }
}

/* =========================
   TEXTO MULTILINEA
   ========================= */

void interpret_text(Env* env, const std::string& text) {
    std::istringstream ss(text);
    std::string line;
    while (std::getline(ss, line))
        if (!line.empty())
            interpret_line(env, line);
}

/* =========================
   GETTERS
   ========================= */

double getDouble(Env* env, const std::string& k) {
    return std::get<double>(env->vars[k].value);
}

std::string getStr(Env* env, const std::string& k) {
    return std::get<std::string>(env->vars[k].value);
}

bool getBool(Env* env, const std::string& k) {
    return std::get<bool>(env->vars[k].value);
}

Function getFunc(Env* env, const std::string& k) {
    return std::get<Function>(env->vars[k].value);
}
