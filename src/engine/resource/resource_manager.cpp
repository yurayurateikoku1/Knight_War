#include "resource_manager.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include "texture_manager.h"
#include "audio_manager.h"
#include "font_manager.h"
engine::resource::ResourceManager::ResourceManager(SDL_Renderer *renderer)
{
    texture_manager_ = std::make_unique<TextureManager>(renderer);
    audio_manager_ = std::make_unique<AudioManager>();
    font_manager_ = std::make_unique<FontManager>();

    spdlog::info("ResourceManager init successfully");
}

engine::resource::ResourceManager::~ResourceManager() = default;

MIX_Mixer *engine::resource::ResourceManager::getMixer() const
{
    return audio_manager_->getMixer();
}

void engine::resource::ResourceManager::clear()
{
    texture_manager_->clearTextures();
    audio_manager_->clearSounds();
    audio_manager_->clearMusics();
    font_manager_->clearFonts();
}

SDL_Texture *engine::resource::ResourceManager::loadTexture(const std::string &file_path)
{
    return texture_manager_->loadTexture(file_path);
}

SDL_Texture *engine::resource::ResourceManager::getTexture(const std::string &file_path)
{
    return texture_manager_->getTexture(file_path);
}

void engine::resource::ResourceManager::unloadTexture(const std::string &file_path)
{
    texture_manager_->unloadTexture(file_path);
}

glm::vec2 engine::resource::ResourceManager::getTextureSize(const std::string &file_path)
{
    return texture_manager_->getTextureSize(file_path);
}
void engine::resource::ResourceManager::clearTextures()
{
    texture_manager_->clearTextures();
}

MIX_Audio *engine::resource::ResourceManager::loadSound(const std::string &file_path)
{
    return audio_manager_->loadSound(file_path);
}

MIX_Audio *engine::resource::ResourceManager::getSound(const std::string &file_path)
{
    return audio_manager_->getSound(file_path);
}

void engine::resource::ResourceManager::unloadSound(const std::string &file_path)
{
    audio_manager_->unloadSound(file_path);
}

void engine::resource::ResourceManager::clearSounds()
{
    audio_manager_->clearSounds();
}

MIX_Audio *engine::resource::ResourceManager::loadMusic(const std::string &file_path)
{
    return audio_manager_->loadMusic(file_path);
}

MIX_Audio *engine::resource::ResourceManager::getMusic(const std::string &file_path)
{
    return audio_manager_->getMusic(file_path);
}

void engine::resource::ResourceManager::unloadMusic(const std::string &file_path)
{
    audio_manager_->unloadMusic(file_path);
}

void engine::resource::ResourceManager::clearMusics()
{
    audio_manager_->clearMusics();
}

TTF_Font *engine::resource::ResourceManager::loadFont(const std::string &file_path, int font_size)
{
    return font_manager_->loadFont(file_path, font_size);
}

TTF_Font *engine::resource::ResourceManager::getFont(const std::string &file_path, int font_size)
{
    return font_manager_->getFont(file_path, font_size);
}

void engine::resource::ResourceManager::unloadFont(const std::string &file_path, int font_size)
{
    font_manager_->unloadFont(file_path, font_size);
}

void engine::resource::ResourceManager::clearFonts()
{
    font_manager_->clearFonts();
}