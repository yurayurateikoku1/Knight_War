#pragma once
#include "../../engine/component/component.h"

namespace engine::component
{

    class HealthComponent : public Component
    {
        friend class engine::object::GameObject;

    private:
        int max_health_ = 1;
        int current_health_ = 1;
        bool is_invincible_ = false;
        float invincible_duration_ = 0.0f;
        float invincible_timer_ = 0.0f;

    public:
        explicit HealthComponent(int max_health = 1, float invincible_duration = 2.0f);
        ~HealthComponent() override = default;
        HealthComponent(const HealthComponent &) = delete;
        HealthComponent(HealthComponent &&) = delete;
        HealthComponent &operator=(const HealthComponent &) = delete;
        HealthComponent &operator=(HealthComponent &&) = delete;

        bool takeDamage(int damage_amount);
        void heal(int heal_amount);

        bool isAlive() const { return current_health_ > 0; }
        bool isInvincible() const { return is_invincible_; }

        int getMaxHealth() const { return max_health_; }
        int getCurrentHealth() const { return current_health_; }

        void setCurrentHealth(int new_health);
        void setMaxHealth(int new_max_health);
        void setInvincible(float duration);
        void setInvincibleDuration(float duration) { invincible_duration_ = duration; }

    protected:
        void update(float delta_time, engine::core::Context &) override;
    };
} // namespace engine::component
