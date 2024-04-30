// Externals
#pragma once
#include <chrono>
#include <thread>
#include <string>
#include <cstdio>
#include <ctime>
#include <random>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#define GLFW_EXPOSE_NATIVE_X11
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

// Internals
#include "Font.hpp"
#include "../Utils/InputManager.hpp"
#include "../Utils/Features.hpp"

class Overlay {
private:
  GLFWwindow *OverlayWindow = nullptr;
  const GLFWvidmode *vidMode = nullptr;
  int ScreenWidth = 0;
  int ScreenHeight = 0;
  int ScreenPosX = 0;
  int ScreenPosY = 0;

  void GrabScreenSize() {
    GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
    vidMode = glfwGetVideoMode(primaryMonitor);
    glfwGetMonitorPos(primaryMonitor, &ScreenPosX, &ScreenPosY);
    ScreenWidth = vidMode->width;
    ScreenHeight = vidMode->height;
  }

  static std::string RandomString(std::string::size_type length) {
    static auto &chrs = "0123456789" "abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    thread_local static std::mt19937 rg{std::random_device{}()};
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

    std::string s;

    s.reserve(length);

    while (length--)
      s += chrs[pick(rg)];

    return s;
  }

  static int RandomInt(const int min, const int max) {
    srand(time(nullptr)); //seeding for the first time only! NOLINT(*-msc51-cpp)
    return min + rand() % ((max + 1) - min); // NOLINT(*-msc50-cpp)
  }

  static void GLFWErrorCallback(const int error, const char *description) { fprintf(stderr, "GLFW Error %d: %s\n", error, description); }

  static long long CurrentEpochMilliseconds() {
    const auto currentTime = std::chrono::system_clock::now();
    const auto duration = currentTime.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  }

  static ImWchar *GetFontGlyphRanges() noexcept {
    static ImVector<ImWchar> ranges;
    if (ranges.empty()) {
      ImFontGlyphRangesBuilder builder;
      constexpr ImWchar baseRanges[] = {
        0x0100, 0x024F, // Latin Extended-A + Latin Extended-B
        0x0300, 0x03FF, // Combining Diacritical Marks + Greek/Coptic
        0x0600, 0x06FF, // Arabic
        0x0E00, 0x0E7F, // Thai
        0
      };
      builder.AddRanges(baseRanges);
      builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
      builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesDefault());
      builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
      builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesChineseSimplifiedCommon());
      // ★龍王™
      builder.AddChar(u'\u2605'); // ★
      builder.AddChar(u'\u9F8D'); // 龍
      builder.AddChar(u'\u738B'); // 王
      builder.AddChar(u'\u2122'); // ™
      builder.BuildRanges(&ranges);
    }
    return ranges.Data;
  }

