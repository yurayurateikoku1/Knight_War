#include "ui_interactive.h"
#include "state/ui_state.h"
#include "../core/context.h"
#include "../render/render.h"
#include "../resource/resource_manager.h"
#include "../audio/audio_player.h"
#include <spdlog/spdlog.h>
#include <entt/core/hashed_string.hpp>

using namespace entt::literals;

engine::ui::UIInteractive::UIInteractive(engine::core::Context &context, glm::vec2 position, glm::vec2 size)
    : UIElement(std::move(position), std::move(size)), context_(context)
{
}

engine::ui::UIInteractive::~UIInteractive() = default;

void engine::ui::UIInteractive::addImage(entt::id_type name_id, engine::render::Image image)
{
    // 可交互UI元素必须有一个size用于交互检测，因此如果参数列表中没有指定，则用图片大小作为size
    if (size_.x == 0.0f && size_.y == 0.0f)
    {
        size_ = context_.getResourceManager().getTextureSize(image.getTextureId());
    }
    // 添加图片 (如果name_id已存在，则替换)
    images_.insert_or_assign(name_id, std::move(image));
}

void engine::ui::UIInteractive::setCurrentImage(entt::id_type name_id)
{
    if (images_.find(name_id) != images_.end())
    {
        current_image_id_ = name_id;
    }
    else
    {
        spdlog::warn("Image '{}' not found", name_id);
    }
}

void engine::ui::UIInteractive::setHoverSound(entt::id_type id, const std::string &path)
{
    context_.getResourceManager().loadSound(id, path);
    sounds_.emplace("ui_hover"_hs, id);
}

void engine::ui::UIInteractive::setClickSound(entt::id_type id, const std::string &path)
{
    context_.getResourceManager().loadSound(id, path); // 确保音效资源被加载
    sounds_.emplace("ui_click"_hs, id);
}

void engine::ui::UIInteractive::playSound(entt::id_type name_id)
{
    if (auto it = sounds_.find(name_id); it != sounds_.end())
    {
        if (context_.getAudioPlayer().playSound(it->second) == -1)
        {
            spdlog::warn("Sound '{}' not found or not loaded", name_id);
        }
    }
    else
    {
        if (context_.getAudioPlayer().playSound(name_id) == -1)
        {
            spdlog::error("Sound '{}' not found or not loaded", name_id);
        }
    }
}

void engine::ui::UIInteractive::setState(std::unique_ptr<engine::ui::state::UIState> state)
{
    if (!state)
    {
        spdlog::warn("state is nullptr");
        return;
    }

    state_ = std::move(state);
    state_->enter();
}

void engine::ui::UIInteractive::setNextState(std::unique_ptr<engine::ui::state::UIState> state)
{
    next_state_ = std::move(state);
}

void engine::ui::UIInteractive::update(float delta_time, engine::core::Context &context)
{
    // 先更新子节点
    UIElement::update(delta_time, context);
    if (state_ && interactive_)
    {
        if (next_state_)
        {
            setState(std::move(next_state_));
            next_state_.reset();
        }
        state_->update(delta_time, context);
    }
}

void engine::ui::UIInteractive::render(engine::core::Context &context)
{
    if (!visible_)
        return;

    // 先渲染自身
    context.getRender().drawUIImage(images_[current_image_id_], getScreenPosition(), size_);

    UIElement::render(context);
}
