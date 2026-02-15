#include "game_scene.h"

game::scene::GameScene::GameScene(engine::core::Context &context, engine::scene::SceneManager &scene_manager)
    : Scene("GameScene", context, scene_manager)
{
}

game::scene::GameScene::~GameScene()
{
}
