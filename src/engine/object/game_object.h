#pragma once
#include "../component/component.h"
#include <unordered_map>
#include <typeindex>
#include <utility>
#include <spdlog/spdlog.h>

namespace engine::core
{
    class Context;
}
namespace engine::object
{
    class GameObject
    {
    private:
        std::string name_;
        std::string target_;
        std::unordered_map<std::type_index, std::unique_ptr<engine::component::Component>> components_;
        /// @brief 延迟删除的标记
        bool need_remove_{false};

    public:
        GameObject(const std::string &name = "", const std::string &tag = "");
        GameObject(const GameObject &) = delete;
        GameObject &operator=(const GameObject &) = delete;
        GameObject(GameObject &&) = delete;
        GameObject &operator=(GameObject &&) = delete;

        void setName(const std::string &name) { name_ = name; }
        const std::string &getName() const { return name_; }
        void setTarget(const std::string &target) { target_ = target; }
        const std::string &getTarget() const { return target_; }
        void setNeedRemove(bool need_remove) { need_remove_ = need_remove; }
        bool getNeedRemove() const { return need_remove_; }

        template <typename T, typename... Args>
        T *addComponent(Args &&...args)
        {
            static_assert(std::is_base_of<engine::component::Component, T>::value, "Component must be derived from engine::component::Component");
            auto type_index = std::type_index(typeid(T));

            if (hasComponent<T>())
            {
                return getComponent<T>();
            }

            auto new_component = std::make_unique<T>(std::forward<Args>(args)...);
            T *ptr = new_component.get();
            new_component->setOwner(this);
            components_[type_index] = std::move(new_component);
            ptr->init();
            spdlog::info("Component {} added to GameObject {}", typeid(T).name(), name_);
            return ptr;
        }

        template <typename T>
        T *getComponent() const
        {
            static_assert(std::is_base_of<engine::component::Component, T>::value, "Component must be derived from engine::component::Component");
            auto type_index = std::type_index(typeid(T));
            if (auto it = components_.find(type_index); it != components_.end())
            {
                /* code */
                return static_cast<T *>(it->second.get());
            }
            return nullptr;
        }

        template <typename T>
        bool hasComponent() const
        {
            static_assert(std::is_base_of<engine::component::Component, T>::value, "Component must be derived from engine::component::Component");
            return components_.contains(std::type_index(typeid(T)));
        }

        template <typename T>
        void removeComponent()
        {
            static_assert(std::is_base_of<engine::component::Component, T>::value, "Component must be derived from engine::component::Component");
            auto type_index = std::type_index(typeid(T));
            for (auto it = components_.find(type_index); it != components_.end();)
            {
                /* code */
                it->second->clean();
                components_.erase(it);
            }
        }

        void update(float dt, engine::core::Context &);
        void render(engine::core::Context &);
        void clean();
        void handleInput(engine::core::Context &);
    };

}