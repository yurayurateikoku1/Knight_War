#include "engine/core/game_app.h"
#include "engine/scene/scene_manager.h"
#include "game/scene/game_scene.h"
#include <spdlog/spdlog.h>
#include <SDL3/SDL_main.h>

void setupInitialScene(engine::scene::SceneManager &scene_manager)
{
    auto game_scene = std::make_unique<game::scene::GameScene>(scene_manager.getContext(), scene_manager);
    scene_manager.requestPushScene(std::move(game_scene));
}

int main(int, char *[])
{
    engine::core::GameApp app;

    app.registerSceneSutep(setupInitialScene);
    app.run();
    return 0;
}
