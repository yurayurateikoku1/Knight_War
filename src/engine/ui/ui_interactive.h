#pragma once
#include "ui_element.h"
#include "state/ui_state.h"
#include "../render/sprite.h"
#include <memory>
#include <string>
#include <unordered_map>

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
        std::unordered_map<std::string, std::unique_ptr<engine::render::Sprite>> sprites_;
        std::unordered_map<std::string, std::string> sounds_;
        engine::render::Sprite *current_sprite_ = nullptr;
        bool interactive_ = true;

    public:
        UIInteractive(engine::core::Context &context, glm::vec2 position = {0.0f, 0.0f}, glm::vec2 size = {0.0f, 0.0f});
        ~UIInteractive() override;

        virtual void clicked() {}

        void addSprite(const std::string &name, std::unique_ptr<engine::render::Sprite> sprite); ///< @brief 添加精灵
        void setSprite(const std::string &name);                                                 ///< @brief 设置当前显示的精灵
        void addSound(const std::string &name, const std::string &path);                         ///< @brief 添加音效
        void playSound(const std::string &name);                                                 ///< @brief 播放音效
        // --- Getters and Setters ---
        void setState(std::unique_ptr<engine::ui::state::UIState> state);     ///< @brief 设置当前状态
        engine::ui::state::UIState *getState() const { return state_.get(); } ///< @brief 获取当前状态

        void setInteractive(bool interactive) { interactive_ = interactive; } ///< @brief 设置是否可交互
        bool isInteractive() const { return interactive_; }                   ///< @brief 获取是否可交互
        bool handleInput(engine::core::Context &context) override;
        void render(engine::core::Context &context) override;
    };
}