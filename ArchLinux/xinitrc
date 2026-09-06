#!/bin/sh

export QT_QPA_PLATFORMTHEME=qt6ct

gsettings set org.gnome.desktop.interface gtk-theme 'Adwaita:dark'
gsettings set org.gnome.desktop.interface color-scheme 'prefer-dark'

feh --bg-fill /home/as/Desktop/wp.png

picom -b --config /home/as/.config/picom/picom.conf

dwmblocks &

exec dwm
