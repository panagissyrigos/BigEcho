#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

class BigEcho {
private:
    ULONG_PTR gdiplusToken;

public:
    BigEcho();
    ~BigEcho();
    void RenderText(const std::wstring& text, const std::wstring& fontName, int fontSize = 24);

private:
    void ConvertToConsole(Bitmap& bitmap, int textWidth, int textHeight);
};
