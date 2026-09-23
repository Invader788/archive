#!/bin/sh

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
  ttf-martian-mono-nerd

#Compile dwm
  cd dwm
  sudo make clean install
  cd ..
  cd dwmblocks
  sudo make clean install
  cd ..
  cd dmenu
  sudo make clean install


#Install programs
  sudo pacman -S --needed --noconfirm \
  alacirtty \
  nvim \
  picom \
  firfox \
  glib2 \
  adwaita-icon-theme \
  gsettings-desktop-schemas gtk3 gtk4 
  


#Configure programs
  cp -r alacritty ~/.config
  cp -r nvim ~/.config
  cp -r picom ~/.config
  cd zsh
  cp -r zshrc ~/.zshrc
  cd ..
  cp -r xinitrc ~/.xinitrc
  cd -r 



# uhhh idk lol
echo Please run startx to start dwm







  
