
#include "framework.h"
#include "Input.h"


Input::Input()
{
	for (int i = 0; i < 256; i++) m_Keys[i] = Released;

}

bool Input::IsKeyDown(BYTE key)
{
	return m_Keys[key] == BeenPressed;
}

bool Input::IsKeyUp(BYTE key)
{
	return m_Keys[key] == BeenReleased;
}


bool Input::IsKey(BYTE key)
{
	if (m_Keys[key] == Pressed)
	{
		return true;
	}
	return false;
}

void Input::Update()
{
	for (int i = 1; i < 256; i++)
	{
		bool keyState = GetAsyncKeyState(i) < 0;
		if (keyState)
		{
			if(m_Keys[i] == Pressed || m_Keys[i] == BeenPressed)
			{
				m_Keys[i] = Pressed;
			}
			else if (m_Keys[i] == Released || m_Keys[i] == BeenReleased)
			{
				m_Keys[i] = BeenPressed;
			}
		}
		else 
		{
			if (m_Keys[i] == Released || m_Keys[i] == BeenReleased)
			{
				m_Keys[i] = Released;
			}
			else if (m_Keys[i] == Pressed || m_Keys[i] == BeenPressed)
			{
				m_Keys[i] = BeenReleased;
			}
		}
	}
}