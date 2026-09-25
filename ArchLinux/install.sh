#!/bin/sh

set -e

echo "======================================"
echo "      Arch Linux DWM Setup"
echo "======================================"

# --------------------------------------
# Update system
# --------------------------------------

echo "[1/9] Updating system..."

sudo pacman -Syu --noconfirm


# --------------------------------------
# Install dependencies
# --------------------------------------

echo "[2/9] Installing dependencies..."

sudo pacman -S --needed --noconfirm \
    base-devel \
    git \
    harfbuzz \
    libxinerama \
    libxft \
    xorg-server \
    xorg-xinit \
    neovim \
    zsh \
    zsh-autosuggestions \
    zsh-syntax-highlighting \
    feh \
    picom \
    thunar \
    thunar-archive-plugin \
    engrampa \
    p7zip \
    alacritty \
    firefox \
    glib2 \
    adwaita-icon-theme \
    gsettings-desktop-schemas \
    gtk3 \
    gtk4 \
    ttf-martian-mono-nerd

echo "Dependencies installed."


# --------------------------------------
# Install yay
# --------------------------------------

echo "[3/9] Installing yay..."

if ! command -v yay >/dev/null 2>&1; then

    TEMP_DIR="$(mktemp -d)"

    git clone https://aur.archlinux.org/yay.git "$TEMP_DIR/yay"

    cd "$TEMP_DIR/yay"

    makepkg -si --noconfirm

    cd -

    rm -rf "$TEMP_DIR"

else
    echo "yay is already installed."
fi


# --------------------------------------
# Install Pywal
# --------------------------------------

echo "[4/9] Installing Pywal
..."

yay -S --needed --noconfirm python-pywal16

echo "Pywal installed."


# --------------------------------------
# Install dwm
# --------------------------------------

echo "[5/9] Installing dwm..."

if [ -d "dwm" ]; then
    cd dwm
    sudo make clean install
    cd ..
else
    echo "ERROR: dwm directory not found."
    exit 1
fi


# --------------------------------------
# Install dwmblocks
# --------------------------------------

echo "[6/9] Installing dwmblocks..."

if [ -d "dwmblocks" ]; then
    cd dwmblocks
    sudo make clean install
    cd ..
else
    echo "ERROR: dwmblocks directory not found."
    exit 1
fi


# --------------------------------------
# Install dmenu
# --------------------------------------

echo "[7/9] Installing dmenu..."

if [ -d "dmenu" ]; then
    cd dmenu
    sudo make clean install
    cd ..
else
    echo "ERROR: dmenu directory not found."
    exit 1
fi


# --------------------------------------
# Configure programs
# --------------------------------------

echo "[8/9] Installing configuration files..."

mkdir -p "$HOME/.config"

if [ -d "alacritty" ]; then
    cp -r alacritty "$HOME/.config/"
fi

if [ -d "nvim" ]; then
    cp -r nvim "$HOME/.config/"
fi

if [ -d "picom" ]; then
    cp -r picom "$HOME/.config/"
fi

if [ -f "zsh/zshrc" ]; then
    cp zsh/zshrc "$HOME/.zshrc"
fi

if [ -f "xinitrc" ]; then
    cp xinitrc "$HOME/.xinitrc"
fi


# --------------------------------------
# Pywal wallpaper directory
# --------------------------------------

mkdir -p "$HOME/.config/wallpapers"

if [ -d "wallpapers" ]; then
    cp -r wallpapers/* "$HOME/.config/wallpapers/"
fi


# --------------------------------------
# Set Zsh
# --------------------------------------

if command -v zsh >/dev/null 2>&1; then
    if [ "$SHELL" != "$(command -v zsh)" ]; then
        chsh -s "$(command -v zsh)"
    fi
fi


# --------------------------------------
# Done
# --------------------------------------

echo
echo "======================================"
echo "       Installation Complete!"
echo "======================================"
echo
echo "Installed:"
echo "  ✓ yay"
echo "  ✓ Pywal"
echo "  ✓ dwm"
echo "  ✓ dwmblocks"
echo "  ✓ dmenu"
echo "  ✓ Alacritty"
echo "  ✓ Neovim"
echo "  ✓ Picom"
echo "  ✓ Firefox"
echo "  ✓ Thunar"
echo "  ✓ Zsh"
echo
echo "Wallpaper directory:"
echo
echo "    ~/.config/wallpapers/"
echo
echo "Generate Pywal colors with:"
echo
echo "    wal -i ~/.config/wallpapers/wallpaper.jpg"
echo
echo "======================================"

# Start DWM
startx







  
