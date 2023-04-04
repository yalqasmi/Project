/*
Declare a function that checks the keys ()
{
  for each key in keys
    if the key is pressed down
      write the key in the output file
}
Declare a function of type LowLevelKeyboardProc that returns an int (int code, intPtr messageIdentifier, intPtr hookStruct)
{
  // LowLevelKeyboardProc is called by the system on a new keyboard input event

  if the code is not negative then
    call the check keys function

  return CallNextHookEx(HookID, nCode, wParam, lParam); // I think it just lets the original program continue running
}

Declare a function that sets the hook (LowLevelKeyboardProc proc)
{
  set the hook as the LowLevelKeyboardProc function 
  {
    Process curProcess = Process.GetCurrentProcess()
    ProcessModule curModule = curProcess.MainModule
    
    return SetWindowsHookEx(2 or 13, proc, GetModuleHandle(curModule.ModuleName), 0);
  }
}

main ()
{
  open a file
  
  call the setup hook function;

  after a while
    close the file

  call the API and send the file over
}

*/




/*
private static LowLevelKeyboardProc LowLevelProc = HookCallback;

HotkeysManager.SetupSystemHook();

public static void SetupSystemHook()
        {
            HookID = SetHook(LowLevelProc);
            IsHookSetup = true;
        }

private static IntPtr HookCallback(int nCode, IntPtr wParam, IntPtr lParam)
        {
            // Checks if this is called from keydown only because key ups aren't
used. if (nCode >= 0)
            {
                CheckHotkeys();

                // Cannot use System.Windows' keys because
                // they dont use the same values as windows
                //int vkCode = Marshal.ReadInt32(lParam);
                //System.Windows.Forms.Keys key =
(System.Windows.Forms.Keys)vkCode;
                //Debug.WriteLine(key);
            }

            // I think this tells windows that this app has successfully
            // handled the key events and now other apps can handle it next.
            return CallNextHookEx(HookID, nCode, wParam, lParam);
        }

private static void CheckHotkeys()
        {
            if (RequiresModifierKey)
            {
                if (Keyboard.Modifiers != ModifierKeys.None)
                {
                    foreach (GlobalHotkey hotkey in Hotkeys)
                    {
                        if (Keyboard.Modifiers == hotkey.Modifier && Keyboard.IsKeyDown(hotkey.Key))
                        {
                            if (hotkey.CanExecute)
                            {
                                hotkey.Callback?.Invoke();
                                }}}}}}

private static IntPtr SetHook(LowLevelKeyboardProc proc)
        {
            using (Process curProcess = Process.GetCurrentProcess())
            {
                using (ProcessModule curModule = curProcess.MainModule)
                {
                    return SetWindowsHookEx(WH_KEYBOARD_LL, proc,
GetModuleHandle(curModule.ModuleName), 0);
                }
            }
        }

HotkeysManager.AddHotkey(ModifierKeys.Control, Key.A, () => { AddToList("Ctrl+A
Fired"); });

public static void AddHotkey(ModifierKeys modifier, Key key, Action
callbackMethod, bool canExecute = true)
        {
            AddHotkey(new GlobalHotkey(modifier, key, callbackMethod,
canExecute));
        }

public GlobalHotkey(ModifierKeys modifier, Key key, Action callbackMethod, bool
canExecute = true)
        {
            this.Modifier = modifier;
            this.Key = key;
            this.Callback = callbackMethod;
            this.CanExecute = canExecute;
        }

public static void AddHotkey(GlobalHotkey hotkey)
        {
            Hotkeys.Add(hotkey);
        }

hotkeys is a list

*/
