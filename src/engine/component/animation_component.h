#pragma once
#include "../../engine/utils/math.h"
#include <entt/core/hashed_string.hpp>
#include <entt/entity/entity.hpp>

namespace engine::component
{
    struct AnimationFrame
    {
        engine::utils::Rect src_rect_{}; ///< @brief 帧源矩形
        float duration_ms_{100.0f};      ///< @brief 帧间隔（毫秒）
        AnimationFrame(engine::utils::Rect src_rect, float duration_ms = 100.0f)
            : src_rect_(std::move(src_rect)), duration_ms_(duration_ms) {}
    };

    struct Animation
    {
        std::vector<AnimationFrame> frames_;            ///< @brief 动画帧
        std::unordered_map<int, entt::id_type> events_; ///< @brief 动画事件，键为帧索引，值为事件ID
        float total_duration_ms_{};                     ///< @brief 动画总时长（毫秒）
        bool loop_{true};                               ///< @brief 是否循环

        Animation(std::vector<AnimationFrame> frames,
                  std::unordered_map<int, entt::id_type> events = {},
                  bool loop = true) : frames_(std::move(frames)),
                                      events_(std::move(events)),
                                      loop_(loop)
        {
            // 计算动画总时长 (总时长 = 所有帧时长之和)
            total_duration_ms_ = 0.0f;
            for (const auto &frame : frames_)
            {
                total_duration_ms_ += frame.duration_ms_;
            }
        }
    };

    struct AnimationComponent
    {
        std::unordered_map<entt::id_type, Animation> animations_; ///< @brief 动画集合
        entt::id_type current_animation_id_{entt::null};          ///< @brief 当前播放的动画名称
        size_t current_frame_index_{};                            ///< @brief 当前播放的帧索引
        float current_time_ms_{};                                 ///< @brief 当前播放时间（毫秒）
        float speed_{1.0f};

        AnimationComponent(std::unordered_map<entt::id_type, Animation> animations,
                           entt::id_type current_animation_id,
                           size_t current_frame_index = 0,
                           float current_time_ms = 0.0f,
                           float speed = 1.0f) : animations_(std::move(animations)),
                                                 current_animation_id_(current_animation_id),
                                                 current_frame_index_(current_frame_index),
                                                 current_time_ms_(current_time_ms),
                                                 speed_(speed) {} ///< @brief 播放速度
    };

}