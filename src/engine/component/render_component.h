#pragma once
#include "../utils/math.h"
namespace engine::component
{
    /// @brief 渲染组件,用于确定渲染顺序
    struct RenderComponent
    {
        static constexpr int MAIN_LAYER{10}; ///< @brief 主图层ID，默认为10
        int layer_{};
        float depth_{};
        engine::utils::FColor color_{engine::utils::FColor::white()}; ///< @brief 颜色调整参数
        RenderComponent(int layer = MAIN_LAYER, float depth = 0, engine::utils::FColor color = engine::utils::FColor::white())
            : layer_(layer), depth_(depth), color_(color) {}
        bool operator<(const RenderComponent &other) const
        {
            if (layer_ == other.layer_)
            {
                return depth_ < other.depth_;
            }
            return layer_ < other.layer_;
        }
    };

}