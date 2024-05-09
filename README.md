# ⚡ ZAP
hir0xygen's fork of zap-client by Gerosity, an Apex Legends external for Linux (X11).

![](https://i.imgur.com/4bwo36x.png)

## :page_facing_up: Features
    Combat:
        - Aimbot
        - Recoil control
        - Triggerbot
    Visuals:
        - Player glow
        - Item glow
        - ESP
        - Crosshair
        - Radar
    Misc
        - Movement
        - Auto shoot
        - Skin changer
    Config system

<details>
<summary><b>:memo: Changelog</b></summary>

    v1.0.8 - 10th May 2024
        - Menu styling changes
        - Removed rage bot and flick bot
        - Removed legit bot weapon config (might rewrite)
        - Removed additional legit bot modes, more follow up soon
        - Fixed all menu key issues preventing from launching

    v1.0.7c - 30th April 2024
        - Added game framerate to watermark

    v1.0.7b - 29th April 2024
        - Now spawns on primary monitor, at maximum refresh rate for that monitor
        - Now caps to the primary monitors refresh rate by default
        - Fixed trigger bot hip fire range not saving in config

    v1.0.7 - 28th April 2024
        - Changed game version check to scan all existing Steam libraries
        - Split trigger bot range in independent ADS/hip fire options
        - Removed sub-tabs in "MISC" tab, instead moved it into separate containers
        - Menu style changes

    v1.0.6b - 22nd April 2024
        - Forked from zap-client by Gerosity
        - Redesigned console output
        - Removed "cool" looking delays in run.sh and initialization (was annoying)

    view changelog for prior versions at Gerosity/zap-client
</details>

## :card_file_box: Installation
<details>
<summary><b>View installation guide</b></summary>

It's recommended you use GNOME or Cinnamon as your desktop environment, though others might work.
KDE Plasma is known not to allow the overlay to be drawn above the game.

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

**3. Navigate to directory for cheat files (I use `/Documents/development/` for example)**

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

**6. Press insert to toggle the menu (you can only interact with the menu and the game when the menu is active)**
**Note: You will need to tab between the cheat overlay and Apex**  
**If the overlay is not vertically aligned correctly (watermark is not all the way in the top-left corner, ESP misaligned), you can hold SUPER + Left-Mouse-Button and then drag it upwards on most desktop environments.**
</details>

### Other repositories
[Read-only version](https://github.com/Gerosity/zap-client-Read-Only-): a memory-read-only version of zap-client by Gerosity  
[Protection guide](https://github.com/Gerosity/Apex-Protection): a protection guide, not necessary but recommended

### Previews
https://www.youtube.com/watch?v=VBnAyOhTSIs  
https://www.youtube.com/watch?v=vCsmewJlgk0

### Credits
    https://github.com/Gerosity/zap-client              - parent of hir0xygen's fork
    https://github.com/Nexilist/xap-client              - for the base, massive credits to them
    https://github.com/arturzxc/grinder                 - alternate aimbot mode, most of the misc features
    https://github.com/Braziliana/T_TApe                - custom config system
    https://www.unknowncheats.me/forum/apex-legends/    - A TON of help, offsets, many additional features & more
    wafflesgaming                                       - aimbot help, Extra ESP Features such as 2D Corners
    0xAgartha & ghostrazzor                             - run.sh script (hide PID & random binary title)
