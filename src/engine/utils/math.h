#pragma once
#include <glm/glm.hpp>
namespace engine::utils
{
    struct Rect
    {
        /* data */
        glm::vec2 position{};
        glm::vec2 size{};

        Rect() = default;
        Rect(glm::vec2 position, glm::vec2 size) : position(position), size(size) {}
        Rect(float x, float y, float width, float height) : position(x, y), size(width, height) {}
    };

    struct FColor
    {
        float r{}, g{}, b{}, a{};
    };
}