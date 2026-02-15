#include "font_manager.h"
#include <spdlog/spdlog.h>
#include <stdexcept>
engine::resource::FontManager::FontManager()
{
    if (!TTF_WasInit() && !TTF_Init())
    {
        /* code */
        throw std::runtime_error("FontManager init failed");
    }
    spdlog::info("FontManager init successfully");
}

engine::resource::FontManager::~FontManager()
{
    if (!fonts_.empty())
    {
        spdlog::info("FontManager not empty, dmynically clear fonts");
        clearFonts();
    }
    TTF_Quit();
    spdlog::info("FontManager quit successfully");
}

TTF_Font *engine::resource::FontManager::loadFont(const std::string &file_path, int font_size)
{
    if (font_size <= 0)
    {
        spdlog::error("Font size must be greater than 0");
        return nullptr;
    }
    FontKey key(file_path, font_size);
    auto it = fonts_.find(key);
    if (it != fonts_.end())
    {
        return it->second.get();
    }
    spdlog::info("Load font: {} - {}", file_path, font_size);
    TTF_Font *raw_font = TTF_OpenFont(file_path.data(), font_size);
    if (!raw_font)
    {
        spdlog::error("Failed to load font: {} - {}", file_path, font_size);
        return nullptr;
    }
    fonts_.emplace(key, std::unique_ptr<TTF_Font, SDLFontDeleter>(raw_font));
    spdlog::info("Load font successfully: {} - {}", file_path, font_size);
    return raw_font;
}

void engine::resource::FontManager::unloadFont(const std::string &file_path, int font_size)
{
    FontKey key(file_path, font_size);
    auto it = fonts_.find(key);
    if (it != fonts_.end())
    {
        spdlog::info("Unload font: {} - {}", file_path, font_size);
        fonts_.erase(it);
        spdlog::info("Unload font successfully: {} - {}", file_path, font_size);
    }
    else
    {
        spdlog::warn("Font not found: {} - {},Unload font failed", file_path, font_size);
    }
}

TTF_Font *engine::resource::FontManager::getFont(const std::string &file_path, int font_size)
{
    FontKey key(file_path, font_size);
    auto it = fonts_.find(key);
    if (it != fonts_.end())
    {
        return it->second.get();
    }
    spdlog::warn("Font not found: {} - {}", file_path, font_size);

    return loadFont(file_path, font_size);
}

void engine::resource::FontManager::clearFonts()
{
    if (!fonts_.empty())
    {
        /* code */
        spdlog::info("Clear {} fonts", fonts_.size());
        fonts_.clear();
    }
}
