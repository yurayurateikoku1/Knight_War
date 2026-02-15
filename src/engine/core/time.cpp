#include "time.h"
#include <spdlog/spdlog.h>
#include <SDL3/SDL_timer.h>
engine::core::Time::Time()
{
    last_time_ = SDL_GetTicksNS();
    frame_start_time_ = last_time_;
    spdlog::trace("Time init ...,LastTime:{},FrameStartTime:{}", last_time_, frame_start_time_);
}

void engine::core::Time::update()
{
    frame_start_time_ = SDL_GetTicksNS(); // 记录进入 update 时的时间戳
    auto current_delta_time = static_cast<double>(frame_start_time_ - last_time_) / 1000000000.0f;
    if (target_frame_time_ > 0)
    {
        limitFrameRate(current_delta_time);
    }
    else
    {
        delta_time_ = current_delta_time;
    }
    last_time_ = SDL_GetTicksNS(); // 记录离开 update 时的时间戳
}

void engine::core::Time::limitFrameRate(float current_delta_time)
{
    if (current_delta_time < target_frame_time_)
    {
        double time_to_wait = target_frame_time_ - current_delta_time;
        Uint64 ns_to_wait = static_cast<Uint64>(time_to_wait * 1000000000.0f);
        SDL_DelayNS(ns_to_wait);
        delta_time_ = static_cast<double>(SDL_GetTicksNS() - last_time_) / 1000000000.0f;
    }
}

double engine::core::Time::getDeltaTime() const
{
    return delta_time_ * time_scale_;
}

double engine::core::Time::getUnScaledDeltaTime() const
{
    return delta_time_;
}

void engine::core::Time::setTimeScale(float scale)
{
    if (scale < 0)
    {
        /* code */
        spdlog::warn("Time scale must be greater than 0");
        scale = 0.0f;
    }
    time_scale_ = scale;
}

void engine::core::Time::setTargetFps(int fps)
{
    if (fps < 0)
    {
        spdlog::warn("Target FPS must be greater than 0");
        fps = 0;
    }
    else
    {
        target_fps_ = fps;
    }

    if (target_fps_ > 0)
    {
        target_frame_time_ = 1.0f / static_cast<double>(target_fps_);
        spdlog::info("Target FPS set to {}", target_fps_);
    }
    else
    {
        target_frame_time_ = 0.0f;
        spdlog::info("Target FPS set Unlimited");
    }
}
