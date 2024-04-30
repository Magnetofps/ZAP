#include <iostream>
#include <string>
#include <unistd.h>
#include <atomic>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdlib>
#include <pwd.h>

#include "Core/Level.hpp"
#include "Core/Player.hpp"
#include "Core/LocalPlayer.hpp"
#include "Core/Camera.hpp"

#include "Features/Legitbot.hpp"
#include "Features/Ragebot.hpp"
#include "Features/Sense.hpp"
#include "Features/Radar.hpp"
#include "Features/Flickbot.hpp"
#include "Features/Triggerbot.hpp"
#include "Features/Misc.hpp"
#include "Features/Glow.hpp"

#include "Overlay/Overlay.hpp"
#include "Overlay/GUI.hpp"

#include "Utils/ConfigManager.hpp"
#include "Utils/Features.hpp"
#include "Utils/Memory.hpp"
#include "Utils/XDisplay.hpp"
#include "Utils/termcolor.hpp"

namespace tc = termcolor;

// Objects
XDisplay *X11Display = new XDisplay();
Overlay OverlayWindow = Overlay();
ImDrawList *Canvas;

// Game Objects
Level *Map = new Level();
LocalPlayer *Myself = new LocalPlayer();
Camera *GameCamera = new Camera();

// Players
std::vector<Player *> *HumanPlayers = new std::vector<Player *>;
std::vector<Player *> *Dummies = new std::vector<Player *>;
std::vector<Player *> *Players = new std::vector<Player *>;

// Features
Sense *ESP = new Sense(Map, Players, GameCamera, Myself, X11Display);
Radar *MapRadar = new Radar(X11Display, Players, GameCamera, Map, Myself);
Glow *GlowESP = new Glow(Map, Players, GameCamera, Myself);
Legitbot *Legit = new Legitbot(X11Display, Map, Myself, Players);
Ragebot *Rage = new Ragebot(X11Display, Map, Myself, Players);
Triggerbot *Trigger = new Triggerbot(X11Display, Map, Myself, Players);
Flickbot *Flick = new Flickbot(X11Display, Map, Myself, Players);
Misc *MiscTab = new Misc(X11Display, Map, Myself, Players);
Overlay *Home = new Overlay;
AdvancedGUI *Advanced = new AdvancedGUI;
Menu *GUI = new Menu(Myself, Advanced);
ConfigManager *Configs = new ConfigManager(Legit, Rage, Flick, Trigger, GlowESP, ESP, MapRadar, MiscTab);

// Booleans and Variables
bool IsMenuOpened = true;

// Thread
std::atomic_bool StopThread(false);

// Inputs
void HandleKeyEvent(Display *display, XEvent *Event) {
  if (Event->type == KeyPress) {
    if (IsMenuOpened) {
      IsMenuOpened = false;
      Features::Home::IsMenuOpened = false;
      OverlayWindow.CaptureInput(false);
    } else {
      IsMenuOpened = true;
      Features::Home::IsMenuOpened = true;
      OverlayWindow.CaptureInput(true);
    }
  }
}

void X11EventListener() {
  Display *display = XOpenDisplay(nullptr);
  Window root = DefaultRootWindow(display);
  try { XGrabKey(display, XKeysymToKeycode(display, XK_Insert), AnyModifier, root, False, GrabModeAsync, GrabModeAsync); } catch (XErrorEvent) { std::cout << " ! >> Failed to grab insert key, is another application already using it?" << std::endl; }
  XEvent event;
  while (!StopThread) {
    XNextEvent(display, &event);
    HandleKeyEvent(display, &event);
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  XCloseDisplay(display);
}

// Overlay
bool InitializeOverlayWindow() {
  if (!OverlayWindow.InitializeOverlay()) {
    OverlayWindow.DestroyOverlay();
    return false;
  }
  int ScreenWidth;
  int ScreenHeight;
  OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);
  GameCamera->Initialize(ScreenWidth, ScreenHeight);
  return true;
}

// Interface
ImVec4 ProcessingTimeColor;

void CreateTabButton(const char* title, const Menu::MenuTabs tab, const ImVec2 size) {
  const ImVec4 BaseTabButton = ImVec4(GUI->DetailColor.x, GUI->DetailColor.y, GUI->DetailColor.z, 0.00f);
  const ImVec4 BaseTabButtonActive = ImVec4(GUI->DetailColor.x, GUI->DetailColor.y, GUI->DetailColor.z, 0.250f);
  ImGui::PushStyleColor(ImGuiCol_Button, (GUI->CurrentTab == tab) ? BaseTabButtonActive : BaseTabButton);
  if (ImGui::Button(title, size)) {
    GUI->CurrentTab = tab;
  }
  ImGui::PopStyleColor(1);
}

