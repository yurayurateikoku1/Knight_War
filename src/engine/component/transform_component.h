#pragma once
#include <glm/glm.hpp>
#include <utility>

namespace engine::component
{
    /// @brief 变换组件
    struct TransformComponent
    {

    public:
        glm::vec2 position_{0.0f, 0.0f}; // 坐标
        glm::vec2 scale_{1.0f, 1.0f};    // 缩放
        float rotation_{0.0f};           // 旋转
        TransformComponent(const glm::vec2 &position = {0.0f, 0.0f}, const glm::vec2 &scale = {1.0f, 1.0f}, float rotation = 0.0f) : position_(position), scale_(scale), rotation_(rotation) {};
    };
}