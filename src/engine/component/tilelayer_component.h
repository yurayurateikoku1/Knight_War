#pragma once
#include "animation_component.h"
#include "sprite_component.h"
#include <entt/entity/entity.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include <utility>
#include <optional>
#include <SDL3/SDL_rect.h>
#include <nlohmann/json.hpp>

namespace engine::component
{
    /// @brief 瓦片类型
    enum class TileType
    {
        /// @brief 空白
        EMPTY,
        /// @brief 普通
        NORMAL,
        /// @brief 静止可碰撞
        SOLID,
        HAZARD
    };

    /// @brief  包含单个瓦片的渲染和逻辑信息
    struct TileInfo
    {
        engine::component::Sprite sprite_;                      ///< @brief 精灵
        engine::component::TileType type_;                      ///< @brief 类型
        std::optional<engine::component::Animation> animation_; ///< @brief 动画（支持Tiled动画图块）
        std::optional<nlohmann::json> properties_;              ///< @brief 属性（存放自定义属性，方便LevelLoader解析）

        TileInfo() = default;

        TileInfo(engine::component::Sprite sprite,
                 engine::component::TileType type,
                 std::optional<engine::component::Animation> animation = std::nullopt,
                 std::optional<nlohmann::json> properties = std::nullopt) : sprite_(std::move(sprite)),
                                                                            type_(type),
                                                                            animation_(std::move(animation)),
                                                                            properties_(std::move(properties)) {}
    };
    struct TileLayerComponent
    {
        glm::ivec2 tile_size_;            ///< @brief 瓦片大小
        glm::ivec2 map_size_;             ///< @brief 地图大小
        std::vector<entt::entity> tiles_; ///< @brief 瓦片实体列表，每个瓦片对应一个实体，按顺序排列

        TileLayerComponent(glm::ivec2 tile_size,
                           glm::ivec2 map_size,
                           std::vector<entt::entity> tiles) : tile_size_(std::move(tile_size)),
                                                              map_size_(std::move(map_size)),
                                                              tiles_(std::move(tiles)) {}
    };
}