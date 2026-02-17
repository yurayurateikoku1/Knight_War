#include "ui_element.h"
#include "../core/context.h"
#include <algorithm>
#include <spdlog/spdlog.h>
#include <utility>

engine::ui::UIElement::UIElement(const glm::vec2 &position, const glm::vec2 &size)
    : position_(position), size_(size)
{
}

void engine::ui::UIElement::update(float dt, engine::core::Context &context)
{
    if (!visible_)
    {
        return;
    }
    for (auto it = children_.begin(); it != children_.end();)
    {
        if (*it && !(*it)->isNeedRemove())
        {
            (*it)->update(dt, context);
            ++it;
        }
        else
        {
            it = children_.erase(it);
        }
    }
}

void engine::ui::UIElement::render(engine::core::Context &context)
{
    if (!visible_)
    {
        return;
    }
    for (const auto &child : children_)
    {
        if (child)
        {
            child->render(context);
        }
    }
}

void engine::ui::UIElement::addChild(std::unique_ptr<UIElement> child, int order_index)
{
    if (child)
    {
        child->setParent(this); // 设置父指针
        if (order_index >= 0)
        {
            child->setOrderIndex(order_index);
        }
        children_.push_back(std::move(child));
    }
}

std::unique_ptr<engine::ui::UIElement> engine::ui::UIElement::removeChild(UIElement *child_ptr)
{
    auto it = std::find_if(children_.begin(), children_.end(), [child_ptr](const std::unique_ptr<UIElement> &child)
                           { return child.get() == child_ptr; });
    if (it != children_.end())
    {
        std::unique_ptr<UIElement> remove_child = std::move(*it);
        children_.erase(it);
        remove_child->setParent(nullptr);
        return remove_child;
    }
    return nullptr;
}

std::unique_ptr<engine::ui::UIElement> engine::ui::UIElement::removeChildById(entt::id_type id)
{
    auto it = std::find_if(children_.begin(), children_.end(),
                           [id](const std::unique_ptr<UIElement> &p)
                           {
                               return p->getId() == id;
                           });
    if (it != children_.end())
    {
        std::unique_ptr<UIElement> removed_child = std::move(*it);
        children_.erase(it);
        removed_child->setParent(nullptr); // 清除父指针
        return removed_child;              // 返回被移除的子元素（可以挂载到别处）
    }
    return nullptr; // 未找到子元素
}

void engine::ui::UIElement::removeAllChildren()
{
    for (auto &child : children_)
    {
        child->setParent(nullptr);
    }
    children_.clear();
}

engine::ui::UIElement *engine::ui::UIElement::getChildById(entt::id_type id) const
{
    auto it = std::find_if(children_.begin(), children_.end(),
                           [id](const std::unique_ptr<UIElement> &p)
                           {
                               return p->getId() == id;
                           });
    if (it != children_.end())
    {
        return it->get();
    }
    return nullptr; // 未找到子元素
}

void engine::ui::UIElement::sortChildrenByOrderIndex()
{
    std::stable_sort(children_.begin(), children_.end(), [](const std::unique_ptr<UIElement> &a, const std::unique_ptr<UIElement> &b)
                     { return a->getOrderIndex() < b->getOrderIndex(); });
}

engine::utils::Rect engine::ui::UIElement::getBounds() const
{
    auto abs_pos = getScreenPosition();
    return engine::utils::Rect(abs_pos, size_);
}

glm::vec2 engine::ui::UIElement::getScreenPosition() const
{
    if (parent_)
    {
        return parent_->getScreenPosition() + position_;
    }
    return position_;
}

bool engine::ui::UIElement::isPointInside(const glm::vec2 &point) const
{
    auto bounds = getBounds();
    return (point.x >= bounds.position.x && point.x < (bounds.position.x + bounds.size.x) &&
            point.y >= bounds.position.y &&
            point.y < (bounds.position.y + bounds.size.y));
}
