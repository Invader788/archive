#!/bin/sh

sudo pkg update
sudo pkg upgrade

sudo pkg install -y \
  harfbuzz \
  libXinerama \
  libXft \
  gmake \
  base-devel \
  xorg-server \
  xinit \
  neovim \
  nerd-fonts-martianmono \
  p7zip \
  thunar-archive-plugin \
  engrampa \
  zsh \
  zsh-autosuggestions \
  zsh-syntax-highlighting \
  feh
