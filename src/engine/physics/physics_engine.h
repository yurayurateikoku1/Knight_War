#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include <optional>
#include "../utils/math.h"
namespace engine::component
{
    class PhysicsComponent;
    class TileLayerComponent;
    enum class TileType;
}
namespace engine::object
{
    class GameObject;
}
namespace engine::physics
{
    class PhysicsEngine
    {
    private:
        std::vector<engine::component::PhysicsComponent *> physics_components_;
        glm::vec2 gravity_ = {0.0f, 980.0f};
        float max_speed_ = 500.0f;
        std::vector<std::pair<engine::object::GameObject *, engine::object::GameObject *>> collision_pairs_;
        std::vector<engine::component::TileLayerComponent *> collision_tile_layers_;
        std::optional<engine::utils::Rect> world_bounds_;

        std::vector<std::pair<engine::object::GameObject *, engine::component::TileType>> tile_tigger_events_;

    public:
        PhysicsEngine() = default;

        PhysicsEngine(const PhysicsEngine &) = delete;
        PhysicsEngine(PhysicsEngine &&) = delete;
        PhysicsEngine &operator=(const PhysicsEngine &) = delete;
        PhysicsEngine &operator=(PhysicsEngine &&) = delete;

        void registerComponent(engine::component::PhysicsComponent *component);
        void unregisterComponent(engine::component::PhysicsComponent *component);

        void registerCollisionTileLayer(engine::component::TileLayerComponent *tile_layer);
        void unregisterCollisionTileLayer(engine::component::TileLayerComponent *tile_layer);

        void update(float dt);
        void checkObjectCollision();

        void resolveTileCollision(engine::component::PhysicsComponent *pc, float dt);

        void resolveSolidObjectCollisions(engine::object::GameObject *move_obj, engine::object::GameObject *solid_obj);

        void setGravity(const glm::vec2 &gravity) { gravity_ = gravity; }
        void setMaxSpeed(float max_speed) { max_speed_ = max_speed; }
        const glm::vec2 &getGravity() const { return gravity_; }
        float getMaxSpeed() const { return max_speed_; }

        const std::vector<std::pair<engine::object::GameObject *, engine::component::TileType>> &getTileTriggerEvents() const { return tile_tigger_events_; }
        void setWorldBounds(const engine::utils::Rect &world_bounds) { world_bounds_ = world_bounds; }
        const std::optional<engine::utils::Rect> &getWorldBounds() const { return world_bounds_; }
        const std::vector<std::pair<engine::object::GameObject *, engine::object::GameObject *>> &getCollisionPairs() const { return collision_pairs_; }
        void applyWorldBounds(engine::component::PhysicsComponent *pc);

        float getTileHeightAtWidth(float width, engine::component::TileType tile_type, glm::vec2 tile_size);
        void checkTileTriggers();
    };

}
