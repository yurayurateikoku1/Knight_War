#pragma once
#include <memory>
#include <vector>
#include <glm/vec2.hpp>

namespace engine::core
{
    class Context;
}

namespace engine::ui
{
    class UIElement;
    class UIPanel;
}

namespace engine::ui
{
    class UIManager final
    {
    private:
        std::unique_ptr<engine::ui::UIPanel> root_element_;

    public:
        UIManager();
        ~UIManager();
        UIManager(const UIManager &) = delete;
        UIManager(UIManager &&) = delete;
        UIManager &operator=(const UIManager &) = delete;
        UIManager &operator=(UIManager &&) = delete;

        [[nodiscard]] bool init(const glm::vec2 &window_size);
        void addElement(std::unique_ptr<engine::ui::UIElement> element);
        UIPanel *getRootElement() const;
        void clearElements();

        // --- 核心循环方法 ---
        void update(float delta_time, engine::core::Context &); ///< @brief 更新UI元素。
        void render(engine::core::Context &context);
    };
}