#include "texture_manager.h"
#include <SDL3_image/SDL_image.h>
#include <spdlog/spdlog.h>
#include <stdexcept>

engine::resource::TextureManager::TextureManager(SDL_Renderer *renderer)
    : renderer_(renderer)
{
    if (!renderer_)
    {
        throw std::runtime_error("TextureManager init failed");
    }
    spdlog::info("TextureManager init successfully");
}

SDL_Texture *engine::resource::TextureManager::loadTexture(const std::string &file_path)
{
    auto it = textures_.find(file_path);
    if (it != textures_.end())
    {
        return it->second.get();
    }
    SDL_Texture *raw_texture = IMG_LoadTexture(renderer_, file_path.c_str());

    if (!SDL_SetTextureScaleMode(raw_texture, SDL_SCALEMODE_NEAREST))
    {
        /* code */
        spdlog::warn("Set texture scale mode failed: {}", file_path);
    }

    if (!raw_texture)
    {
        spdlog::error("Load texture failed: {} , SDL error: {}", file_path, SDL_GetError());
        return nullptr;
    }

    textures_.emplace(file_path, std::unique_ptr<SDL_Texture, SDLTextureDeleter>(raw_texture));
    spdlog::info("Load texture successfully: {}", file_path);

    return raw_texture;
}

SDL_Texture *engine::resource::TextureManager::getTexture(const std::string &file_path)
{
    auto it = textures_.find(file_path);
    if (it != textures_.end())
    {
        return it->second.get();
    }
    spdlog::warn("Texture not found: {}", file_path);
    return loadTexture(file_path);
}

glm::vec2 engine::resource::TextureManager::getTextureSize(const std::string &file_path)
{
    SDL_Texture *texture = getTexture(file_path);
    if (!texture)
    {
        spdlog::error("Texture not found: {}", file_path);
        return glm::vec2(0.0f, 0.0f);
    }

    glm::vec2 size;
    if (!SDL_GetTextureSize(texture, &size.x, &size.y))
    {
        spdlog::error("Get texture size failed: {}", file_path);
        return glm::vec2(0.0f, 0.0f);
    }
    return size;
}

void engine::resource::TextureManager::unloadTexture(const std::string &file_path)
{
    auto it = textures_.find(file_path);
    if (it != textures_.end())
    {
        spdlog::info("Unload texture: {}", file_path);
        textures_.erase(it);
    }
    else
    {
        spdlog::warn("Texture not found: {}", file_path);
    }
}

void engine::resource::TextureManager::clearTextures()
{
    if (!textures_.empty())
    {
        /* code */
        spdlog::info("Clear {} textures", textures_.size());
        textures_.clear();
    }
}
