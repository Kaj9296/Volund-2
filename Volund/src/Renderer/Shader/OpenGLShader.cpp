#pragma once

#include "PCH/PCH.h"
#include "OpenGLShader.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	void OpenGLShader::Init(std::string const& FilePath)
	{
		if (this->ID != NULL)
		{
			VOLUND_INFO("Shader (%s) already initialized.", FilePath.c_str());
			return;
		}
		VOLUND_INFO("Loading Shader (%s)...", FilePath.c_str());

		Source Source = this->ParseShader(FilePath);

		uint32_t program = glCreateProgram();

		uint32_t vs = NULL;
		if (Source.VertexSource.length() > 1)
		{
			vs = CompileShader(GL_VERTEX_SHADER, Source.VertexSource);
			glAttachShader(program, vs);
		}

		uint32_t fs = NULL;
		if (Source.FragmentSource.length() > 1)
		{
			fs = CompileShader(GL_FRAGMENT_SHADER, Source.FragmentSource);
			glAttachShader(program, fs);
		}

		uint32_t gs = NULL;
		if (Source.GeometrySource.length() > 1)
		{
			gs = CompileShader(GL_GEOMETRY_SHADER, Source.GeometrySource);
			glAttachShader(program, gs);
		}

		glLinkProgram(program);
		glValidateProgram(program);

		if (vs != NULL)
		{
			glDeleteShader(vs);
		}

		if (fs != NULL)
		{
			glDeleteShader(fs);
		}

		if (gs != NULL)
		{
			glDeleteShader(gs);
		}

		this->ID = program;
	}

	bool OpenGLShader::HasUniform(std::string const& Name)
	{
		return UniformLocations.contains(Name) || glGetUniformLocation(this->ID, Name.c_str()) != 0;
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(this->ID);
	}

	void OpenGLShader::SetInt(std::string const& Name, int32_t Value)
	{
		this->Bind();
		glUniform1i(this->GetUniformLocation(Name), Value);
	}

	void OpenGLShader::SetFloat(std::string const& Name, float Value)
	{
		this->Bind();
		glUniform1f(this->GetUniformLocation(Name), Value);
	}

	void OpenGLShader::SetDouble(std::string const& Name, float Value)
	{
		this->Bind();
		glUniform1d(this->GetUniformLocation(Name), Value);
	}

	void OpenGLShader::SetVec2(std::string const& Name, Vec2 const& Value)
	{
		this->Bind();
		glUniform2fv(this->GetUniformLocation(Name), 1, glm::value_ptr(Value));
	}

	void OpenGLShader::SetVec3(std::string const& Name, Vec3 const& Value)
	{
		this->Bind();
		glUniform3fv(this->GetUniformLocation(Name), 1, glm::value_ptr(Value));
	}

	void OpenGLShader::SetVec4(std::string const& Name, Vec4 const& Value)
	{
		this->Bind();
		glUniform4fv(this->GetUniformLocation(Name), 1, glm::value_ptr(Value));
	}

	void OpenGLShader::SetMat3x3(std::string const& Name, Mat3x3 const& Value, bool Transpose)
	{
		this->Bind();
		glUniformMatrix3fv(this->GetUniformLocation(Name), 1, Transpose, glm::value_ptr(Value));
	}

	void OpenGLShader::SetMat4x4(std::string const& Name, Mat4x4 const& Value, bool Transpose)
	{
		this->Bind();
		glUniformMatrix4fv(this->GetUniformLocation(Name), 1, Transpose, glm::value_ptr(Value));
	}

	uint32_t OpenGLShader::CompileShader(uint32_t type, std::string const& source)
	{
		uint32_t id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int32_t result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (!result)
		{
			int32_t length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)_malloca(length * (sizeof(char)));
			glGetShaderInfoLog(id, length, &length, message);
			VOLUND_WARNING("Failed to compile shader: %s", message);
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	uint32_t OpenGLShader::GetUniformLocation(std::string const& Name)
	{	
		if (UniformLocations.contains(Name))
		{
			return UniformLocations[Name];
		}
		else
		{
			int UniformLocation = glGetUniformLocation(this->ID, Name.c_str());

			if (UniformLocation == -1)
			{
				VOLUND_WARNING("Unknown Uniform specified (%s)", Name.c_str());
			}		
			
			UniformLocations[Name] = UniformLocation;
			return UniformLocation;
		}
	}

	OpenGLShader::OpenGLShader(std::string const& FilePath)
	{
		this->Init(FilePath);
	}

	OpenGLShader::~OpenGLShader()
	{
		if (this->ID != 0)
		{
			glDeleteProgram(this->ID);
		}
	}

} //namespace Volund