#pragma once

#include "Component.h"
#include "../Vector3.h"

namespace Volund
{
    class VOLUND_API PointLight : public Component
    {
    public:
        RGB color;
        float brightness;
        void Procedure(const Event& e);
        PointLight(const RGB& color = RGB(1.0f), float brightness = 500.0f);
    private:
    };
} //namespace Volund