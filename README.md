# xap-client  [LINUX]
**Updated to Game Version v3.0.53.30 (16.01.24)**

By **Gerosity**

All credits to original owners

Instructions down below

# Changelog:

    Updated Offsets - UC Forum
    Aimbot:
       - Keybind & Extra Keybind (If you want aimbot to be on left + right click)
       - Select Bone (Head, Neck, Upper Chest, Lower Chest, Stomach, Hip)
       - Select Weapons (e.g. only aim with R-99)
    Triggerbot:
       - Keybind (Hold to enabled)
       - Always On (Ignores keybind, always on)
       - Select Weapons (e.g. only with snipers)
    Sense/ESP:
       - Color Picker (Change Visible & Invisible colors for most features)
       - Visibile Only (Only draws ESP on those who are visible)
       - Draw Team (Displays ESP on teammates)
           - Draw Team Names
       - Tracer Screen Position (Where tracers start e.g. Top, Middle (Crosshair), Bottom)
       - Tracer Bone Position (Where tracers goto/end e.g. Top (Head), Bottom)
       - Thickness Slider
           - For Box, Tracers, Skeleton, FOV Circle, Crosshair
       - Crosshair
           - Color, Size, Thickness
    Misc:
       - Team Gamemode (Enable for BR, Gun Run or Training. Disable for Control or TDM)
       - Superglide [!]
           - Works (most) of the time, freezes overlay until space is no longer held down (Needs Fix)
    Menu:
       - Layout (Simple or Compact)


# ToDo List:
    Multi-Monitor Support (? / ✅) 
       - Doesnt work for me but others have said it works. Needs testing
    Aimbot:
       - Visibility Check
    Triggerbot:
       - Crash fix
       - Hitbox Select (e.g. only shoot if on head)
    ESP/Sense:
       - Filled FOV
       - Filled Box ESP (?) 
       - Health/Shield Bar ESP
       - Weapon ESP
       - Deathbox ESP
       - Item ESP
     Themes:
       - Change Theme (Change menu theme (Style, Colors) 




xap-client UC Link: https://www.unknowncheats.me/forum/apex-legends/606842-xap-client-aimbot-esp-triggerbot.html

# Original README.md
So yeah, this thing was made by me, I was very bored so I took T_Tape's Menu and grinder's features and put them together to create this monstrosity. The code is still very messy so if you want to improve it, go ahead.
I'll will be very grateful if you do so.

**Disclaimer: This code is for educational purposes only .**

# Credits
arturzxc: for the features (ESP, Triggerbot, Aimbot) and X11Display's XTestFakeRelativeMotionEvent

Koelion (Braziliana): menu, aimbot calculations

unguhelvu : Seer-Styled ESP

unknowncheats: basic knowledge and offsets


# Previews

![enter image description here](https://i.imgur.com/7mVlPrr.png)

# Installation
**1.Install dependencies**

    sudo apt-get install -y libudev-dev
    sudo apt install cmake xorg-dev libglu1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
    sudo apt-get install build-essential
    sudo apt-get install libx11-dev
    sudo apt-get install libxtst-dev

**2.Build glfw**

    git clone https://github.com/glfw/glfw.git
    cd glfw
    mkdir build
    cd build
    cmake ..
    make
    sudo make install

**3. Clone repo**

    git clone https://github.com/Gerosity/zap-client.git
    cd xap-client-v3.0.53.30

**4. Build and Run**

    mkdir build
    cd build
    cmake ..
    make
    sudo ./zapclient
    
**5. Press Insert to toggle the Menu (You can only interact with the Menu and the game when the menu is active).**
