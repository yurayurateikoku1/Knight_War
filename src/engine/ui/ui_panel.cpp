#include "ui_panel.h"
#include "../core/context.h"
#include "../render/render.h"
#include <SDL3/SDL_rect.h>
#include <spdlog/spdlog.h>
engine::ui::UIPanel::UIPanel(const glm::vec2 &position, const glm::vec2 &size, std::optional<engine::utils::FColor> background_color)
    : UIElement(position, size), background_color_(background_color)
{
    spdlog::info("UIPanel created");
}

void engine::ui::UIPanel::render(engine::core::Context &context)
{
    if (!visible_)
    {
        return;
    }
    if (background_color_)
    {
        context.getRender().drawUIFillRect(getBounds(), background_color_.value());
    }
    UIElement::render(context);
}
