#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <SDL3/SDL_render.h>
#include <glm/vec2.hpp>
#include <variant>
namespace engine::core
{
    class Config;
}

namespace engine::input
{
    enum class ActionState
    {
        INACTIVE,
        PRESSED,
        HELD,
        RELEASED
    };

    class InputManager final
    {
    private:
        /* data */
        SDL_Renderer *sdl_renderer_{nullptr};

        std::unordered_map<std::string, std::vector<std::string>> action2keyname_map_;
        std::unordered_map<std::variant<Uint32, SDL_Scancode>, std::vector<std::string>> input2action_map_;
        std::unordered_map<std::string, ActionState> action_states_{};

        bool should_quit_{false};
        glm::vec2 mouse_position_{0.0f, 0.0f};

    public:
        InputManager(SDL_Renderer *sdl_renderer, const engine::core::Config *config);

        void update();

        /// @brief 动作当前是否触发,持续按压
        /// @param action_name
        /// @return
        bool isActionDown(const std::string &action_name) const;

        /// @brief 动作当前是否在本帧刚刚按下
        /// @param action_name
        /// @return
        bool isActionPressed(const std::string &action_name) const;

        /// @brief 动作当前是否在本帧刚刚释放
        /// @param action_name
        /// @return
        bool isActionReleased(const std::string &action_name) const;

        bool getShouldQuit() const { return should_quit_; }
        void setShouldQuit(bool quit) { should_quit_ = quit; }

        glm::vec2 getMousePosition() const { return mouse_position_; }
        glm::vec2 getLogicalMousePosition() const;

    private:
        /// @brief 处理事件，将按键状态转换为动作状态
        /// @param event
        void processEvent(const SDL_Event &event);
        void initMappings(const engine::core::Config *config);
        void updateActionStates(const std::string &action_name, bool is_input_active, bool is_reapt_event);
        SDL_Scancode scancodeFromString(const std::string &key_name);
        Uint32 mouseButtonFromString(const std::string &button_name);
    };

}
