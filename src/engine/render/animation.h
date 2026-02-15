#pragma once
#include <SDL3/SDL_rect.h>
#include <vector>
#include <string>

namespace engine::render
{
    /**
     * @brief 代表动画中的单个帧。
     */
    struct AnimationFrame
    {
        SDL_Rect source_rect; // 纹理图集上此帧的区域
        float duration;       // 持续时间
    };

    class Animation final
    {
    private:
        std::string name_;
        std::vector<AnimationFrame> frames_;
        float total_duration_;
        bool loop_ = true;

    public:
        Animation(const std::string &name = "default", bool loop = true);
        ~Animation() = default;

        Animation(const Animation &) = delete;
        Animation(Animation &&) = delete;
        Animation &operator=(const Animation &) = delete;
        Animation &operator=(Animation &&) = delete;

        void addFrame(const SDL_Rect &source_rect, float duration);

        const AnimationFrame &getFrame(float time) const;

        const std::string &getName() const { return name_; }
        const std::vector<AnimationFrame> &getFrames() const { return frames_; };
        size_t getFrameCount() const { return frames_.size(); }
        float getTotalDuration() const { return total_duration_; }
        bool isLooping() const { return loop_; }
        bool isEmpty() const { return frames_.empty(); }

        void setName(const std::string &name) { name_ = name; }
        void setLopping(bool loop) { loop_ = loop; }
    };
}