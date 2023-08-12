#pragma once

#include "Rendering/Texture/Texture.h"
#include "Rendering/Framebuffer/Framebuffer.h"

#include "ResourceLibrary/ResourceLibrary.h"

#include "MaterialBlueprint/MaterialBlueprint.h"

#include "ShaderLoader/ShaderLoader.h"

namespace Volund
{
	class Shader
	{
	public:

		virtual void Bind() = 0;

		virtual bool HasUniform(const std::string& name) = 0;

		virtual uint32_t GetId() = 0;

		virtual void SetInt(const std::string& name, int32_t value) = 0;

		virtual void SetFloat(const std::string& name, float value) = 0;

		virtual void SetDouble(const std::string& name, double value) = 0;

		virtual void SetVec2(const std::string& name, const Vec2& value) = 0;

		virtual void SetVec3(const std::string& name, const Vec3& value) = 0;

		virtual void SetVec4(const std::string& name, const Vec4& value) = 0;

		virtual void SetMat3x3(const std::string& name, const Mat3x3& value, bool transpose = false) = 0;

		virtual void SetMat4x4(const std::string& name, const Mat4x4& value, bool transpose = false) = 0;

		virtual void SetTexture(const std::string& name, const Ref<Texture>& value, uint32_t textureUnit) = 0;

		virtual void SetFramebuffer(const std::string& name, const Ref<Framebuffer>& value, uint32_t textureUnit) = 0;

		virtual void Init(const ShaderSource& source, Ref<MaterialBlueprint> materialBlueprint) = 0;

		const Ref<MaterialBlueprint> GetMaterialBlueprint();

		static Ref<Shader> Create();

		static Ref<Shader> Create(const std::string& filepath);

		static Ref<Shader> Create(const ShaderSource& source, Ref<MaterialBlueprint> materialBlueprint);

		virtual ~Shader() = default;

	protected:

		Shader();

		Ref<MaterialBlueprint> m_MaterialBlueprint;
	};
}
