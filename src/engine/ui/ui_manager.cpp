#include "ui_manager.h"
#include "ui_panel.h"
#include "ui_element.h"
#include <spdlog/spdlog.h>
engine::ui::UIManager::UIManager()
{
    root_element_ = std::make_unique<UIPanel>(glm::vec2{0.0f, 0.0f}, glm::vec2{0.0f, 0.0f});
    spdlog::info("UIManager created");
}

engine::ui::UIManager::~UIManager() = default;

bool engine::ui::UIManager::init(const glm::vec2 &window_size)
{
    root_element_->setSize(window_size);
    spdlog::info("UIManager initialized");
    return true;
}

void engine::ui::UIManager::addElement(std::unique_ptr<engine::ui::UIElement> element)
{
    if (root_element_)
    {
        root_element_->addChild(std::move(element));
    }
    else
    {
        spdlog::error("UIManager is not initialized");
    }
}

engine::ui::UIPanel *engine::ui::UIManager::getRootElement() const
{
    return root_element_.get();
}

void engine::ui::UIManager::clearElements()
{
    if (root_element_)
    {
        root_element_->removeAllChildren();
    }
}

bool engine::ui::UIManager::handleInput(engine::core::Context &context)
{
    if (root_element_ && root_element_->isVisible())
    {
        if (root_element_->handleInput(context))
        {
            return true;
        }
    }
    return false;
}

void engine::ui::UIManager::update(float dt, engine::core::Context &context)
{
    if (root_element_ && root_element_->isVisible())
    {
        root_element_->update(dt, context);
    }
}

void engine::ui::UIManager::render(engine::core::Context &context)
{
    if (root_element_ && root_element_->isVisible())
    {
        /* code */
        root_element_->render(context);
    }
}
