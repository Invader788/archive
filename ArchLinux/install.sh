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
