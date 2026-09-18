#!/bin/sh

#wsg gng
echo Welcome to the archive installer.
printf "Press Enter to continue... "
read -r _

#Update system
sudo pacman -Syu --noconfirm

#Install dependencies
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
  ttf-martian-mono-nerd \
  alacritty

  #install dwm
  cd dwm
  sudo make clean install
  cd ..

  #install dwmblocks
  cd dwmblocks
  sudo make clean install
  cd ..

  #install dmenu
  cd dmenu
  sudo make clean install
  cd ..

  #setup xinitrc
  cp xinitrc ~/.xinitrc

  #setup alacritty
  mkdir ~/.config/alacritty
  cd alacritty
  cp alacritty.toml ~/.config/alacritty
  cp alacritty.toml~ ~/.config/alacritty
  cp alacritty.yml ~/.config/alacritty
  cd..

  #setup picom
  cd picom
  cp picom.conf ~/.config/picom
  cd ..

  # setup zsh
  cd zsh
  cp zshrc ~/.zshrc
  cd ..

  #done
  echo Done installing. Also checkout the github for more information
  printf "Press Enter to continue... "
  read -r _
