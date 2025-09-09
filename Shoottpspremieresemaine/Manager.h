#pragma once

#include "Input.h"
#include "Timer.h"

class Manager
{
public:
    Manager(HINSTANCE hInstance, int nCmdShow);
    int Run();

private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    void Update();
    void Render(HDC hdc);

    HINSTANCE m_hInstance;
    HWND m_hWnd;
    
    Input m_Input;
    Timer m_Timer;

    // Propriétés du carré
    RECT m_Player;
};
