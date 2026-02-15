#pragma once
#include "component.h"
#include <glm/glm.hpp>
#include <utility>

namespace engine::component
{
    /// @brief 管理GameObject的位置，旋转和缩放
    class TransformComponent : public Component
    {
        friend class engine::object::GameObject;

    public:
        glm::vec2 position_{0.0f, 0.0f};
        glm::vec2 scale_{1.0f, 1.0f};
        float rotation_{0.0f};
        TransformComponent(const glm::vec2 &position = {0.0f, 0.0f}, const glm::vec2 &scale = {1.0f, 1.0f}, float rotation = 0.0f) : position_(position), scale_(scale), rotation_(rotation) {};

        TransformComponent(const TransformComponent &) = delete;
        TransformComponent &operator=(const TransformComponent &) = delete;
        TransformComponent(TransformComponent &&) = delete;
        TransformComponent &operator=(TransformComponent &&) = delete;

        const glm::vec2 &getPosition() const { return position_; };
        const glm::vec2 &getScale() const { return scale_; };
        float getRotation() const { return rotation_; };
        void setPosition(const glm::vec2 &position) { position_ = position; };
        void setScale(const glm::vec2 &scale);
        void setRotation(float rotation) { rotation_ = rotation; };
        /// @brief 平移
        /// @param offset
        void translate(const glm::vec2 &offset) { position_ += offset; };

    private:
        void update(float dt, engine::core::Context &) override {}
    };
}