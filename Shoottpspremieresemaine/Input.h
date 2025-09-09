#pragma once


class Input
{
	public:
		Input();
		void Update();
		bool IsKeyDown(BYTE key);
		bool IsKeyUp(BYTE key);
		bool IsKey(BYTE key);

	private:
		BYTE m_Keys[256];
		enum keyState
		{
			Pressed,
			Released,
			BeenPressed,
			BeenReleased,
		};
};

