#pragma once

#include "Component.hpp"

#include "../Rendering/Material.hpp"
#include "../Rendering/Mesh.hpp"

namespace Volund
{
    class VOLUND_API MeshRenderer : public Component
    {
    public:
        bool IsValid();
        void SetLayer(uint8_t layer);
        uint32_t GetLayerMask();
        void SetMesh(std::shared_ptr<Mesh> newMesh);
        void SetMaterial(std::shared_ptr<Material> newMaterial);
        std::shared_ptr<Mesh> GetMesh();
        std::shared_ptr<Material> GetMaterial();
        void Procedure(const Event& e);
        MeshRenderer(std::shared_ptr<Mesh> mesh = nullptr, std::shared_ptr<Material> material = nullptr);
    private:
        uint32_t m_layerMask = 1;
        std::shared_ptr<Mesh> m_mesh;
        std::shared_ptr<Material> m_material;
    };
}