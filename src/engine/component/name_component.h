#pragma once
#include <string>
#include <entt/entity/entity.hpp>

namespace engine::component
{
    struct NameComponent
    {
        entt::id_type name_id_{entt::null};
        std::string name_;
    };
}