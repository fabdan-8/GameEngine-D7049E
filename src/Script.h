#pragma once

#include <string>
#include <vector>

class Variable {
public:
    std::string name = "";
    std::string content = "";
    double value = 0;
    bool IsValue() {
        return content == "$value";
    }
    bool IsString() {
        return !IsValue();
    }
};

class Script {
public:
    std::vector<std::string> command;
    std::vector<std::vector<Variable>> argument;
    void Read();
private:
    float GetValue(std::string name, int a, float default_value = 0.0f);
    std::string GetContent(std::string name, int a, std::string default_content = "");
};