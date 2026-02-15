#pragma once
#include "component.h"
#include <string>
#include <unordered_map>
#include <memory>

namespace engine::render
{
    class Animation;
}

namespace engine::component
{
    class SpriteComponent;
}

namespace engine::component
{
    class AnimationComponent : public Component
    {
        friend class engine::object::GameObject;

    private:
        std::unordered_map<std::string, std::unique_ptr<engine::render::Animation>> animations_;
        SpriteComponent *sprite_component_ = nullptr;
        engine::render::Animation *current_animation_ = nullptr;

        float animation_timer_ = 0.0f;
        bool is_playing_ = false;
        bool is_one_shot_removal_ = false;

    public:
        AnimationComponent() = default;
        ~AnimationComponent() override;
        AnimationComponent(const AnimationComponent &) = delete;
        AnimationComponent(AnimationComponent &&) = delete;
        AnimationComponent &operator=(const AnimationComponent &) = delete;
        AnimationComponent &operator=(AnimationComponent &&) = delete;

        void addAnimation(std::unique_ptr<engine::render::Animation> &&animation);
        void playAnimation(const std::string &name);

        void stopAnimation() { is_playing_ = false; }
        void resumeAnimation() { is_playing_ = true; }

        std::string getCurrentAnimationName() const;
        bool isPlaying() const { return is_playing_; }
        bool isAnimationFinished() const;
        bool isOneShotRemoval() const { return is_one_shot_removal_; }
        void setOneShotRemoval(bool value) { is_one_shot_removal_ = value; }

    protected:
        void init() override;
        void update(float dt, engine::core::Context &) override;
    };
}