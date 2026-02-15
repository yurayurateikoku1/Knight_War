#pragma once
#include "./component.h"
#include "../physics/collider.h"
#include "../utils/math.h"
#include "../utils/alignment.h"
#include <memory>

namespace engine::component
{
    class TransformComponent;
}

namespace engine::component
{
    /// @brief 碰撞盒组件
    class ColliderComponent final : public Component
    {
        friend class engine::object::GameObject;

    private:
        TransformComponent *transform_ = nullptr;
        /// @brief 碰撞器对象
        std::unique_ptr<engine::physics::Collider> collider_;
        glm::vec2 offset_{0.0f, 0.0f};
        engine::utils::Alignment alignment_ = engine::utils::Alignment::NONE;

        /// @brief 是否为触发器
        bool is_trigger_ = false;
        /// @brief 是否激活
        bool is_active_ = true;

    public:
        explicit ColliderComponent(std::unique_ptr<engine::physics::Collider> collider,
                                   engine::utils::Alignment alignment = engine::utils::Alignment::NONE,
                                   bool is_trigger = false,
                                   bool is_active = true);

        /// @brief 更新碰撞盒偏移,根据_alignment_
        void updateOffset();

        TransformComponent *getTransform() const { return transform_; }
        const engine::physics::Collider *getCollider() const { return collider_.get(); }
        const glm::vec2 &getOffset() const { return offset_; }
        engine::utils::Alignment getAlignment() const { return alignment_; }
        engine::utils::Rect getWorldAABB() const;
        bool isTrigger() const { return is_trigger_; }
        bool isActive() const { return is_active_; }

        void setAlignment(engine::utils::Alignment alignment);
        void setOffset(const glm::vec2 &offset) { offset_ = offset; }
        void setTrigger(bool is_trigger) { is_trigger_ = is_trigger; }
        void setActive(bool is_active) { is_active_ = is_active; }

    private:
        void init() override;
        void update(float, engine::core::Context &) override {}
    };
}