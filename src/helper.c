#include <windows.h>
#include <stdio.h>

void press_key(WORD key) {
  INPUT input = {0};
  input.type = INPUT_KEYBOARD;

  input.ki.wVk = key;
  SendInput(1, &input, sizeof(INPUT));

  input.ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, &input, sizeof(INPUT));
}

void click_mouse(int x, int y) {
  SetCursorPos(x, y);

  INPUT input = {0};
  input.type = INPUT_MOUSE;
  input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
  SendInput(1, &input, sizeof(INPUT));

  input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
  SendInput(1, &input, sizeof(INPUT));
}

void run_glitch(int x, int y) {

  press_key(VK_ESCAPE);
  Sleep(100);

  click_mouse(x, y);
  Sleep(200);

}

int hot_lava_active(HWND hwnd) {

  if (hwnd) {
    char title[256];
    GetWindowText(hwnd, title, sizeof(title));

    if (!strcmp(title, "Hot Lava")) {
      return 1;
    }

    return 0;
  }
}

int main() {
  SetConsoleTitle("Hot Lava Fly Glitch Helper");

  int x = 2262;
  int y = 903;

  char hotkey = 'G';

  printf("Hotkey: %c\nAbility Help position: %d, %d\n", hotkey, x, y);
  printf("Hotkey is deactivated while Hot Lava is not the focused window.\n");

  HWND hwnd;

  while (1) {

    hwnd = GetForegroundWindow();

    if (hot_lava_active(hwnd) && GetAsyncKeyState(hotkey) & 0x8000) {
      run_glitch(x, y);
      Sleep(300);
    }

    Sleep(10);
  }

  return 0;
}
