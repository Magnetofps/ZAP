# ⚡ ZAP
hir0xygen's fork of zap-client by Gerosity, an Apex Legends external for Linux (X11).

![](https://i.imgur.com/0bNmJQj.png)

## Features
    Legitbot - Aimbot, RCS
    Ragebot - Aimbot, RCS
    Flickbot
    Triggerbot
    Glow - Player, Viewmodel & Item
    ESP - Enemy & Teammate, Spectator List, Crosshair, Radar
    Misc - Movement, Camera (Quick Turn), Rapid Fire (For Semi-Auto & Burst Weapons), Skin Changer (Basic, not to be confused with a model changer)
    Settings - Gamemode Switcher, Disable Overlay, Disable ESP, FPS Cap
    Configs - Custom Configs

<details>
<summary><b>Changelog</b></summary>

    v1.0.6b - 22nd April 2024
        Forked from zap-client by Gerosity
        Reformatted codebase
        Redesigned console output
        General code cleanup (got rid of some if-else chains)
        Removed "cool" looking delays in run.sh and initialization (was annoying)

    view changelog for prior versions at Gerosity/zap-client
</details>

## Installation
<details>
<summary><b>View installation guide</b></summary>

**1. Install dependencies**

    sudo apt install git cmake g++ gcc xorg-dev libudev-dev libglu1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libxkbcommon-dev libwayland-dev libinput-dev libsoil-dev build-essential libx11-dev libxtst-dev

**2. Build glfw**

    git clone https://github.com/glfw/glfw.git
    cd glfw
    mkdir build
    cd build
    cmake ..
    make
    sudo make install

**3. Navigate to directory for cheat files (I use /Documents/development/ for example)**

    cd ~/Documents/

**4. Clone repo**

    git clone https://github.com/hir0xygen/zap-client.git
    cd zap-client

**5. Build & Run**

    mkdir build
    cd build
    cmake ..
    make
    chmod +x run.sh
    ./run.sh

**6. Press insert to toggle the nenu (you can only interact with the nenu and the game when the menu is active)**
**Note: You will need to tab between the cheat overlay and Apex**
</details>

### Other repositories
[Read-only version](https://github.com/Gerosity/zap-client-Read-Only-): a memory-read-only version of zap-client by Gerosity
[Protection guide](https://github.com/Gerosity/Apex-Protection): a protection guide, not necessary but recommended

### Previews
https://www.youtube.com/watch?v=VBnAyOhTSIs
https://www.youtube.com/watch?v=vCsmewJlgk0

### Credits
    https://github.com/Gerosity/zap-client - parent of hir0xygen's fork
    https://github.com/Nexilist/xap-client - for the base, massive credits to them
    https://github.com/arturzxc/grinder - alternate aimbot mode, most of the misc features
    https://github.com/Braziliana/T_TApe - custom config system
    https://www.unknowncheats.me/forum/apex-legends/ - A TON of help, offsets, many additional features & more
    wafflesgaming - aimbot help, Extra ESP Features such as 2D Corners
    0xAgartha & ghostrazzor - run.sh script (Randomises zapclient binary & Hides PID before execution)
