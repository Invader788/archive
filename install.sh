#!/bin/sh
sudo pacman -S harfbuzz
sudo pacman -S libxinerama
sudo pacman -S libxft
sudo pacman -S make
sudo pacman -S base-devel
sudo pacman -S xorg-xinit
sudo pacman -S nvim
sudo pacman -Syu xorg-server xorg-xinit
sudo pacman -S ttf-martian-mono-nerd
sudo pacman -S p7zip thunar-archive-plugin engrampa
sudo pacman -S zsh-autosuggestions zsh-syntax-highlighting
sudo pacman -S feh
cd archive
cd dwm
sudo make clean install
cd ..
cd dwmblocks
sudo make clean install
cd ..
cd dmenu
sudo make clean install
cd ..
cd st
sudo make clean install
cd
cd /tmp
git clone https://aur.archlinux.org/yay.git
cd yay
makepkg -si
cd
yay -S arc-gtk-theme
yay -S picom-ftlabs-git
yay -S zen-browser-bin
sudo pacman -S zsh
cd archive/xinitrc
mv xinitrc .xinitrc
mv -r .xinitrc /home
chmod +x .xinitrc
