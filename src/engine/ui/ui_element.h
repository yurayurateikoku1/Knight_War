#pragma once
#include <SDL3/SDL_rect.h>
#include <memory>
#include <vector>
#include "../utils/math.h"
#include <entt/entity/entity.hpp>
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
        int order_index_ = 0;           ///< @brief 一个用于排序的索引
        entt::id_type id_ = entt::null; ///< @brief 可用于标记或查找的ID

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

        /// @brief 添加子元素, 可指定子元素的排序键(默认为-1，不设置排序键)
        void addChild(std::unique_ptr<UIElement> child, int order_index = -1);
        std::unique_ptr<UIElement> removeChild(UIElement *child_ptr);
        std::unique_ptr<UIElement> removeChildById(entt::id_type id); ///< @brief 根据ID移除子元素，并返回其智能指针
        void removeAllChildren();

        const glm::vec2 &getPosition() const { return position_; }
        const glm::vec2 &getSize() const { return size_; }
        bool isVisible() const { return visible_; }
        bool isNeedRemove() const { return need_remove_; }
        int getOrderIndex() const { return order_index_; } ///< @brief 获取元素的排序索引
        UIElement *getParent() const { return parent_; }
        const std::vector<std::unique_ptr<UIElement>> &getChildren() const { return children_; }
        UIElement *getChildById(entt::id_type id) const; ///< @brief 根据ID获取子元素
        entt::id_type getId() const { return id_; }      ///< @brief 获取自身的ID

        void setSize(const glm::vec2 &size) { size_ = size; }
        void setVisible(bool visible) { visible_ = visible; }
        void setParent(UIElement *parent) { parent_ = parent; }
        void setPosition(const glm::vec2 &position) { position_ = position; }
        void setNeedRemove(bool need_remove) { need_remove_ = need_remove; }
        void setOrderIndex(int order_index) { order_index_ = order_index; } ///< @brief 设置元素的排序索引
        void setId(entt::id_type id) { id_ = id; }                          ///< @brief 设置元素的ID

        void sortChildrenByOrderIndex(); ///< @brief 根据order_index_排序子元素
        engine::utils::Rect getBounds() const;
        glm::vec2 getScreenPosition() const;
        bool isPointInside(const glm::vec2 &point) const;
    };
}
