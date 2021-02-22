#include "BaseWindow.hpp"

class MainWindow : public BaseWindow<MainWindow>
{
public:
	PCWSTR ClassName() const { return L"Sample Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(m_hwnd, &ps);
				FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
				EndPaint(m_hwnd, &ps);
			}
			return 0;
		}
		return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
	}
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, PWSTR pCmdLine, int nCmdShow)
{
	MainWindow mainWindow;

	if (!mainWindow.Create(L"Learn to Program Windows", WS_OVERLAPPEDWINDOW))
	{
		return -1;
	}
	ShowWindow(mainWindow.Window(), nCmdShow);

	// run message loop
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return 0;
}