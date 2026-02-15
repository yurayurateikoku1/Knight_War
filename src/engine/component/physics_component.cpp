#include "physics_component.h"
#include "transform_component.h"
#include "../object/game_object.h"
#include <spdlog/spdlog.h>
#include "../physics/physics_engine.h"

engine::component::PhysicsComponent::PhysicsComponent(engine::physics::PhysicsEngine *physics_engine, bool use_gravity, float mass)
    : physics_engine_(physics_engine), use_gravity_(use_gravity), mass_(mass >= 0.0f ? mass : 1.0f)
{
    if (!physics_engine_)
    {
        spdlog::error("Physics engine is null");
    }
    spdlog::info("Physics component created, useGravity={}", use_gravity_);
}

void engine::component::PhysicsComponent::init()
{
    if (!owner_)
    {
        spdlog::error("PhysicsComponent: Owner is not set.");
        return;
    }
    if (!physics_engine_)
    {
        spdlog::error("Physics engine is null");
        return;
    }
    transform_ = owner_->getComponent<engine::component::TransformComponent>();
    if (!transform_)
    {
        spdlog::warn("physics component: game object {} does not have a TransformComponent.", owner_->getName());
        return;
    }
    physics_engine_->registerComponent(this);
    spdlog::info("Physics component initialized");
}

void engine::component::PhysicsComponent::clean()
{
    physics_engine_->unregisterComponent(this);
    spdlog::info("Physics component cleaned");
}
