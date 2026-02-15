#pragma once
#include <glm/vec2.hpp>

namespace engine::physics
{
    /// @brief 碰撞盒类型
    enum class ColliderType
    {
        NONE,
        AABB,
        CIRCLE
    };

    /// @brief 碰撞盒的抽象基类
    class Collider
    {
    protected:
        glm::vec2 aabb_size_ = {0.0f, 0.0f};

    public:
        virtual ColliderType getType() const = 0;
        virtual ~Collider() = default;

        void setAABBSize(const glm::vec2 &size) { aabb_size_ = size; }
        const glm::vec2 &getAABBSize() const { return aabb_size_; }
    };

    /// @brief 矩形碰撞盒
    class AABBCollider : public Collider
    {
    private:
        glm::vec2 size_ = {0.0f, 0.0f};

    public:
        explicit AABBCollider(const glm::vec2 &size = {0.0f, 0.0f}) : size_(size) { setAABBSize(size); };
        ~AABBCollider() override = default;

        ColliderType getType() const override { return ColliderType::AABB; }
        const glm::vec2 &getSize() const { return size_; }
        void setSize(const glm::vec2 &size) { size_ = size; }
    };

    class CircleCollider : public Collider
    {
    private:
        float radius_ = 0.0f;

    public:
        explicit CircleCollider(float radius = 0.0f) : radius_(radius) { setAABBSize({radius, radius}); };
        ~CircleCollider() override = default;

        ColliderType getType() const override { return ColliderType::CIRCLE; }
        float getRadius() const { return radius_; }
        void setRadius(float radius) { radius_ = radius; }
    };

}