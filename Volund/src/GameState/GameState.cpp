#include "PCH/PCH.h"
#include "GameState.h"

namespace Volund
{
	Ref<Scene> GameState::GetScene()
	{
		return this->m_Scene;
	}

	Ref<LuaState> GameState::GetLuaState()
	{
		return this->m_LuaState;
	}

	void GameState::Procedure(const Event& e)
	{
		this->m_Input->Procedure(e);
		this->m_Scene->Procedure(e);
	}

	GameState::GameState(Ref<Window> window, const std::string& filepath)
	{		
		this->m_FilesystemLink = FilesystemLink::Create(std::filesystem::path(filepath).parent_path().string());

		this->m_Input = std::make_shared<Input>();
		this->m_Scene = std::make_shared<Scene>();
		this->m_LuaState = std::make_shared<LuaState>(this->m_Scene, this->m_Input, window);

		this->m_LuaState->ScriptFile(filepath);
	}

	GameState::~GameState()
	{
		this->m_Input.reset();
		this->m_Scene.reset();
		this->m_LuaState.reset();
	}
}