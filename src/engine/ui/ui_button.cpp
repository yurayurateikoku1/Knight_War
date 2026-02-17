#include "ui_button.h"
#include "state/ui_normal_state.h"
#include <spdlog/spdlog.h>
#include <entt/core/hashed_string.hpp>
using namespace entt::literals;

engine::ui::UIButton::UIButton(engine::core::Context &context, engine::render::Image normal_image, engine::render::Image hover_image, engine::render::Image pressed_image, const glm::vec2 &position, const glm::vec2 &size, std::function<void()> click_callback, std::function<void()> hover_enter_callback, std::function<void()> hover_leave_callback)
    : UIInteractive(context, std::move(position), std::move(size)), click_callback_(std::move(click_callback)), hover_enter_callback_(std::move(hover_enter_callback)), hover_leave_callback_(std::move(hover_leave_callback))
{
    addImage("normal"_hs, std::move(normal_image));
    addImage("hover"_hs, std::move(hover_image));
    addImage("pressed"_hs, std::move(pressed_image));

    setState(std::make_unique<engine::ui::state::UINormalState>(this));

    spdlog::info("UIButton created");
}
