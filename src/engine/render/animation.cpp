#include "animation.h"
#include <glm/common.hpp>
#include <spdlog/spdlog.h>

engine::render::Animation::Animation(const std::string &name, bool loop)
    : name_(name), loop_(loop)
{
}

void engine::render::Animation::addFrame(const SDL_Rect &source_rect, float duration)
{
    if (duration <= 0.0f)
    {
        spdlog::warn("Animation frame duration must be greater than 0.0f", name_);
        return;
    }
    frames_.push_back({source_rect, duration});
    total_duration_ += duration;
}

const engine::render::AnimationFrame &engine::render::Animation::getFrame(float time) const
{
    if (frames_.empty())
    {
        spdlog::error("Animation is empty: {}", name_);
        return frames_.back();
    }
    float current_time = time;
    if (loop_ && total_duration_ > 0.0f)
    {
        current_time = glm::mod(time, total_duration_);
    }
    else
    {
        if (current_time >= total_duration_)
        {
            return frames_.back();
        }
    }

    float accumulated_time = 0.0f;
    for (const auto &frame : frames_)
    {
        accumulated_time += frame.duration;
        if (current_time < accumulated_time)
        {
            return frame;
        }
    }
    return frames_.back();
}
