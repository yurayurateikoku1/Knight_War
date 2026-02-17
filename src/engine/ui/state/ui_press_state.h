#pragma once
#include "ui_state.h"

namespace engine::ui::state
{
    class UIPressState final : public UIState
    {
        friend class engine::ui::UIInteractive;

    public:
        UIPressState(engine::ui::UIInteractive *owner);
        ~UIPressState();

    private:
        void enter() override;
        bool onMouseReleased();
    };
}