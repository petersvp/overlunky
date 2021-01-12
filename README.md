# Overlunky

An overlay for Spelunky 2 to help you with modding, exploring the depths of the game and practicing with tools like spawning arbitrary items, warping to levels and teleporting made by the cool people from the Spelunky Community Discord.

**Please read the [![open issues](https://img.shields.io/github/issues-raw/spelunky-fyi/overlunky)](https://github.com/spelunky-fyi/overlunky/issues) before complaining about them in the discord.**

[![Overlunky](https://img.shields.io/github/v/release/spelunky-fyi/overlunky?label=Overlunky)](https://github.com/spelunky-fyi/overlunky/releases/latest) is compatible with ![Spelunky](https://img.shields.io/badge/Spelunky2-1.20.0j-green).

## Disclaimer
You are strongly discouraged from using any modding tools in your actual online Steam installation as to prevent unlocking achievements, ruining or corrupting your savefile and cheating while using online features. You should make a copy of your game somewhere else and install [Mr. Goldbergs Steam Emulator](https://mr_goldberg.gitlab.io/goldberg_emulator/) in the game directory. (Just replace steam_api64.dll with the one in the zip and that copy of the game can't talk to Steam no more!) If you break anything using this tool you get to keep both pieces. Do not report modding related bugs to BlitWorks.

## Installation and usage
**[Download the latest release](https://github.com/spelunky-fyi/overlunky/releases/latest)** and extract anywhere. Run the program, leave it running and then start your game, or the other way around! Overlunky doesn't do any permanent changes to your game, it only exists when you run it.

Check the generated `Spelunky 2/hotkeys.ini` after running to change shortcut keys and check `Spelunky 2/entities.txt` for a list of numerical entity IDs.

## Features
Current features and their *default* keyboard shortcuts. Note: There's a LOT of useful keys that are not listed here because this list is getting pretty long, check your `hotkeys.ini` for cool beans.
  - **Enter**: Run active tool
  - **F1**: Search and spawn entities where you're standing
      + **Ctrl+Enter**: Spawn entity
      + **Tab**: Add selected itemid to list
      + **Mouse left**: Spawn entity at mouse cursor
      + **Mouse right**: Teleport to mouse cursor
      + **Mouse middle**: Drag entities around (not stuff like walls)
      + **Ctrl+Mouse middle**: Launch dragged entity with velocity
      + **Shift+Mouse middle**: Drag all entities around (even walls and background)
      + **(Ctrl/Shift+)Mouse 4**: Zap / Boom / Big Boom / Nuke!
      + **Mouse 5**: Destroy entity (not stuff like walls)
      + **Ctrl+Mouse 5**: Clone entity
      + **Shift+Mouse 5**: Destroy any entity (really unsafe :)
      + You can also draw a velocity vector for spawn/teleport by holding the mouse button
      + Dragged entities have noclip on, so you can drag yourself through walls etc
      + Enter multiple numeric IDs like `526 560 570` to spawn them all at once. Useful for making a kit you can just paste in.
  - **F2**: Spawn doors to many places
      + **Shift+Enter**: Spawn back layer door
      + **Ctrl+Shift+Enter**: Spawn warp door
  - **F3**: Camera controls
      + **Ctrl+,**: Zoom in
      + **Ctrl+.**: Zoom out
      + **Ctrl+0**: Auto fit level width to screen
      + **Ctrl+2345**: Zoom to X level width
  - **F9**: Options
      + **Ctrl+M**: Toggle mouse controls (spawn/teleport)
      + **Ctrl+G**: Toggle god mode
      + **Ctrl+S**: Toggle snap to grid
      + **Ctrl+P**: Toggle game engine pause
      + **Ctrl+Shift+P**: Toggle pausing allowed (disables focus loss pause)
      + **Ctrl+K**: Toggle disabling game keyboard input when typing
  - **F11**: Hide overlay
  - **Ctrl+Shift+U**: Change UI color
  - **Ctrl+Shift+I**: ImGui internal metrics and settings
  - **Ctrl+Shift+R**: Reset window positions (stack horizontally)
  - **Ctrl+Shift+V**: Reset window positions (stack vertically)
  - **Enter**: Run active tool
  - **Escape**: Return focus to game from an input

## Troubleshooting
  - If your game crashes when launching Overlunky or it just closes and you don't ever see the overlay in game:
    + Make sure you are running the latest version of each. We don't support old game versions and sometimes not the too recent ones either. The latest somewhat tested version can be found at the top if this document.
    + Make sure your antivirus is not blocking it. **This is very likely if you're using one.** Overlunky is very hacky and acts like malware. It isn't, but you can audit the source code and build it yourself if you want.
  - If your game crashes when actually trying to use the tools:
    + See previous section.
    + Some entities just crash the game, try to avoid them next time. [A nonexhaustive list of glitchy entities](https://gist.github.com/DekeAvell/935f414c715da1f08162deb140975fa8/).
  - If your game crashes and you're using **Modlunky2 or Playlunky**:
    + While we try to keep all the modding tools compatible, some things may break sometimes.
    + Check the [open issues](https://github.com/spelunky-fyi/overlunky/issues) for known compatibility problems with other tools.
  - If you're missing some overlay windows:
    + Delete `Spelunky 2/imgui.ini` to reset tool window positions that might be outside the screen region for whatever reason.
  - If you mess up your keyboard shortcuts:
    + Delete `Spelunky 2/hotkeys.ini` to reset shortcut keys.
  - If keyboard input no longer works in game after using the tools:
    + Make sure you're using **borderless / windowed** mode with the `Disable game keys when typing` option enabled, it doesn't work in fullscreen.
    + Restart the game after changing graphics modes.
    + Try Alt+Tabbing to restore input.
    + If nothing else works, disable the `Disable game keys when typing` option and try Alt+Tabbing to restore input.
    
## Development
If you'd rather build it yourself or help with development, clone the repository, get some Rust and C++ build tools and run this to get started:
```bash
cd overlunky
rustup toolchain install nightly
rustup default nightly
git submodule update --init --recursive
cargo build
```
The debug build will be in `target/debug/`. To enable debug logging, `set RUST_LOG=debug` in *the game environment*, e.g. where you run Spel2.exe.
