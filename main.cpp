#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "BigEcho.h"

// Helper function to convert string to wstring
std::wstring StringToWString(const std::string& str) {
    int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    std::wstring wstr(len, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], len);
    return wstr;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: bigecho \"text\" \"font name\"" << std::endl;
        std::cerr << "Example: bigecho \"Hello\" \"Arial\"" << std::endl;
        return 1;
    }

    std::string text = argv[1];
    std::string fontName = argv[2];

    try {
        BigEcho bigEcho;
        bigEcho.RenderText(StringToWString(text), StringToWString(fontName));
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
