#pragma once

#include <windows.h>
#include <string>

#include "include/internal/cef_types_wrappers.h"

// Returns the current time in microseconds.
uint64_t GetTimeNow();

// Set the window's user data pointer.
void SetUserDataPtr(HWND hWnd, void* ptr);

// Return the window's user data pointer.
template <typename T>
T GetUserDataPtr(HWND hWnd) {
  return reinterpret_cast<T>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
}

// Set the window's window procedure pointer and return the old value.
WNDPROC SetWndProcPtr(HWND hWnd, WNDPROC wndProc);

// Return the resource string with the specified id.
std::wstring GetResourceString(UINT id);

int GetCefMouseModifiers(WPARAM wparam);
int GetCefKeyboardModifiers(WPARAM wparam, LPARAM lparam);
bool IsKeyDown(WPARAM wparam);

// Returns the device scale factor. For example, 200% display scaling will
// return 2.0.
float GetDeviceScaleFactor();
