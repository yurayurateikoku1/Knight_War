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

bool engine::ui::UIElement::handleInput(engine::core::Context &context)
{
    if (!visible_)
    {
        return false;
    }

    for (auto it = children_.begin(); it != children_.end();)
    {
        if (*it && !(*it)->isNeedRemove())
        {
            if ((*it)->handleInput(context))
            {
                return true;
            }
            ++it;
        }
        else
        {
            it = children_.erase(it);
        }
    }
    return false;
}

void engine::ui::UIElement::addChild(std::unique_ptr<UIElement> child)
{
    if (child)
    {
        child->setParent(this);
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

void engine::ui::UIElement::removeAllChildren()
{
    for (auto &child : children_)
    {
        child->setParent(nullptr);
    }
    children_.clear();
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
