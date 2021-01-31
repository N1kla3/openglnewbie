//
// Created by nicola on 25/01/2021.
//

#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    void use();

    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec2(const std::string& name, const glm::vec2& value) const ;
    void setVec2(const std::string& name, float x, float y) const ;
    void setVec3(const std::string& name, const glm::vec3& value) const ;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, const glm::vec2& value) const ;
    void setVec4(const std::string& name, float x, float y, float z, float w) const ;
    void setMat2(const std::string& name, const glm::mat2& value) const ;
    void setMat3(const std::string& name, const glm::mat3& value) const ;
    void setMat4(const std::string& name, const glm::mat4& value) const ;

    unsigned int id;

private:
    void checkCompileErrors(unsigned int shader, const std::string& type);
};
