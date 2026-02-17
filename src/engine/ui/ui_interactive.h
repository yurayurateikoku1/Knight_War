#pragma once
#include "ui_element.h"
#include "state/ui_state.h"
#include "../render/image.h"
#include <unordered_map>
#include <memory>
#include <entt/entity/fwd.hpp>
namespace engine::core
{
    class Context;
}

namespace engine::ui
{
    class UIInteractive : public UIElement
    {
    protected:
        engine::core::Context &context_;
        std::unique_ptr<engine::ui::state::UIState> state_;
        std::unique_ptr<engine::ui::state::UIState> next_state_;          ///< @brief 下一个状态，用于处理状态切换
        std::unordered_map<entt::id_type, engine::render::Image> images_; ///< @brief 图片集合
        std::unordered_map<entt::id_type, entt::id_type> sounds_;
        entt::id_type current_image_id_ = entt::null; ///< @brief 当前显示的图片ID
        bool interactive_ = true;

    public:
        UIInteractive(engine::core::Context &context, glm::vec2 position = {0.0f, 0.0f}, glm::vec2 size = {0.0f, 0.0f});
        ~UIInteractive() override;

        virtual void clicked() {}
        virtual void hover_enter() {} ///< @brief 如果有悬停进入事件，则重写该方法
        virtual void hover_leave() {} ///< @brief 如果有悬停离开事件，则重写该方法

        void addImage(entt::id_type name_id, engine::render::Image image); ///< @brief 添加/替换图片
        void setCurrentImage(entt::id_type name_id);                       ///< @brief 设置当前显示的图片

        void setHoverSound(entt::id_type id, const std::string &path = ""); ///< @brief 设置悬浮音效
        void setClickSound(entt::id_type id, const std::string &path = ""); ///< @brief 设置点击音效
        void playSound(entt::id_type name_id);                              ///< @brief 播放音效
                                                                            // --- Getters and Setters ---
        engine::core::Context &getContext() const { return context_; }
        void setState(std::unique_ptr<engine::ui::state::UIState> state);     ///< @brief 设置当前状态
        void setNextState(std::unique_ptr<engine::ui::state::UIState> state); ///< @brief 设置下一个状态
        engine::ui::state::UIState *getState() const { return state_.get(); } ///< @brief 获取当前状态

        void setInteractive(bool interactive) { interactive_ = interactive; } ///< @brief 设置是否可交互
        bool isInteractive() const { return interactive_; }                   ///< @brief 获取是否可交互
        void update(float delta_time, engine::core::Context &context) override;
        void render(engine::core::Context &context) override;
    };
}