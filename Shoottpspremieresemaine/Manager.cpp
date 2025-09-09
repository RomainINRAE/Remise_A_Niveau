
#include "framework.h"


#include "Manager.h"
#include <iostream>

Manager::Manager(HINSTANCE hInstance, int nCmdShow)
    : m_hInstance(hInstance), m_hWnd(nullptr)
{
    // Définir la classe de fenêtre
    WNDCLASS wc = {};
    wc.lpfnWndProc = Manager::WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"FenetreManager";

    RegisterClass(&wc);

    // Créer la fenêtre
    m_hWnd = CreateWindowEx(
        0,
        L"FenetreManager",
        L"Fenetre Win32 - Manager",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
        nullptr, nullptr, hInstance, this // passe "this" comme paramètre
    );

    ShowWindow(m_hWnd, nCmdShow);

    // Init Timer
    m_Timer.SetDataTime(timeGetTime());
    m_Timer.SetDeltaTime(0.f);
    m_Timer.SetTotalTime(0.f);

    // Init carré
    m_Player = { 250, 250, 300, 300 }; // (x1, y1, x2, y2)
}

int Manager::Run()
{
    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Update();
            InvalidateRect(m_hWnd, nullptr, TRUE); // Redessine la fenêtre
        }
    }
    return static_cast<int>(msg.wParam);
}

void Manager::Update()
{
    m_Input.Update();
    m_Timer.Update();

    // Exemple : quitter avec Echap
    if (m_Input.IsKeyDown(VK_ESCAPE))
    {
        PostQuitMessage(0);
    }

    // ---- Déplacement du carré ----
    int speed = 200; // pixels par seconde
    float deltaTime = m_Timer.GetDeltaTime();

    if (m_Input.IsKey(VK_LEFT))
    {
        OffsetRect(&m_Player, (int)(-speed * deltaTime), 0);
    }
    if (m_Input.IsKey(VK_RIGHT))
    {
        OffsetRect(&m_Player, (int)(speed * deltaTime), 0);
    }
    if (m_Input.IsKey(VK_UP))
    {
        OffsetRect(&m_Player, 0, (int)(-speed * deltaTime));
    }
    if (m_Input.IsKey(VK_DOWN))
    {
        OffsetRect(&m_Player, 0, (int)(speed * deltaTime));
    }

    // Debug Timer
    std::cout << "Temps écoulé : " << m_Timer.GetTotalTime() << "s" << std::endl;
}


void Manager::Render(HDC hdc)
{
    // Efface la fenêtre en noir
    HBRUSH background = CreateSolidBrush(RGB(0, 0, 0));
    RECT rect = { 0, 0, 600, 600 };   // créer un RECT local
    FillRect(hdc, &rect, background);
    DeleteObject(background);

    // Dessiner le carré bleu
    HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
    FillRect(hdc, &m_Player, brush);
    DeleteObject(brush);
}



LRESULT CALLBACK Manager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Manager* pThis;

    if (message == WM_NCCREATE)
    {
        CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = reinterpret_cast<Manager*>(cs->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
        pThis->m_hWnd = hWnd;
    }
    else
    {
        pThis = reinterpret_cast<Manager*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    if (pThis)
    {
        switch (message)
        {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            pThis->Render(hdc);
            EndPaint(hWnd, &ps);
        }
        return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

