#include "camera.h"
#include <spdlog/spdlog.h>
engine::render::Camera::Camera(const glm::vec2 &viewport_size, const glm::vec2 &position, const std::optional<engine::utils::Rect> &limit_bounds)
    : viewport_size_(viewport_size), position_(position), limit_bounds_(limit_bounds)
{
    spdlog::info("Camera created{},{}", position_.x, position_.y);
}

void engine::render::Camera::setPosition(const glm::vec2 &position)
{
    position_ = position;
    clampPosition();
}

void engine::render::Camera::setLimitBounds(const std::optional<engine::utils::Rect> &limit_bounds)
{
    limit_bounds_ = limit_bounds;
    clampPosition();
}

void engine::render::Camera::clampPosition()
{
    if (limit_bounds_.has_value() && limit_bounds_->size.x > 0 && limit_bounds_->size.y > 0)
    {
        /* code */
        glm::vec2 min_camera_position = limit_bounds_->position;
        glm::vec2 max_camera_position = limit_bounds_->position + limit_bounds_->size - viewport_size_;

        max_camera_position.x = std::max(min_camera_position.x, max_camera_position.x);
        max_camera_position.y = std::max(min_camera_position.y, max_camera_position.y);
        position_ = glm::clamp(position_, min_camera_position, max_camera_position);
    }
}

void engine::render::Camera::move(const glm::vec2 &offset)
{
    position_ += offset;
    clampPosition();
}

glm::vec2 engine::render::Camera::world2Screen(const glm::vec2 &world_position) const
{
    // 世界坐标减去相机位置，得到屏幕坐标
    return world_position - position_;
}

glm::vec2 engine::render::Camera::world2ScreenWithParallax(const glm::vec2 &world_position, const glm::vec2 &scroll_factor) const
{
    //
    return world_position - position_ * scroll_factor;
}

glm::vec2 engine::render::Camera::screen2World(const glm::vec2 &screen_position) const
{
    // 屏幕坐标加上相机位置，得到世界坐标
    return screen_position + position_;
}
