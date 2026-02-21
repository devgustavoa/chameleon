# Chameleon 🦎

A lightweight, blazing-fast C daemon that automatically switches Neovim and Alacritty colorschemes based on the time of day.

Built for Linux. Relies on `systemd` timers for zero-overhead scheduling.

*Future release features will include: tmux status bar, waybar color palette, and wallpaper switch.*

## Prerequisites

- `gcc` (for compiling)
- `systemd` (for scheduling)
- Neovim & Alacritty (target applications)

## 1. Compile

Compile the source code with basic optimizations and warnings enabled:

`gcc -O2 chameleon.c -o chameleon -Wall -Wextra`

## 2. Install the Binary

Move the compiled executable to your local bin directory:

`mkdir -p ~/.local/bin`

`mv chameleon ~/.local/bin/`

_(Make sure `~/.local/bin` is in your `$PATH` if you want to run it manually from anywhere)._

## 3. Setup Systemd Scheduling

Move the provided `.service` and `.timer` files to your user's systemd directory:

`mkdir -p ~/.config/systemd/user/`

`cp chameleon.service ~/.config/systemd/user/`

`cp chameleon.timer ~/.config/systemd/user/`

## 4. Enable and Start

Reload the systemd daemon to recognize the new files, then enable and start the timer:

`systemctl --user daemon-reload`

`systemctl --user enable --now chameleon.timer`

## Useful Commands

- **Check the timer status:** `systemctl --user list-timers --all`
- **Trigger a theme switch manually right now:** `systemctl --user start chameleon.service`
- **Check the logs:** `journalctl --user -u chameleon.service`
