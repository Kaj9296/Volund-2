#include "PCH/PCH.h"
#include "Renderer.h"

#include "Frustum/Frustum.h"

#include "Scene/Component/Components.h"

namespace Volund
{
	void Renderer::Submit(Ref<Scene> scene)
	{
		for (auto& entity : *scene)
		{
			auto componentRegistry = entity.second;

			Mat4x4 modelMatrix = Mat4x4();
			Vec3 position = Vec3();
			if (componentRegistry.Contains<Transform>())
			{
				auto transform = componentRegistry.Get<Transform>();

				modelMatrix = transform->GetModelMatrix();
				position = transform->Position;
			}

			for (int i = 0; i < componentRegistry.Size<MeshRenderer>(); i++)
			{
				auto meshRenderer = componentRegistry.Get<MeshRenderer>(i);

				RendererModel model;
				model.LayerMask = meshRenderer->GetLayerMask();
				model.material = meshRenderer->GetMaterial();
				model.mesh = meshRenderer->GetMesh();
				model.ModelMatrix = modelMatrix;

				this->Submit(model);
			}

			for (int i = 0; i < componentRegistry.Size<Camera>(); i++)
			{
				auto camera = componentRegistry.Get<Camera>(i);

				const auto spec = this->m_Data.Target->GetSpec();

				RendererEye eye;
				eye.LayerMask = camera->GetLayerMask();
				eye.ViewMatrix = camera->GetViewMatrix();
				eye.ProjectionMatrix = camera->GetProjectionMatrix((float)spec.Width / (float)spec.Height);
				eye.Target = nullptr; //TODO: Implement render cameras
				this->Submit(eye);
			}

			for (int i = 0; i < componentRegistry.Size<PointLight>(); i++)
			{
				auto pointLight = componentRegistry.Get<PointLight>(i);

				RendererLight light;
				light.Brightness = pointLight->Brightness;
				light.Color = pointLight->Color;
				light.Position = position;

				this->Submit(light);
			}
		}
	}

	void Renderer::Submit(const RendererModel& model)
	{
		this->m_Data.Models.push_back(model);
	}

	void Renderer::Submit(const RendererLight& light)
	{
		this->m_Data.Lights.push_back(light);
	}

	void Renderer::Submit(const RendererEye& eye)
	{
		this->m_Data.Eyes.push_back(eye);
	}
}
