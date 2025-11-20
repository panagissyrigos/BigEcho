#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "BigEcho.h"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

    BigEcho::BigEcho() {
        GdiplusStartupInput gdiplusStartupInput;
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    }

    BigEcho::~BigEcho() {
        GdiplusShutdown(gdiplusToken);
    }

    void BigEcho::RenderText(const std::wstring& text, const std::wstring& fontName, int fontSize) {
        // Create bitmap for rendering
        int width = fontSize * text.length() * 2;
        int height = fontSize * 2;

        Bitmap bitmap(width, height, PixelFormat32bppARGB);
        Graphics graphics(&bitmap);
        graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
        graphics.Clear(Color(255, 0, 0, 0));

        // Create font and brush
        FontFamily fontFamily(fontName.c_str());
        Font font(&fontFamily, (REAL)fontSize, FontStyleRegular, UnitPixel);
        SolidBrush whiteBrush(Color(255, 255, 255, 255));

        // Measure text to center it
        RectF boundingBox;
        graphics.MeasureString(text.c_str(), -1, &font, PointF(0, 0), &boundingBox);

        // Draw text
        graphics.DrawString(text.c_str(), -1, &font,
            PointF(0, 0), &whiteBrush);

        // Convert bitmap to console output
        ConvertToConsole(bitmap, (int)boundingBox.Width, (int)boundingBox.Height);
    }

    void BigEcho::ConvertToConsole(Bitmap& bitmap, int textWidth, int textHeight) {
        // ASCII characters for different brightness levels
        const char* chars = " .:-=+*#%@";
        int charCount = strlen(chars);

        // Sample the bitmap and convert to ASCII
        for (int y = 0; y < textHeight; y += 2) {  // Sample every 2 pixels for aspect ratio
            for (int x = 0; x < textWidth; x++) {
                Color pixelColor;
                bitmap.GetPixel(x, y, &pixelColor);

                // Calculate brightness (0-255)
                int brightness = (pixelColor.GetR() + pixelColor.GetG() + pixelColor.GetB()) / 3;

                // Map to character
                int charIndex = (brightness * charCount) / 256;
                std::cout << chars[charIndex];
            }
            std::cout << std::endl;
        }
    }