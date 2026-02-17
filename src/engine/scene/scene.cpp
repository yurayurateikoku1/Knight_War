#include "scene.h"
#include <spdlog/spdlog.h>
#include "scene_manager.h"
#include "../core/context.h"
#include "../ui/ui_manager.h"
#include "../utils/events.h"
#include <entt/signal/dispatcher.hpp>
engine::scene::Scene::Scene(const std::string &scene_name, engine::core::Context &context)
    : scene_name_(scene_name), context_(context), is_initialized_(false), ui_manager_(std::make_unique<engine::ui::UIManager>())
{
    spdlog::info("Scene {} created", scene_name_);
}

engine::scene::Scene::~Scene() = default;

void engine::scene::Scene::init()
{
    is_initialized_ = true;
    spdlog::info("Scene {} initialized", scene_name_);
}

void engine::scene::Scene::update(float dt)
{
    if (!is_initialized_)
    {
        return;
    }
    ui_manager_->update(dt, context_);
}

void engine::scene::Scene::render()
{
    if (!is_initialized_)
    {
        /* code */
        return;
    }
    ui_manager_->render(context_);
}

void engine::scene::Scene::clean()
{
    if (!is_initialized_)
    {
        /* code */
        return;
    }
    registry_.clear();
    is_initialized_ = false;
    spdlog::info("Scene {} cleaned", scene_name_);
}

void engine::scene::Scene::requestPopScene()
{
    context_.getDispatcher().trigger<engine::utils::PopSceneEvent>();
}

void engine::scene::Scene::requestPushScene(std::unique_ptr<engine::scene::Scene> &&scene)
{
    context_.getDispatcher().trigger<engine::utils::PushSceneEvent>(engine::utils::PushSceneEvent{std::move(scene)});
}

void engine::scene::Scene::requestReplaceScene(std::unique_ptr<engine::scene::Scene> &&scene)
{
    context_.getDispatcher().trigger<engine::utils::ReplaceSceneEvent>(engine::utils::ReplaceSceneEvent{std::move(scene)});
}

void engine::scene::Scene::requestQuit()
{
    context_.getDispatcher().trigger<engine::utils::QuitEvent>();
}
