#pragma once
#include <entt/entity/fwd.hpp>
#include <unordered_map>

namespace engine::component
{
    struct AudioComponent
    {
        std::unordered_map<entt::id_type, entt::id_type> sounds_;
    };

}