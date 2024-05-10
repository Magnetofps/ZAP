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
#include "IconsFontAwesome5.h"
#include "Fontawesome.hpp"
#include "../Utils/InputManager.hpp"
#include "../Utils/Features.hpp"


class Overlay {
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

  static ImVec4 HEXTOIV4(const std::string& hex) {
    if (hex.length() != 8) {
      std::cerr << "Invalid hexadecimal color code: " << hex << std::endl;
      return {0.0f, 0.0f, 0.0f, 1.0f}; // Default to black with full opacity
    }

    const unsigned int colorValue = std::stoul(hex, nullptr, 16);
    return {(colorValue >> 24 & 0xFF) / 255.0f, (colorValue >> 16 & 0xFF) / 255.0f, (colorValue >> 8 & 0xFF) / 255.0f, (colorValue & 0xFF) / 255.0f
    };
  }

public:
  int ProcessingTime{};
  long long StartTime{};
  int SleepTime{};
  int TimeLeftToSleep{};

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
    cfg.OversampleH = cfg.OversampleV = 1;
    cfg.PixelSnapH = false;
    cfg.SizePixels = 13.0f; // 13.0f
    cfg.GlyphOffset = {0.0f, 0.0f};
    const ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.Fonts->AddFontFromMemoryCompressedTTF(compressedFontData, compressedFontSize, cfg.SizePixels, &cfg, GetFontGlyphRanges());

    static constexpr ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_16_FA, 0};
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.GlyphMinAdvanceX = 32.0f;
    io.Fonts->AddFontFromMemoryCompressedTTF(fontAwesome900_compressed_data, fontAwesome900_compressed_size, 32.0f, &icons_config, icons_ranges);

    ImGui::StyleColorsDark();
    ImGuiStyle &style = ImGui::GetStyle();

    style.Colors[ImGuiCol_Text] = HEXTOIV4("f0f0f0ff");           // all text
    style.Colors[ImGuiCol_WindowBg] = HEXTOIV4("0d0d0dff");          // entire background
    style.Colors[ImGuiCol_MenuBarBg] = HEXTOIV4("ffffffff");
    style.Colors[ImGuiCol_Border] = HEXTOIV4("ffffffff");
    style.Colors[ImGuiCol_BorderShadow] = HEXTOIV4("ffffffff");
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.10f);             // frame background
    style.Colors[ImGuiCol_FrameBgHovered] = HEXTOIV4("ffffffff");  // frame bg hovered
    style.Colors[ImGuiCol_FrameBgActive] = HEXTOIV4("ffffffff");   // frame background active??
    style.Colors[ImGuiCol_CheckMark] = HEXTOIV4("ffffffff");       // checkbox checkmark
    style.Colors[ImGuiCol_Button] = HEXTOIV4("57606fff");          // button
    style.Colors[ImGuiCol_ButtonHovered] = HEXTOIV4("57606f80");   // button hovered
    style.Colors[ImGuiCol_ButtonActive] = HEXTOIV4("57606fff");    // button clicked

    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.7f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.48f, 0.48f, 0.48f, 0.7f);

    // BG: 2f3542ff
    // buttons: 57606fff
    // accent: ffa502ff
    // border: 747d8cff

    style.WindowPadding = ImVec2(4.00f, 4.00f);
    style.FramePadding = ImVec2(5.00f, 2.00f);
    style.CellPadding = ImVec2(6.00f, 6.00f);
    style.ItemSpacing = ImVec2(4.00f, 4.00f);
    style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
    style.WindowRounding = 7;
    style.ChildRounding = 4;
    style.FrameRounding = 7;

    ImGui_ImplGlfw_InitForOpenGL(OverlayWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
  }

  void DestroyOverlay() const {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (OverlayWindow != nullptr) { glfwDestroyWindow(OverlayWindow); }

    glfwTerminate();
  }

  void CaptureInput(const bool capture) const { glfwSetWindowAttrib(OverlayWindow, GLFW_MOUSE_PASSTHROUGH, capture ? GLFW_FALSE : GLFW_TRUE); }

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
