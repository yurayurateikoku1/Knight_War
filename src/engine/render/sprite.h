#pragma once
#include <SDL3/SDL_rect.h>
#include <optional>
#include <string>

namespace engine::render
{
    class Sprite
    {
    private:
        /// @brief 纹理ID
        std::string texture_id_;
        /// @brief 源矩形
        std::optional<SDL_Rect> source_rect_;
        /// @brief 是否翻转
        bool is_flipped_ = false;

    public:
        Sprite() = default;
        /// @brief 构造函数
        /// @param texture_id
        /// @param source_rect
        /// @param is_flipped
        Sprite(const std::string &texture_id, std::optional<SDL_Rect> source_rect = std::nullopt, bool is_flipped = false);

        const std::string &getTextureId() const { return texture_id_; }
        const std::optional<SDL_Rect> &getSourceRect() const { return source_rect_; }
        bool isFlipped() const { return is_flipped_; }
        void setTextureId(const std::string &texture_id) { texture_id_ = texture_id; }
        void setSourceRect(const std::optional<SDL_Rect> &source_rect) { source_rect_ = source_rect; }
        void setFlipped(bool is_flipped) { is_flipped_ = is_flipped; }
    };

}