public:
  int ProcessingTime;
  long long StartTime;
  int SleepTime;
  int TimeLeftToSleep;

  int AsciiArt = 5;
  int AsciiArtSpeed = 100;
  int ThemeStyle;
  int ThemeColor;
  bool TeamGamemode = true;
  bool ErrorLogging = false;

  bool InitializeOverlay() {
    glfwSetErrorCallback(GLFWErrorCallback);
    if (!glfwInit()) { return false; }

    GrabScreenSize();

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE); // why was refresh rate previously forced to 75Hz? GLFW kindly allows us to say I DONT CARE!!!

    OverlayWindow = glfwCreateWindow(ScreenWidth, ScreenHeight, RandomString(RandomInt(10, 20)).c_str(), nullptr, nullptr);

    CaptureInput(true);
    glfwMakeContextCurrent(OverlayWindow);

    glfwSetWindowPos(OverlayWindow, ScreenPosX, ScreenPosY);

    InitializeUI();

    glfwShowWindow(OverlayWindow);
    glfwSwapInterval(0);

    return true;
  }

  void InitializeUI() const {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImFontConfig cfg;
    /*cfg.OversampleH = cfg.OversampleV = 1;
    cfg.PixelSnapH = true;
    cfg.SizePixels = 13.0f;
    cfg.GlyphOffset = {1.0f, -1.0f};*/
    cfg.OversampleH = cfg.OversampleV = 1;
    cfg.PixelSnapH = false;
    cfg.SizePixels = 13.0f; // 13.0f
    cfg.GlyphOffset = {0.0f, 0.0f};
    const ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.Fonts->AddFontFromMemoryCompressedTTF(_compressedFontData, _compressedFontSize, cfg.SizePixels, &cfg, GetFontGlyphRanges());

    ImGui::StyleColorsDark();
    ImGuiStyle &style = ImGui::GetStyle();

    style.SliderThickness = 0.2f;
    style.SliderContrast = 0.5f;
    style.SliderValuePos = ImVec2(1.0f, 2.2f);
    style.WindowPadding = ImVec2(8.00f, 8.00f);
    style.FramePadding = ImVec2(5.00f, 2.00f);
    style.CellPadding = ImVec2(6.00f, 6.00f);
    style.ItemSpacing = ImVec2(6.00f, 6.00f);
    style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
    style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
    style.IndentSpacing = 25;
    style.ScrollbarSize = 12;
    style.GrabMinSize = 10;
    style.WindowBorderSize = 1;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 1;
    style.FrameBorderSize = 1;
    style.TabBorderSize = 1;
    style.WindowRounding = 7;
    style.ChildRounding = 4;
    style.FrameRounding = 3;
    style.PopupRounding = 4;
    style.ScrollbarRounding = 9;
    style.GrabRounding = 3;
    style.LogSliderDeadzone = 4;
    style.TabRounding = 4;

    style.Colors[ImGuiCol_Text] = ImVec4(0.900000f, 0.900000f, 0.900000f, 1.000000f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.600000f, 0.600000f, 0.600000f, 1.000000f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.058824f, 0.058824f, 0.058824f, 1.000000f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.000000f, 0.000000f, 0.000000f, 0.000000f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(57 / 255.f, 57 / 255.f, 57 / 255.f, 1);
    style.Colors[ImGuiCol_Border] = ImVec4(0.500000f, 0.500000f, 0.500000f, 0.500000f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.000000f, 0.000000f, 0.000000f, 0.000000f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.430000f, 0.430000f, 0.430000f, 0.390000f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.470000f, 0.470000f, 0.690000f, 0.400000f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.420000f, 0.410000f, 0.640000f, 0.690000f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.270000f, 0.270000f, 0.540000f, 0.830000f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.320000f, 0.320000f, 0.630000f, 0.870000f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.400000f, 0.400000f, 0.800000f, 0.200000f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.400000f, 0.400000f, 0.550000f, 0.800000f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.200000f, 0.250000f, 0.300000f, 0.000000f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.400000f, 0.400000f, 0.400000f, 0.300000f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.400000f, 0.400000f, 0.400000f, 0.400000f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.400000f, 0.400000f, 0.400000f, 0.600000f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.900000f, 0.900000f, 0.900000f, 0.500000f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.000000f, 1.000000f, 1.000000f, 0.300000f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.410000f, 0.390000f, 0.800000f, 0.600000f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.350000f, 0.400000f, 0.610000f, 0.620000f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.400000f, 0.480000f, 0.710000f, 0.790000f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.460000f, 0.540000f, 0.800000f, 1.000000f);
    style.Colors[ImGuiCol_Header] = ImVec4(45 / 255.f, 45 / 255.f, 45 / 255.f, 1);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(50 / 255.f, 50 / 255.f, 50 / 255.f, 1);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(45 / 255.f, 45 / 255.f, 45 / 255.f, 1);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.500000f, 0.500000f, 0.500000f, 0.600000f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.600000f, 0.600000f, 0.700000f, 1.000000f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.700000f, 0.700000f, 0.900000f, 1.000000f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.000000f, 1.000000f, 1.000000f, 0.160000f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.780000f, 0.820000f, 1.000000f, 0.600000f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.780000f, 0.820000f, 1.000000f, 0.900000f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.000000f, 0.000000f, 1.000000f, 0.350000f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.000000f, 1.000000f, 0.000000f, 0.900000f);

    ImGui_ImplGlfw_InitForOpenGL(OverlayWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
  }

  static bool AlignedButton(const char *label, const float alignment = 0.5f) {
    const ImGuiStyle &style = ImGui::GetStyle();

    const float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
    const float avail = ImGui::GetContentRegionAvail().x;

    if (const float off = (avail - size) * alignment; off > 0.0f)
      ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

    return ImGui::Button(label);
  }

  void DestroyOverlay() const {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (OverlayWindow != nullptr) { glfwDestroyWindow(OverlayWindow); }

    glfwTerminate();
  }

  void CaptureInput(const bool capture) const { glfwSetWindowAttrib(OverlayWindow, GLFW_MOUSE_PASSTHROUGH, capture ? GLFW_FALSE : GLFW_TRUE); }

  void FocusOverlay() const { glfwFocusWindow(OverlayWindow); }

  void Start(void (*Update)(), void (*RenderUI)()) {
    while (!glfwWindowShouldClose(OverlayWindow)) {
      StartTime = CurrentEpochMilliseconds();
      glfwPollEvents();
      glViewport(0, 0, ScreenWidth, ScreenHeight);
      glClearColor(0, 0, 0, 0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, ScreenWidth, ScreenHeight, 0, -1, 1);

      if (Update != nullptr)
        Update();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      if (RenderUI != nullptr)
        RenderUI();

      // Render ImGui and swap buffers
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      glfwSwapBuffers(OverlayWindow);

      ProcessingTime = static_cast<int>(CurrentEpochMilliseconds() - StartTime);
      SleepTime = 1000 / vidMode->refreshRate; // 165 = ~6ms, 144 = ~7ms, 60 = ~16ms
      if (!Features::Settings::FPSCap)
        TimeLeftToSleep = std::max(0, SleepTime - ProcessingTime);

      if (Features::Settings::FPSCap)
        TimeLeftToSleep = 1000 / Features::Settings::CappedFPS;

      std::this_thread::sleep_for(std::chrono::milliseconds(TimeLeftToSleep));
    }

    DestroyOverlay();
  }

  void GetScreenResolution(int &Width, int &Height) const {
    Width = ScreenWidth;
    Height = ScreenHeight;
  }
};
