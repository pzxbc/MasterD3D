#include <Windows.h>

// 学习资料
// https://docs.microsoft.com/en-us/windows/win32/learnwin32/introduction-to-windows-programming-in-c--

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, PWSTR pCmdLine, int nCmdShow)
{
	// Register the Window class
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc{};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the Window
	HWND hwnd = CreateWindowEx(
		0, // optional window styles
		CLASS_NAME, // window class
		L"Learn to Program Windows", // window text
		WS_OVERLAPPEDWINDOW, // window style
		// size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, // parent window
		NULL, // Menu
		hInstance, // Instance handle
		NULL // additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	// run the message loop
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 消息处理的返回值是跟消息有关的
	// 不同消息的返回值会影响后续的处理
	// 比如WM_NCCREATE 如果返回-1，则会阻止后续窗口的创建
	// 一般返回0即可，但还是要看看MSDN文档
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));
			EndPaint(hwnd, &ps);
		}
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}