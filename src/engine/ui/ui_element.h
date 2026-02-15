#pragma once
#include <SDL3/SDL_rect.h>
#include <memory>
#include <vector>
#include "../utils/math.h"

namespace engine::core
{
    class Context;
} // namespace

namespace engine::ui
{
    class UIElement
    {
    protected:
        glm::vec2 position_;
        glm::vec2 size_;
        bool visible_ = true;
        bool need_remove_ = false;
        UIElement *parent_ = nullptr;
        std::vector<std::unique_ptr<UIElement>> children_;

    public:
        explicit UIElement(const glm::vec2 &position = {0.0f, 0.0f}, const glm::vec2 &size = {0.0f, 0.0f});
        virtual ~UIElement() = default;
        UIElement(const UIElement &) = delete;
        UIElement(UIElement &&) = delete;
        UIElement &operator=(const UIElement &) = delete;
        UIElement &operator=(UIElement &&) = delete;

        virtual void update(float dt, engine::core::Context &context);
        virtual void render(engine::core::Context &context);
        virtual bool handleInput(engine::core::Context &context);

        void addChild(std::unique_ptr<UIElement> child);
        std::unique_ptr<UIElement> removeChild(UIElement *child_ptr);
        void removeAllChildren();

        const glm::vec2 &getPosition() const { return position_; }
        const glm::vec2 &getSize() const { return size_; }
        bool isVisible() const { return visible_; }
        bool isNeedRemove() const { return need_remove_; }
        UIElement *getParent() const { return parent_; }
        const std::vector<std::unique_ptr<UIElement>> &getChildren() const { return children_; }

        void setSize(const glm::vec2 &size) { size_ = size; }
        void setVisible(bool visible) { visible_ = visible; }
        void setParent(UIElement *parent) { parent_ = parent; }
        void setPosition(const glm::vec2 &position) { position_ = position; }
        void setNeedRemove(bool need_remove) { need_remove_ = need_remove; }

        engine::utils::Rect getBounds() const;
        glm::vec2 getScreenPosition() const;
        bool isPointInside(const glm::vec2 &point) const;
    };
}
