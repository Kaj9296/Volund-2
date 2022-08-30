#include "PCH/PCH.h"
#include "Input.h"

namespace Volund
{
	int8_t Input::Keys[KEY_AMOUNT];
	int8_t Input::MouseButtons[MOUSE_BUTTON_AMOUNT];

	double Input::ScrollOffset = 0;
	Vec2 Input::MousePosition;

	bool Input::IsHeld(char KeyCode)
	{
		return Keys[KeyCode];
	}

	bool Input::IsPressed(char KeyCode)
	{
		bool IsDown = Keys[KeyCode] == 1;
		Keys[KeyCode] += IsDown;

		return IsDown;
	}

	bool Input::IsMouseButtonHeld(char Button)
	{
		return MouseButtons[Button];
	}

	bool Input::IsMouseButtonPressed(char Button)
	{
		bool IsDown = MouseButtons[Button] == 1;
		MouseButtons[Button] += IsDown;

		return IsDown;
	}

	double Input::GetScrollOffset()
	{
		double TEMP = ScrollOffset;
		ScrollOffset = 0;
		return TEMP;
	}

	Vec2 Input::GetCursorPosition()
	{
		return MousePosition;
	}

	void Input::SendEvent(KeyEvent E)
	{		
		Keys[E.GetKey()] += E.GetIsDown();
		Keys[E.GetKey()] *= E.GetIsDown();
		Keys[E.GetKey()] = Math::Min(Keys[E.GetKey()], (int8_t)100);
	}

	void Input::SendEvent(MouseButtonEvent E)
	{
		MouseButtons[E.GetButton()] += E.GetIsDown();
		MouseButtons[E.GetButton()] *= E.GetIsDown();
		MouseButtons[E.GetButton()] = Math::Min(MouseButtons[E.GetButton()], (int8_t)100);
	}

	void Input::SendEvent(ScrollEvent E)
	{
		ScrollOffset += E.GetYOffset();
	}

	void Input::SendEvent(CursorPosEvent E)
	{
		//VOLUND_INFO("%d", E.GetXPos());

		MousePosition = Vec2(E.GetXPos(), E.GetYPos());
	}
}