void RenderUI() {
  const auto io = ImGui::GetIO();
  ImGui::SetNextWindowSize(io.DisplaySize);
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::Begin("##Overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground | ImGuiSliderFlags_AlwaysClamp);
  Canvas = ImGui::GetWindowDrawList();
  // if (Map->IsPlayable)
  MapRadar->RenderDrawings(Canvas, Myself, OverlayWindow);
  ESP->RenderWatermark(Canvas, Myself, OverlayWindow);
  ESP->RenderDrawings(Canvas, Legit, Myself, OverlayWindow);
  ImGui::End();

  if (!Features::Home::IsMenuOpened)
    return;

  // Window Size
  ImGui::SetNextWindowSizeConstraints(ImVec2(GUI->WindowWidth, GUI->WindowHeight), ImVec2(GUI->WindowWidth, GUI->WindowHeight));
  ImGui::SetNextWindowSize(ImVec2(GUI->WindowWidth, GUI->WindowHeight), ImGuiCond_FirstUseEver);

  if (ImGui::Begin("##CheatGUI", &Features::Home::IsMenuOpened, GUI->WindowFlags)) {
    const ImVec2 MenuSize = ImGui::GetWindowSize();

    // Render Left Panel
    ImGui::SetCursorPos(ImVec2(10, 32));

    ImVec4 *colors = ImGui::GetStyle().Colors;

    colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    if (ImGui::BeginChild("##LeftPanel", ImVec2(GUI->WindowWidth / 6 - 5, GUI->WindowHeight - 43), true, ImGuiWindowFlags_NoScrollbar)) {
      // Color the background of the tab button brighter if it is the active tab
      const ImVec4 BaseTabButton = ImVec4(GUI->DetailColor.x, GUI->DetailColor.y, GUI->DetailColor.z, 0.00f);
      const ImVec4 BaseTabButtonActive = ImVec4(GUI->DetailColor.x, GUI->DetailColor.y, GUI->DetailColor.z, 0.250f);

      ImGuiStyle &Style = ImGui::GetStyle();
      constexpr int ButtonHeight = 43;
      Style.FrameBorderSize = 1;

      colors[ImGuiCol_ButtonHovered] = BaseTabButtonActive;
      colors[ImGuiCol_ButtonActive] = BaseTabButtonActive;
      colors[ImGuiCol_Button] = BaseTabButton;
      colors[ImGuiCol_Text] = GUI->TextColor;

      CreateTabButton("LEGITBOT", Menu::Legitbot, ImVec2(MenuSize.x / 6 - 35, ButtonHeight));
      CreateTabButton("RAGEBOT", Menu::Ragebot, ImVec2(MenuSize.x / 6 - 35, ButtonHeight));
      CreateTabButton("FLICKBOT", Menu::Flickbot, ImVec2(MenuSize.x / 6 - 35, ButtonHeight));
      CreateTabButton("TRIGGERBOT", Menu::Triggerbot, ImVec2(MenuSize.x / 6 - 35, ButtonHeight));
      CreateTabButton("GLOW", Menu::Glow, ImVec2(MenuSize.x / 6 - 35, ButtonHeight));
      CreateTabButton("ESP", Menu::ESP, ImVec2(MenuSize.x / 6 - 35, ButtonHeight));
      CreateTabButton("MISC", Menu::Misc, ImVec2(MenuSize.x / 6 - 35, ButtonHeight));
      CreateTabButton("SETTINGS", Menu::Settings, ImVec2(MenuSize.x / 6 - 35, ButtonHeight));
      CreateTabButton("CONFIGS", Menu::Config, ImVec2(MenuSize.x / 6 - 35, ButtonHeight));

      ImGui::EndChild();
    }

    std::stringstream MenuTitle;
    MenuTitle << ZAP_VERSION << " for Apex " << GAME_VERSION;
    const ImVec2 WindowPosition = ImGui::GetWindowPos();
    const auto TextPosition = WindowPosition.x + GUI->WindowWidth / 2;
    const auto TextSize = ImGui::CalcTextSize(MenuTitle.str().c_str()).x;
    ImGui::GetForegroundDrawList()->AddText(ImVec2(TextPosition - TextSize / 2, WindowPosition.y + 10), ImColor(1.0, 1.0f, 1.0f, 1.0f), MenuTitle.str().c_str());

    // Render Right (Main) Panel
    ImGui::SetCursorPos(ImVec2(175, 32));
    colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    if (ImGui::BeginChild("##RightPanel", ImVec2(GUI->WindowWidth - 186, GUI->WindowHeight - 43), true, ImGuiWindowFlags_NoScrollbar)) {
      colors[ImGuiCol_Border] = GUI->DetailColor;
      // Render Tabs
      switch (GUI->CurrentTab) {
        case GUI->MenuTabs::Legitbot:
          GUI->RenderLegitbot();
          break;
        case GUI->MenuTabs::Ragebot:
          GUI->RenderRagebot();
          break;
        case GUI->MenuTabs::Flickbot:
          GUI->RenderFlickbot();
          break;
        case GUI->MenuTabs::Triggerbot:
          GUI->RenderTriggerbot();
          break;
        case GUI->MenuTabs::Glow:
          GUI->RenderGlow();
          break;
        case GUI->MenuTabs::ESP:
          GUI->RenderESP(OverlayWindow);
          break;
        case GUI->MenuTabs::Misc:
          GUI->RenderMisc();
          break;
        case GUI->MenuTabs::Settings:
          GUI->RenderSettings();
          break;
        case GUI->MenuTabs::Config:
          ImVec2 TabSize;
          TabSize = ImGui::GetWindowSize();
          ImGui::SetCursorPos(ImVec2(0, 0));
          ImGui::BeginChild("workzone", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
          ImGui::SetCursorPos({15, 15});
          ImGui::BeginChild("workzone", ImVec2(GUI->WindowWidth - 186, GUI->WindowHeight - 60), false, ImGuiWindowFlags_NoScrollbar);
          ImGui::BeginChildFrame(1, ImVec2(GUI->WindowWidth - 220, GUI->WindowHeight - 73), true); {
            GUI->DoubleSpacing();
            Configs->LoadConfigs();
            Configs->RenderConfigs();
            ImGui::EndChildFrame();
          }
          ImGui::EndChild();
          ImGui::EndChild();
          break;
      }
      ImGui::EndChild();
      Legit->UpdateAimList();
      Legit->UpdateRCSList();
      Rage->UpdateRageList();
      Flick->UpdateFlickList();
      Trigger->UpdateWeaponList();
      MiscTab->UpdateRapidFireList();
    }

    // Add Vertical Separator Line
    const ImVec2 Window = ImGui::GetWindowPos();
    const ImVec2 Point1 = ImVec2(MenuSize.x / 6 + 6.5f + Window.x, 32 + Window.y);
    const ImVec2 Point2 = ImVec2(MenuSize.x / 6 + 6.5f + Window.x, 32 + (MenuSize.y - 43) + Window.y);
    ImGui::GetWindowDrawList()->AddLine(Point1, Point2, ImGui::ColorConvertFloat4ToU32(GUI->DetailColor), 1.0f);

    // End Drawlist Calls
    ImGui::End();
  }
}

// Core
void UpdateCore() {
  try {
    Map->Read();
    if (!Map->IsPlayable)
      return;

    Myself->Read();
    if (!Myself->IsValid())
      return;

    Players->clear();
    if (Map->IsFiringRange) {
      for (auto p : *Dummies) {
        p->Read();
        if (p->BasePointer != 0 && (p->IsPlayer() || p->IsDummy()))
          Players->push_back(p);
      }
    } else {
      for (auto p : *HumanPlayers) {
        p->Read();
        if (p->BasePointer != 0 && (p->IsPlayer() || p->IsDummy()))
          Players->push_back(p);
      }
    }

    // Updates //
    GameCamera->Update();
    GlowESP->Update();
    GlowESP->ViewModelGlow();
    Legit->UpdateAimbot();
    Legit->UpdateRCS();
    Rage->Update();
    Trigger->Update();
    Flick->Update();
    MiscTab->Update();
    MapRadar->ActivateBigMap();

  } catch (const std::exception &ex) {
    std::system("clear");
    std::cout << "Error: " << ex.what() << std::endl;
  }
}

void MiscThreadRun() {
  while (!StopThread) {
    if (!Map->IsPlayable) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      continue;
    }

    if (!Myself->IsValid()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      continue;
    }

    if (Features::Misc::SuperGlide)
      MiscTab->SuperGlide();

    if (Features::Misc::BHop)
      MiscTab->BHop();

    if (Features::Misc::QuickTurn)
      MiscTab->QuickTurn();

    if (Features::Misc::RapidFire)
      MiscTab->RapidFire();
  }
}

std::string slurpFile(const std::string& absolutePath) {
  std::string contents;
  std::ifstream file;
  file.open(absolutePath, std::ios::in);

  if (file.fail()) {
    return contents;
  }

  char c;
  while (file.get(c)) {
    contents += c;
  }

  file.close();
  std::erase(contents, '\n');
  return contents;
}

bool isOutdated() { // Scan possible Steam installation paths for libraryfolders.vdf to then scan existing library folders for the games "gameversion.txt"
  // Get currently logged in user, since getuid won't work when we're run as root
  struct passwd *pw;
  const char* username = nullptr;
  while ((pw = getpwent()) != nullptr) {
    if (strncmp(pw->pw_dir, "/home/", 6) == 0) {
      username = pw->pw_name;
      break;
    }
  }
  endpwent();

  if (username == nullptr)
    return true;

  const std::string steamPaths[] = {
    "/.steam/steam/config/libraryfolders.vdf",
    "(/.local/share/Steam/config/libraryfolders.vdf",
    "/.var/app/com.valvesoftware.Steam/data/Steam/config/libraryfolders.vdf"
  };

  std::vector<std::string> extractedPaths;
  for (const auto & steamPath : steamPaths) {
    std::stringstream fullPath;
    fullPath << "/home/" << username << steamPath;

    std::string libraryfolders = slurpFile(fullPath.str());
    size_t currentPos = 0;
    while (true) {
      const size_t pathPos = libraryfolders.find("path", currentPos);

      if (pathPos == std::string::npos)
        break;

      const size_t pathStart = pathPos + 8;
      const size_t pathEnd = libraryfolders.find('"', pathStart);

      if (pathEnd != std::string::npos) {
        std::string extractedPath = libraryfolders.substr(pathStart, pathEnd - pathStart);
        std::stringstream finalPath;
        finalPath << extractedPath << R"(/steamapps/common/Apex Legends/gameversion.txt)";

        if (std::string version = slurpFile(finalPath.str()); version == GAME_VERSION) {
          return false;
        }
      }

      currentPos = pathEnd;
    }
  }

  return true;
}

// Main
int main(int argc, char *argv[]) {
  if (getuid()) {
    std::cout << tc::red << " ! >> Please run as root" << std::endl;
    return -1;
  }

  std::system("clear");

  std::cout << tc::color<255, 255, 0> << "\n       ____    __    ____ " << std::endl;
  std::cout << tc::color<255, 230, 0> << "      (_   )  /__\\  (  _ \\" << std::endl;
  std::cout << tc::color<255, 190, 0> << "       / /_  /(__)\\  )___/" << std::endl;
  std::cout << tc::color<255, 165, 0> << "      (____)(__)(__)(__)  \n" << tc::reset << std::endl;
  std::cout << tc::color<255, 100, 0> << "  ZAP " << ZAP_VERSION << " - hir0xygen's fork" << std::endl;
  std::cout << tc::color<133, 255, 133> << " ✔  " << tc::reset << ">> Apex Legends " << GAME_VERSION << std::endl;

  if (isOutdated()) {
    std::cout << tc::red << " ! " << tc::reset << " >> There has been a game update, or the version check failed" << std::endl;
    std::cout << tc::red << " ! " << tc::reset << " >> Continuing execution 3 seconds" << std::endl;
    sleep(3);
  } else {
    std::cout << tc::color<133, 255, 133> << " ✔  " << tc::reset << ">> Compatible game version installed" << std::endl;
  }

  if (Memory::GetPID() == 0) {
    std::cout << " ⚡ >> Waiting for Apex" << std::endl;
    while (Memory::GetPID() == 0) { std::this_thread::sleep_for(std::chrono::milliseconds(500)); }
  }

  std::cout << " ⚡ >> Apex is running" << std::endl;

  if (!InitializeOverlayWindow())
    return -1;

  std::cout << " ⚡ >> Overlay initialized" << std::endl;

  // Theading //
  std::thread X11Thread(X11EventListener);
  X11Thread.detach();
  std::thread InputManagerThread(InputManager::run);
  InputManagerThread.detach();
  std::thread MiscThread(MiscThreadRun);
  MiscThread.detach();

  // Initialize the whole process //
  try {
    for (int i = 0; i < 70; i++)
      HumanPlayers->push_back(new Player(i, Myself));

    for (int i = 0; i < 15000; i++) // 15000
      Dummies->push_back(new Player(i, Myself));

    std::cout << " ⚡ >> ZAP initialized" << std::endl;

    OverlayWindow.Start(&UpdateCore, &RenderUI);
    srand(static_cast<unsigned>(time(0)));
  } catch (...) {
  }

  StopThread = true;
  InputManager::StopThread = true;
  X11Thread.join();
  InputManagerThread.join();
  MiscThread.join();
  return 0;
};
