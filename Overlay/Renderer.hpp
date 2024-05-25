#pragma once
#include <GL/gl.h>
#include <cstring>
#include <string>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include "../imgui/imgui.h"
#include "../Utils/Color.hpp"
#include "../Utils/Features.hpp"
#include "../Math/Vector2D.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Player.hpp"

// I'm gonna be dead before I ever find a single unknowncheats source that consistently uses either 2 spaces, 4 spaces or tabs...
// is it really that hard to run a formatter over it

class Renderer {
public:
  static void DrawText(ImDrawList *canvas, const Vector2D &pos, const char *text, ImColor color, bool outline, bool centered, bool adjustHeight) {
    const auto textColor = color;
    const auto outlineColor = ImColor(0, 0, 0);

    const auto textSize = ImGui::CalcTextSize(text);
    const auto horizontalOffset = centered ? textSize.x / 2 : 0.0f;
    const auto verticalOffset = adjustHeight ? textSize.y : 0.0f;

    if (outline) {
      canvas->AddText({pos.x - horizontalOffset, pos.y - verticalOffset - 1}, outlineColor, text);
      canvas->AddText({pos.x - horizontalOffset, pos.y - verticalOffset + 1}, outlineColor, text);
      canvas->AddText({pos.x - horizontalOffset - 1, pos.y - verticalOffset}, outlineColor, text);
      canvas->AddText({pos.x - horizontalOffset + 1, pos.y - verticalOffset}, outlineColor, text);
    }

    canvas->AddText({pos.x - horizontalOffset, pos.y - verticalOffset}, textColor, text);
  }

