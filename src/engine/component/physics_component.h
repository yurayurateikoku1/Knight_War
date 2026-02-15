#pragma once
#include "component.h"
#include <glm/vec2.hpp>
namespace engine::physics
{
    class PhysicsEngine;
}

namespace engine::component
{
    class TransformComponent;

    /// @brief 物理组件
    class PhysicsComponent final : public Component
    {
        friend class engine::object::GameObject;

    public:
        glm::vec2 velocity_{0.0f, 0.0f}; // 移动速度

    private:
        engine::physics::PhysicsEngine *physics_engine_ = nullptr;
        TransformComponent *transform_ = nullptr;

        /// @brief 当前帧受力
        glm::vec2 force_ = {0.0f, 0.0f};
        /// @brief 物体质量
        float mass_ = 1.0f;
        /// @brief 物理是否受重力影响
        bool use_gravity_ = true;
        /// @brief 主件是否启用
        bool enabled_ = true;

        /// 碰撞状态标志
        bool collided_below_ = false;
        bool collided_above_ = false;
        bool collided_left_ = false;
        bool collided_right_ = false;
        bool collided_loadder_ = false;
        bool is_on_top_ladder_ = false;

    public:
        PhysicsComponent(engine::physics::PhysicsEngine *physics_engine, bool use_gravity = true, float mass = 1.0f);
        ~PhysicsComponent() override = default;
        PhysicsComponent(const PhysicsComponent &) = delete;
        PhysicsComponent(PhysicsComponent &&) = delete;
        PhysicsComponent &operator=(const PhysicsComponent &) = delete;
        PhysicsComponent &operator=(PhysicsComponent &&) = delete;

        void addForce(const glm::vec2 &force)
        {
            if (enabled_)
                force_ += force;
        }
        void clearForce() { force_ = {0.0f, 0.0f}; }
        const glm::vec2 &getForce() const { return force_; }

        float getMass() const { return mass_; }
        void setMass(float mass) { mass_ = (mass > 0.0f) ? mass : 1.0f; }
        bool getUseGravity() const { return use_gravity_; }
        void setUseGravity(bool use_gravity) { use_gravity_ = use_gravity; }
        bool getEnabled() const { return enabled_; }
        void setEnabled(bool enabled) { enabled_ = enabled; }
        void setVelocity(const glm::vec2 &velocity) { velocity_ = velocity; }
        TransformComponent *getTransform() const { return transform_; }

        void resetCollidedFlags()
        {
            collided_below_ = false;
            collided_above_ = false;
            collided_left_ = false;
            collided_right_ = false;
            collided_loadder_ = false;
            is_on_top_ladder_ = false;
        }

        void setCollidedBelow(bool collided) { collided_below_ = collided; }
        void setCollidedAbove(bool collided) { collided_above_ = collided; }
        void setCollidedLeft(bool collided) { collided_left_ = collided; }
        void setCollidedRight(bool collided) { collided_right_ = collided; }
        void setVelocity(glm::vec2 velocity) { velocity_ = std::move(velocity); }
        void setCollidedLoadder(bool collided) { collided_loadder_ = collided; }
        const glm::vec2 &getVelocity() const { return velocity_; }
        bool getCollidedBelow() const { return collided_below_; }
        bool getCollidedAbove() const { return collided_above_; }
        bool getCollidedLeft() const { return collided_left_; }
        bool getCollidedRight() const { return collided_right_; }
        bool getCollidedLoadder() const { return collided_loadder_; }
        bool isOnTopLadder() const { return is_on_top_ladder_; }
        void setOnTopLadder(bool on_top) { is_on_top_ladder_ = on_top; }

    private:
        void init() override;
        void update(float dt, engine::core::Context &) override {}
        void clean() override;
    };
}
