#pragma once

#include "Mesh.hpp"
#include "Framebuffer.hpp"

#include "../Math.hpp"

namespace Volund
{
    enum class GraphicsAPI
    {
        None,
        OpenGL
    };

    class VOLUND_API RenderingAPIInstance
    {
    public:
        virtual IVec2 GetViewSize() = 0;
        virtual void Clear(const RGBA color) = 0;
        virtual void SetViewPort(int32_t x, int32_t y, int32_t width, int32_t height) = 0;
        virtual void DrawIndexed(uint64_t indexCount) = 0;
        virtual void Draw(uint64_t first, uint64_t count) = 0;
        virtual void BlitFramebuffer(std::shared_ptr<Framebuffer> readBuffer, std::shared_ptr<Framebuffer> drawBuffer) = 0;
        virtual ~RenderingAPIInstance() = default;
    };

    class VOLUND_API RenderingAPI
    {
    public:
        static IVec2 GetViewSize();
        static void Clear(const RGBA color = RGBA(0.0f, 0.0f, 0.0f, 1.0f));
        static void SetViewPort(int32_t x, int32_t y, int32_t width, int32_t height);
        static void DrawIndexed(uint64_t indexCount);
        static void Draw(uint64_t first, uint64_t count);
        static void BlitFramebuffer(std::shared_ptr<Framebuffer> readBuffer, std::shared_ptr<Framebuffer> drawBuffer);
        static void Init(GraphicsAPI api);
        static GraphicsAPI GetSelectedAPI();
    private:
        RenderingAPI() = delete;
        static inline std::shared_ptr<RenderingAPIInstance> m_instance;
        static inline GraphicsAPI m_selectedAPI;
    };
}