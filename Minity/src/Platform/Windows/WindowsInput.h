#pragma once
#include "pch.h"
#include "Minity/Input.h"


namespace Minity {

    class WindowsInput : public Input {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;
        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
        virtual float GetMouseScrollXImpl() override;
        virtual float GetMouseScrollYImpl() override;

    public:
        WindowsInput(){};
    };

}  // namespace Minity