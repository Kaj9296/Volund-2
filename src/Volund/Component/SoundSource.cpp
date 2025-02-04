
#include "Component/SoundSource.hpp"
#include "Component/Transform.hpp"
#include "Scene.hpp"
#include "Lua/LuaAPI.hpp"

namespace Volund
{
	void SoundSource::Play()
	{
		this->m_source.Play();
	}

	void SoundSource::SetBuffer(std::shared_ptr<AudioBuffer> buffer)
	{
		this->m_source.SetBuffer(buffer);
	}

	std::shared_ptr<AudioBuffer> SoundSource::GetBuffer()
	{
		return this->m_source.GetBuffer();
	}

	void SoundSource::SetPitch(float pitch)
	{
		this->m_source.SetPitch(pitch);
	}

	float SoundSource::GetPitch()
	{
		return this->m_source.GetPitch();
	}

	void SoundSource::SetLooping(bool looping)
	{
		this->m_source.SetLooping(looping);
	}

	bool SoundSource::GetLooping()
	{
		return this->m_source.GetLooping();
	}

	void SoundSource::SetGain(float gain)
	{
		this->m_source.SetGain(gain);
	}

	float SoundSource::GetGain()
	{
		return this->m_source.GetGain();
	}

	void SoundSource::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (e.type)
		{
		case VOLUND_EVENT_UPDATE:
		{
			if (this->AutoPlay && !this->m_hasAutoPlayed)
			{
				this->m_hasAutoPlayed = true;
				this->Play();
			}

			static Vec3 oldPosition = Vec3(0.0f);

			const float timeStep = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

			const std::shared_ptr<Transform> entityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

			this->m_source.SetPosition(entityTransform->pos);
			this->m_source.SetVelocity((entityTransform->pos - oldPosition) * timeStep);
			this->m_source.SetDirection(entityTransform->GetFront());
		}
		break;
		default:
		{

		}
		break;
		}
	}

	SoundSource::SoundSource(std::shared_ptr<AudioBuffer> buffer)
	{
		this->m_source.SetBuffer(buffer);
	}

    VOLUND_USERTYPE_COMPONENT_REGISTER(SoundSource,
    [](LuaState* state){
        state->NewUsertype<SoundSource>("SoundSource", 
            sol::constructors<>(),
            "autoPlay", &SoundSource::AutoPlay,
            "play", &SoundSource::Play,
            "set_buffer", &SoundSource::SetBuffer,
            "get_buffer", &SoundSource::GetBuffer,
            "set_pitch", &SoundSource::SetPitch,
            "get_pitch", &SoundSource::GetPitch,
            "set_looping", &SoundSource::SetLooping,
            "get_looping", &SoundSource::GetLooping,
            "set_gain", &SoundSource::SetGain,
            "get_gain", &SoundSource::GetGain
        );
    }, std::shared_ptr<AudioBuffer>);
}