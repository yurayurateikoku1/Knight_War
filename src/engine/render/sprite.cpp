#include "sprite.h"

engine::render::Sprite::Sprite(const std::string &texture_id, std::optional<SDL_Rect> source_rect, bool is_flipped)
    : texture_id_(texture_id), source_rect_(source_rect), is_flipped_(is_flipped)
{
}