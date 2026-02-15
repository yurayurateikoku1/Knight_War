#pragma once
#include "component.h"
#include "../render/sprite.h"
#include <string>
#include <glm/vec2.hpp>

namespace engine::component
{
    class TransformComponent;
    /// @brief 在背景中渲染视差滚动的贴图，根据相机的位置和视差滚动因子进行移动
    class ParallaxComponent : public Component
    {
        friend class engine::object::GameObject;

    private:
        /// @brief 缓存变换组件
        TransformComponent *transform_{nullptr};

        engine::render::Sprite sprite_;
        glm::vec2 scroll_factor_{1.0f, 1.0f};
        glm::bvec2 repeat_;
        bool is_hidden_ = false;

    public:
        ParallaxComponent(const std::string &texture_id, const glm::vec2 &scroll_factor, const glm::bvec2 &repeat);

        void setSprite(const engine::render::Sprite &sprite) { sprite_ = sprite; }
        void setScrollFactor(const glm::vec2 &scroll_factor) { scroll_factor_ = scroll_factor; }
        void setRepeat(const glm::bvec2 &repeat) { repeat_ = repeat; }
        void setIsHidden(bool is_hidden) { is_hidden_ = is_hidden; }

        const engine::render::Sprite &getSprite() const { return sprite_; }
        const glm::vec2 &getScrollFactor() const { return scroll_factor_; }
        const glm::bvec2 &getRepeat() const { return repeat_; }
        bool getIsHidden() const { return is_hidden_; }

    protected:
        void update(float dt, engine::core::Context &) override {}
        void init() override;
        void render(engine::core::Context &) override;
    };
}