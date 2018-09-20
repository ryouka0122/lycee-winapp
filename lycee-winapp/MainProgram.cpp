#include <Windows.h>


#define WINDOW_CLASS_NAME TEXT("Lycee_window")
#define WINDOW_TITLE TEXT("Sample Lycee Window")
#define WINDOW_SIZE_WIDTH 800
#define WINDOW_SIZE_HEIGHT 600


LRESULT CALLBACK mainWndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp) {

	switch (uMsg) {
	case WM_CREATE:
		return 0;
	case WM_CLOSE:
		if (IDOK == MessageBox(hWnd, TEXT("終了しますか？"), TEXT("確認"), MB_OKCANCEL)) {
			DestroyWindow(hWnd);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wp, lp);
}


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	WNDCLASSEX wcex = {0};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = mainWndProc;
	wcex.lpszClassName = WINDOW_CLASS_NAME;
	wcex.lpszMenuName = NULL;
	wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;

	ATOM atom = RegisterClassEx(&wcex);

	if (INVALID_ATOM == atom) {
		return -1;
	}

	MSG msg = {0};
	HWND hMainWindow = CreateWindowEx(0L,
		WINDOW_CLASS_NAME, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		50, 50, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT,
		NULL, NULL, hInstance, NULL);

	if (IsWindow(hMainWindow)) {
		ShowWindow(hMainWindow, nCmdShow);
		UpdateWindow(hMainWindow);

		BOOL bRes;
		while (true) {
			bRes = GetMessage(&msg, hMainWindow, 0L, 0L);
			if (bRes <= 0) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	UnregisterClass(WINDOW_CLASS_NAME, hInstance);
	return msg.wParam;
}