  static void DrawString(ImDrawList *canvas, float fontSize, const Vector2D &vec, const ImColor &col, bool bCenter, bool stroke, const char *pText, ...) {
    va_list va_alist;
    char buf[1024] = {0};
    va_start(va_alist, pText);
    vsnprintf(buf, sizeof(buf), pText, va_alist);
    va_end(va_alist);
    std::string text = pText;
    Vector2D drawPos = vec;
    if (bCenter) {
      ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
      drawPos.x = vec.x - textSize.x / 2;
      drawPos.y = vec.y - textSize.y;
    }

    if (stroke) {
      canvas->AddText(ImGui::GetFont(), fontSize, ImVec2(drawPos.x + 1, drawPos.y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
      canvas->AddText(ImGui::GetFont(), fontSize, ImVec2(drawPos.x - 1, drawPos.y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
      canvas->AddText(ImGui::GetFont(), fontSize, ImVec2(drawPos.x + 1, drawPos.y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
      canvas->AddText(ImGui::GetFont(), fontSize, ImVec2(drawPos.x - 1, drawPos.y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
    }
    canvas->AddText(ImGui::GetFont(), fontSize, ImVec2(drawPos.x, drawPos.y), col, text.c_str());
  }

  static void DrawCircle(ImDrawList *canvas, const Vector2D &pos, float radius, int segments, const ImColor &color, float thickness) { canvas->AddCircle(ImVec2(pos.x, pos.y), radius, color, segments, thickness); }

  static void DrawCircleFilled(ImDrawList *canvas, const Vector2D &pos, float radius, int segments, const ImColor &color) { canvas->AddCircleFilled(ImVec2(pos.x, pos.y), radius, color, segments); }

  static void DrawLine(ImDrawList *canvas, const Vector2D &start, const Vector2D &end, float thickness, const ImColor &color) { canvas->AddLine((const ImVec2 &) start, (const ImVec2 &) end, ImColor(color), thickness); }

  static void DrawQuadFilled(ImDrawList *canvas, ImVec2 p1, ImVec2 p2, ImVec2 p3, ImVec2 p4, ImColor color) { canvas->AddQuadFilled(p1, p2, p3, p4, color); }

  static void DrawHexagon(ImDrawList *canvas, const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, const ImVec2 &p5, const ImVec2 &p6, ImU32 col, float thickness) { canvas->AddHexagon(p1, p2, p3, p4, p5, p6, col, thickness); }

  static void DrawHexagonFilled(ImDrawList *canvas, const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, const ImVec2 &p5, const ImVec2 &p6, ImU32 col) { canvas->AddHexagonFilled(p1, p2, p3, p4, p5, p6, col); }

  // Bar Style 1
  static void drawRectangleOutline(Vector2D position, Vector2D size, Color color, float lineWidth) {
    glLineWidth(lineWidth);
    glColor3f(color.r, color.g, color.b);

    glBegin(GL_LINE_LOOP);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x + size.x, position.y);
    glVertex2f(position.x + size.x, position.y + size.y);
    glVertex2f(position.x, position.y + size.y);
    glEnd();

    glLineWidth(1.0f);
  }

  static void drawFilledRectagle(Vector2D position, Vector2D size, Color color) {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_QUADS);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x + size.x, position.y);
    glVertex2f(position.x + size.x, position.y + size.y);
    glVertex2f(position.x, position.y + size.y);
    glEnd();
  }

  static void drawBorderedFillRectangle(Vector2D position, Vector2D size, Color fillColor, Color borderColor, float lineWidth, float fill) {
    drawFilledRectagle(position, Vector2D(size.x, size.y), Color(0, 0, 0));
    drawFilledRectagle(position, Vector2D(size.x * fill, size.y), fillColor);
    drawRectangleOutline(position, size, borderColor, lineWidth);
  }

  static void DrawCorneredBox(ImDrawList *canvas, float X, float Y, float W, float H, ImColor color, float thickness) {
    float lineW = (W / 4);
    float lineH = (H / 5.5);
    float lineT = -thickness;
    // corners
    DrawLine(canvas, Vector2D(X, Y + thickness / 2), Vector2D(X, Y + lineH), thickness, color); // bot right vert
    DrawLine(canvas, Vector2D(X + thickness / 2, Y), Vector2D(X + lineW, Y), thickness, color);
    DrawLine(canvas, Vector2D(X + W - lineW, Y), Vector2D(X + W - thickness / 2, Y), thickness, color); // bot left hor
    DrawLine(canvas, Vector2D(X + W, Y + thickness / 2), Vector2D(X + W, Y + lineH), thickness, color);
    DrawLine(canvas, Vector2D(X, Y + H - lineH), Vector2D(X, Y + H - (thickness / 2)), thickness, color); // top right vert
    DrawLine(canvas, Vector2D(X + thickness / 2, Y + H), Vector2D(X + lineW, Y + H), thickness, color);
    DrawLine(canvas, Vector2D(X + W - lineW, Y + H), Vector2D(X + W - thickness / 2, Y + H), thickness, color); // top left hor
    DrawLine(canvas, Vector2D(X + W, Y + H - lineH), Vector2D(X + W, Y + H - (thickness / 2)), thickness, color);
  }

  static void Draw2DBox(ImDrawList *canvas, int Type, int Style, Vector2D &foot, const Vector2D &head, const ImColor &color2D, const ImColor &Filledcolor, float thickness) {
    // Type = 2D, 2D Filled
    // Style = 1 or 2, idk what to call them (for now)
    if (Type == 0) { // 2D Box
      if (Style == 0) {
        float height = head.y - foot.y;
        float width = height / 2.0f;
        canvas->AddRect(ImVec2(foot.x - (width / 2), foot.y), ImVec2(head.x + (width / 2), head.y + (height * 0.2)), color2D, 0.0f, 0, thickness);
      }
      if (Style == 1) {
        float Height = (head.y - foot.y);
        Vector2D rectTop = Vector2D(head.x - Height / 3, head.y);
        Vector2D rectBottom = Vector2D(foot.x + Height / 3, foot.y);
        canvas->AddRect(ImVec2(rectBottom.x, rectBottom.y), ImVec2(rectTop.x, rectTop.y + (Height * 0.2)), color2D, 0.0f, 0, thickness);
      }
    }
    if (Type == 1) { // 2D Box + 2D Filled Box
      if (Style == 0) {
        float height = head.y - foot.y;
        float width = height / 2.0f;
        canvas->AddRect(ImVec2(foot.x - (width / 2), foot.y), ImVec2(head.x + (width / 2), head.y + (height * 0.2)), color2D, 0.0f, 0, thickness);
        canvas->AddRectFilled(ImVec2(foot.x - (width / 2), foot.y), ImVec2(head.x + (width / 2), head.y + (height * 0.2)), Filledcolor, 0.0f, 0);
      }
      if (Style == 1) {
        float Height = (head.y - foot.y);
        Vector2D rectTop = Vector2D(head.x - Height / 3, head.y);
        Vector2D rectBottom = Vector2D(foot.x + Height / 3, foot.y);
        canvas->AddRect(ImVec2(rectBottom.x, rectBottom.y), ImVec2(rectTop.x, rectTop.y + (Height * 0.2)), color2D, 0.0f, 0, thickness);
        canvas->AddRectFilled(ImVec2(rectBottom.x, rectBottom.y), ImVec2(rectTop.x, rectTop.y + (Height * 0.2)), Filledcolor, thickness);
      }
    }
    if (Type == 2) { // 2D Corners
      float height = head.y - foot.y;
      float width = height / 2.0f;
      float x = foot.x - (width / 2.f);

      Renderer::DrawCorneredBox(canvas, x, foot.y, width, height + (height * 0.2), color2D, thickness);
    }
  }

  static void DrawRectFilled(ImDrawList *canvas, float x, float y, float x2, float y2, ImColor color, float rounding, int rounding_corners_flags) { canvas->AddRectFilled(ImVec2(x, y), ImVec2(x2, y2), color, rounding, rounding_corners_flags); }

  static void DrawProgressBar(ImDrawList *canvas, float x, float y, float w, float h, int value, int v_max, ImColor barColor) {
    canvas->AddRectFilled(ImVec2(x - 1, y - 1), ImVec2(x + w + 1, y - h + 1), ImColor(20, 20, 20), 0, 1);
    DrawRectFilled(canvas, x, y, x + w, y - ((h / float(v_max)) * (float) value), barColor, 0.0f, 0);
    canvas->AddRect(ImVec2(x - 1, y - 1), ImVec2(x + w + 1, y - h + 1), ImColor(0, 0, 0), 0, 1);
  }

  // Draw 2D Bars
  static void Draw2DBar(ImDrawList *canvas, int BarMode, int BarStyle, int ColorMode, Vector2D &Foot, Vector2D &Head, Vector2D &AboveHead, int health, int maxHealth, int shield, int maxShield, float thickness, float thickness2, float BarWidth, float BarHeight) {
    // Shield Color
    ImColor shieldBarColor;
    if (ColorMode == 0) { // Max shield
      switch (maxShield) {
        case 75:
          shieldBarColor = ImColor(39, 178, 255, 255); // Blue
          break;
        case 100:
          shieldBarColor = ImColor(206, 59, 255, 255); // Purple
          break;
        case 125:
          shieldBarColor = ImColor(219, 2, 2, 255); // Red
          break;
        default:
          shieldBarColor = ImColor(247, 247, 247, 255); // White
          break;
      }
    }

    if (ColorMode == 1) { // Current shield
      switch (shield) { // WARNING: FUCKERY !!! this switch is using a gcc language extension, will not work when using any other compiler (replace with if-else)
        case 0 ... 50:
          shieldBarColor = ImColor(247, 247, 247, 255); // White
          break;
        case 51 ... 75 :
          shieldBarColor = ImColor(39, 178, 255, 255); // Blue
          break;
        case 76 ... 100:
          shieldBarColor = ImColor(206, 59, 255, 255); // Purple
          break;
        case 101 ... 125:
          shieldBarColor = ImColor(219, 2, 2, 255); // Red
          break;
        default:
          shieldBarColor = ImColor(247, 247, 247, 255); // White
          break;
      }
    }

    // Bars
    if (BarMode == 0) { // Health Only
      if (BarStyle == 0) { // Side Bar
        // Old + New Side Bar - Credits: wafflesgaming (UnknownCheats)
        float height = Head.y - Foot.y;
        float width = height / 2.f;
        float width2 = width / 10;
        if (width2 < 2.f)
          width2 = 2.;
        if (width2 > 3)
          width2 = 3.;

        float entityHeight = Foot.y - Head.y;
        float boxLeft = Foot.x - entityHeight / 3;
        float boxRight = Head.x + entityHeight / 3;
        float barPercentWidth = thickness2;
        float barPixelWidth = barPercentWidth * (boxRight - boxLeft);
        float barHeight = entityHeight * (health / 100.0f);
        Vector2D barTop = Vector2D(boxLeft - barPixelWidth, Foot.y - barHeight);
        Vector2D barBottom = Vector2D(boxLeft, Foot.y);

        Renderer::DrawProgressBar(canvas, barBottom.x - 3.5f, barBottom.y, width2, barBottom.y - Head.y + (entityHeight * 0.2), health, 100, ImColor(0, 255, 0));
      }
      if (BarStyle == 1) { // Top Bar
        float height = BarHeight; // 8.0f
        float width = BarWidth; // 80.0f
        Vector2D rectPosition = Vector2D(Foot.x - width / 2, AboveHead.y - 10.0f);
        Vector2D size = Vector2D(width, height);

        // HealthBar
        float fill = (float) health / (float) maxHealth;
        Renderer::drawBorderedFillRectangle(rectPosition, size, Color::lerp(Color(1.0, 0.0, 0.0), Color(0.0, 1.0, 0.0), fill), Color(), thickness, fill);
      }
    }
    if (BarMode == 1) { // Shield Only
      if (BarStyle == 0) { // Side Bar
        // Old + New Side Bar - Credits: wafflesgaming (UnknownCheats)
        float height = Head.y - Foot.y;
        float width = height / 2.f;
        float width2 = width / 10;
        if (width2 < 2.f)
          width2 = 2.;
        if (width2 > 3)
          width2 = 3.;

        float entityHeight = Foot.y - Head.y;
        float boxLeft = Foot.x - entityHeight / 3;
        float boxRight = Head.x + entityHeight / 3;
        float barPercentWidth = thickness2;
        float barPixelWidth = barPercentWidth * (boxRight - boxLeft);
        float barHeight = entityHeight * (health / 100.0f);
        Vector2D barTop = Vector2D(boxLeft - barPixelWidth, Foot.y - barHeight);
        Vector2D barBottom = Vector2D(boxLeft, Foot.y);

        Renderer::DrawProgressBar(canvas, barBottom.x - 3.5f, barBottom.y, width2, barBottom.y - Head.y + (entityHeight * 0.2), shield, maxShield, shieldBarColor);
      }
      if (BarStyle == 1) { // Top Bar
        float height = BarHeight; // 8.0f
        float width = BarWidth; // 80.0f
        Vector2D rectPosition = Vector2D(Foot.x - width / 2, AboveHead.y - 10.0f);
        Vector2D size = Vector2D(width, height);

        // ShieldBar
        float fill = (float) shield / (float) maxShield;
        switch (maxShield) {
          case 125: // Red shield
            Renderer::drawBorderedFillRectangle(Vector2D(rectPosition.x, rectPosition.y - (height + 3)), size, Color::lerp(Color(1.0, 0.0, 0.0), Color(1.0, 0.0, 0.0), fill), Color(), thickness, fill);
            break;
          case 100: // Purple shield
            Renderer::drawBorderedFillRectangle(Vector2D(rectPosition.x, rectPosition.y - (height + 3)), size, Color::lerp(Color(0.501, 0.00, 0.970), Color(0.501, 0.00, 0.970), fill), Color(), thickness, fill);
            break;
          case 75: // Blue shield
            Renderer::drawBorderedFillRectangle(Vector2D(rectPosition.x, rectPosition.y - (height + 3)), size, Color::lerp(Color(0.0297, 0.734, 0.990), Color(0.0297, 0.734, 0.990), fill), Color(), thickness, fill);
            break;
          case 50: // Grey Shield
            Renderer::drawBorderedFillRectangle(Vector2D(rectPosition.x, rectPosition.y - (height + 3)), size, Color::lerp(Color(0.707, 0.702, 0.700), Color(0.707, 0.702, 0.700), fill), Color(), thickness, fill);
            break;
        }
      }
    }

    if (BarMode == 2) { // Health & Shield
      if (BarStyle == 0) { // Side Bar
        // Old + New Side Bar - Credits: wafflesgaming (UnknownCheats)
        float height = Head.y - Foot.y;
        float width = height / 2.f;
        float width2 = width / 10;
        if (width2 < 2.f)
          width2 = 2.;
        if (width2 > 3)
          width2 = 3.;

        float entityHeight = Foot.y - Head.y;
        float boxLeft = Foot.x - entityHeight / 3;
        float boxRight = Head.x + entityHeight / 3;
        float barPercentWidth = thickness2;
        float barPixelWidth = barPercentWidth * (boxRight - boxLeft);
        float barHeight = entityHeight * (health / 100.0f);
        Vector2D barTop = Vector2D(boxLeft - barPixelWidth, Foot.y - barHeight);
        Vector2D barBottom = Vector2D(boxLeft, Foot.y);

        Renderer::DrawProgressBar(canvas, barBottom.x - 3.5f /* + (width / 2) - width2*/, barBottom.y, width2, barBottom.y - Head.y + (entityHeight * 0.2), health, 100, ImColor(0, 255, 0));
        Renderer::DrawProgressBar(canvas, barBottom.x - 8.5f /* + (width / 2) - width2*/, barBottom.y, width2, barBottom.y - Head.y + (entityHeight * 0.2), shield, maxShield, shieldBarColor);
      }

      if (BarStyle == 1) { // Top Bar
        float height = BarHeight; // 8.0f
        float width = BarWidth; // 80.0f
        Vector2D rectPosition = Vector2D(Foot.x - width / 2, Head.y - 10.0f);
        Vector2D size = Vector2D(width, height);

        // HealthBar
        float fillHP = (float) health / (float) maxHealth;
        Renderer::drawBorderedFillRectangle(rectPosition, size, Color::lerp(Color(1.0, 0.0, 0.0), Color(0.0, 1.0, 0.0), fillHP), Color(), thickness, fillHP);

        // ShieldBar
        float fillAP = (float) shield / (float) maxShield;

        switch (maxShield) {
          case 125: // Red shield
            Renderer::drawBorderedFillRectangle(Vector2D(rectPosition.x, rectPosition.y - (height + 3)), size, Color::lerp(Color(1.0, 0.0, 0.0), Color(1.0, 0.0, 0.0), fillAP), Color(), thickness, fillAP);
            break;
          case 100: // Purple shield
            Renderer::drawBorderedFillRectangle(Vector2D(rectPosition.x, rectPosition.y - (height + 3)), size, Color::lerp(Color(0.501, 0.00, 0.970), Color(0.501, 0.00, 0.970), fillAP), Color(), thickness, fillAP);
            break;
          case 75: // Blue shield
            Renderer::drawBorderedFillRectangle(Vector2D(rectPosition.x, rectPosition.y - (height + 3)), size, Color::lerp(Color(0.0297, 0.734, 0.990), Color(0.0297, 0.734, 0.990), fillAP), Color(), thickness, fillAP);
            break;
          case 50: // Grey Shield
            Renderer::drawBorderedFillRectangle(Vector2D(rectPosition.x, rectPosition.y - (height + 3)), size, Color::lerp(Color(0.707, 0.702, 0.700), Color(0.707, 0.702, 0.700), fillAP), Color(), thickness, fillAP);
            break;
        }
      }
    }
  }

  static Vector3D RotatePoint(Vector3D EntityPos, Vector3D LocalPlayerPos, int posX, int posY, int sizeX, int sizeY, float angle, float zoom, bool *viewCheck) {
    float r_1, r_2;
    float x_1, y_1;

    r_1 = -(EntityPos.y - LocalPlayerPos.y);
    r_2 = EntityPos.x - LocalPlayerPos.x;

    float yawToRadian = angle * (float) (M_PI / 180.0F);
    x_1 = (float) (r_2 * (float) cos((double) (yawToRadian)) - r_1 * sin((double) (yawToRadian))) / 20;
    y_1 = (float) (r_2 * (float) sin((double) (yawToRadian)) + r_1 * cos((double) (yawToRadian))) / 20;

    *viewCheck = y_1 < 0;

    x_1 *= zoom;
    y_1 *= zoom;

    int sizX = sizeX / 2;
    int sizY = sizeY / 2;

    x_1 += sizX;
    y_1 += sizY;

    if (x_1 < 5)
      x_1 = 5;

    if (x_1 > sizeX - 5)
      x_1 = sizeX - 5;

    if (y_1 < 5)
      y_1 = 5;

    if (y_1 > sizeY - 5)
      y_1 = sizeY - 5;

    x_1 += posX;
    y_1 += posY;

    return Vector3D(x_1, y_1, 0);
  }

  static void TeamMiniMap(int x, int y, int radius, int teamID, float targetyaw, int dotSize, int outlineSize, const ImColor &circleColor) {
    auto colOutline = ImGui::ColorConvertFloat4ToU32(ImVec4(0.0, 0.0, 0.0, 1.0));
    ImVec2 center(x, y);
    // ImGui::GetWindowDrawList()->AddCircleFilled(center, radius, ImGui::ColorConvertFloat4ToU32(ImVec4(0.99, 0, 0, 0.99)));
    // ImGui::GetWindowDrawList()->AddCircle(center, radius, colOutline, 12, radius);
    ImGui::GetWindowDrawList()->AddCircleFilled(center, radius, circleColor);
    ImGui::GetWindowDrawList()->AddCircle(center, outlineSize, colOutline, 12, radius);

    // Draw a line pointing in the direction of each player's aim
    const int numPlayers = 3;
    for (int i = 0; i < numPlayers; i++) {
      float angle = (360.0 - targetyaw) * (M_PI / 180.0); // Replace this with the actual yaw of the player, then convert it to radians.
      ImVec2 endpoint(center.x + radius * cos(angle), center.y + radius * sin(angle));
      ImGui::GetWindowDrawList()->AddLine(center, endpoint, colOutline);
    }
  }
};
