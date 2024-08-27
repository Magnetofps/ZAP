# THIS CHEAT IS BEING SOLD AS "PremiumX"
# DO NOT BUY IT, IT'S A SCAM.

# ⚡ ZAP
hir0xygen's fork of zap-client by Gerosity,Maintained by Magneto | an Apex Legends external for Linux (X11).

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

## :card_file_box: Installation
<details>
<summary><b>View installation guide</b></summary>

It's recommended you use GNOME or Cinnamon as your desktop environment, though others might work.
KDE Plasma is known not to allow the overlay to be drawn above the game.

**1. Install dependencies**

sudo apt-get install -y libudev-dev
sudo apt install cmake xorg-dev libglu1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
sudo apt install -y libudev-dev libglu1-mesa-dev libxkbcommon-dev libwayland-dev git cmake g++ gcc libinput-dev libsoil-dev
sudo apt-get install build-essential
sudo apt-get install libx11-dev
sudo apt-get install libxtst-dev

**2. Build glfw**

    git clone https://github.com/glfw/glfw.git
    cd glfw
    mkdir build
    cd build
    cmake ..
    make
    sudo make install

**3. Navigate to directory for cheat files (I use `/Documents/development/` for example)**

    cd ~

**4. Clone repo**

    git clone https://github.com/Magnetofps/ZAP.git
    cd ZAP

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
