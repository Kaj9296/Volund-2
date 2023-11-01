#pragma once

#include "Editor/EditorContext/EditorContext.h"

class EditorWindow : public VL::ImGuiWindow
{
public:

	virtual ~EditorWindow() = default;

protected:
	
	VL::Ref<EditorContext> m_Context;
};