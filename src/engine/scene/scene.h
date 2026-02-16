#pragma once
#include <vector>
#include <memory>
#include <string>
#include <entt/entity/registry.hpp>
namespace engine::core
{
    class Context;
}

namespace engine::render
{
    class Renderer;
}

namespace engine::ui
{
    class UIManager;
}
namespace engine::input
{
    class InputManager;
}

namespace engine::scene
{
    class SceneManager;
    /// @brief 场景基类,复制场景中的游戏对象和场景的生命周期
    class Scene
    {
    protected:
        std::string scene_name_;
        engine::core::Context &context_;
        std::unique_ptr<engine::ui::UIManager> ui_manager_;
        entt::registry registry_;
        bool is_initialized_{false};

    public:
        /// @brief
        /// @param scene_name 场景名称
        /// @param context 上下文
        /// @param scene_manager 场景的管理器
        Scene(const std::string &scene_name, engine::core::Context &context);
        virtual ~Scene();
        Scene(const Scene &) = delete;
        Scene(Scene &&) = delete;
        Scene &operator=(const Scene &) = delete;
        Scene &operator=(Scene &&) = delete;

        virtual void init();
        virtual void update(float dt);
        virtual void render();
        virtual void handleInput();
        virtual void clean();

        /// @brief 请求弹出场景
        void requestPopScene();
        /// @brief 请求推入场景
        /// @param scene
        void requestPushScene(std::unique_ptr<engine::scene::Scene> &&scene);
        /// @brief 请求替换场景
        /// @param scene
        void requestReplaceScene(std::unique_ptr<engine::scene::Scene> &&scene);
        /// @brief 请求退出
        void requestQuit();

        void setName(const std::string &name) { scene_name_ = name; }
        std::string getName() const { return scene_name_; }
        void setInitialized(bool initialized) { is_initialized_ = initialized; }
        bool getInitialized() const { return is_initialized_; }

        entt::registry &getRegistry() { return registry_; }
        engine::core::Context &getContext() const { return context_; }

    protected:
        /// @brief 待处理的添加，每轮更新的最后调用
        void processPendingAdditions();
    };
}