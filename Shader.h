//
// Created by nicola on 25/01/2021.
//

#pragma once

#include <string>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    void use();

    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);

    unsigned int id;

private:
    void checkCompileErrors(unsigned int shader, const std::string& type);
};
