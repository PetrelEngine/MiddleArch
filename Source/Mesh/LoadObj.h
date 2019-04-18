#pragma once

#include <string>
#include <glm/vec3.hpp>
#include <vector>
#include <glm/vec2.hpp>
class LoadObj
{
public:
    LoadObj();
    ~LoadObj();

    bool ParseObj(const std::string fileName);

protected:
    std::vector<glm::vec3>  Vertex_;
    std::vector<glm::vec3>  Normal_;
    std::vector<glm::vec2>  TexCoord_;

};