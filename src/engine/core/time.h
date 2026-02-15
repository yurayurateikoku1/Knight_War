#pragma once
#include <SDL3/SDL_stdinc.h>

namespace engine::core
{

    class Time final
    {
    private:
        /// @brief 上一帧的时间
        Uint64 last_time_{0};
        /// @brief 当前帧开始的时间戳
        Uint64 frame_start_time_{0};
        /// @brief 帧的时间差
        double delta_time_{0.0f};
        /// @brief 时间缩放因子
        double time_scale_{1.0f};

        /// @brief 目标帧率
        int target_fps_{0};
        /// @brief 目标帧时间
        double target_frame_time_{0.0f};

    public:
        Time();
        Time(const Time &) = delete;
        Time(Time &&) = delete;
        Time &operator=(const Time &) = delete;
        Time &operator=(Time &&) = delete;
        /// @brief 每帧开始调用 更新内部时间并计算状态
        void update();

        double getDeltaTime() const;
        double getUnScaledDeltaTime() const;
        float getTimeScale() const { return time_scale_; }
        void setTimeScale(float scale);
        int getTargetFps() const { return target_fps_; }
        void setTargetFps(int fps);

    private:
        /// @brief 限制帧率
        /// @param current_delta_time 当前帧执行时间
        void limitFrameRate(float current_delta_time);
    };
}