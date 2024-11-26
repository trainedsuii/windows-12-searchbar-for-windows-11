// ==WindhawkMod==
// @id              windows12-top-search-bar-mod
// @name            Windows 12 Top Search Bar
// @description     Adds a top search bar similar to the one expected in Windows 12.
// @version         1.0
// @author          Your Name
// @github          https://github.com/yourgithubusername
// @twitter         https://twitter.com/yourtwitterusername
// @homepage        https://your-personal-homepage.example.com/
// @include         explorer.exe
// @compilerOptions -lgdi32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Windows 12 Top Search Bar
This mod adds a top search bar similar to the one expected in Windows 12.

To see the mod in action:
- Compile the mod with the button on the left or with Ctrl+B.
- Run Windows Explorer or restart your computer to see the changes.
- The top search bar will appear at the top of your screen.

# Getting started
Check out the documentation
[here](https://github.com/ramensoftware/windhawk/wiki/Creating-a-new-mod).
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
# Here you can define settings, in YAML format, that the mod users will be able
# to configure. Metadata values such as $name and $description are optional.
# Check out the documentation for more information:
# https://github.com/ramensoftware/windhawk/wiki/Creating-a-new-mod#settings
- searchBarColor:
  - red: 255
  - green: 255
  - blue: 255
  $name: Search Bar Color
  $description: The color of the search bar.
- enableVoiceSearch: false
  $name: Enable Voice Search
  $description: When enabled, voice search will be activated.
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <string>

// Function to create a search bar
HWND CreateSearchBar(HWND hWndParent, HINSTANCE hInstance) {
    HWND hSearchBar = CreateWindowEx(0, L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        10, 10, 400, 25,
        hWndParent, NULL, hInstance, NULL);
    return hSearchBar;
}

// Main window procedure
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            HINSTANCE hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
            CreateSearchBar(hWnd, hInstance);
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Entry point
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"WindhawkModClass";

    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(0, L"WindhawkModClass", L"Windhawk Mod",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
