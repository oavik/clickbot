#include <windows.h>
#pragma comment(lib, "user32")

DWORD WINAPI sendclicks(LPVOID window)
{
	while (IsWindow((HWND)window)) {
		if (GetForegroundWindow() == (HWND)window) {
			INPUT click = {
				.type = INPUT_MOUSE,
				.mi = {
					.dwFlags = MOUSEEVENTF_LEFTDOWN,
				},
			};
			SendInput(1, &click, sizeof(click));
			Sleep(1);

			INPUT release = {
				.type = INPUT_MOUSE,
				.mi = {
					.dwFlags = MOUSEEVENTF_LEFTUP,
				},
			};
			SendInput(1, &release, sizeof(release));
		}
	}

	ExitProcess(0);
}

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR cmdline, INT show)
{
	(void)hinst; (void)hprev; (void)cmdline; (void)show;
	HWND clicker = FindWindowA(NULL, "Sakura Clicker");
	HANDLE clickthread = NULL;

	RegisterHotKey(NULL, 0, MOD_CONTROL, VK_SPACE);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (msg.message == WM_HOTKEY) {
			if (clickthread == NULL) {
				clickthread = CreateThread(NULL, 0, sendclicks, clicker, 0, NULL);
			} else {
				TerminateThread(clickthread, 0);
				clickthread = NULL;
			}
		}
	}

	return 0;
}