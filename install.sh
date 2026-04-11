#!/bin/sh

sudo pacman -S make
sudo pacman -S base-devel
sudo pacman -S xorg-xinit
sudo pacman -Syu xorg-server xorg-xinit
sudo pacman -S harfbuzz
sudo pacman -S libxinerama
sudo pacman -S libxft
sudo pacman -S picom
cd /tmp
git clone https://aur.archlinux.org/yay.git
cd yay
makepkg -si

cd archive
mv suckless ~/.config
mv picom.conf /home/as
cd 
cd ~/.config
cd suckless
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


vim ~/.xinitrc
#!/bin/sh
picom -b --config /home/as/picom.conf
dwmblocks &
exec dwm

