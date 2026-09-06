


# Build Instructions

Note! you will not be able to compile dwm without the Xlib development headers.

1. Clone github repository, make sure you have git installed on your system.
```bash
git clone https://github.com/Invader788/archive
```
2. Open the folder labeled "archive" in the same directory you cloned the repository.
```
cd archive
```
3. Once inside the "archive" directory navigate to the "ArchLinux" or "BSD" folders
  based on the type of system you have, this project will work best on ArchLinux and BSD systems,
  I will be adding more support in the future.

4. Install dependencies:

   BSD
```BSD

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
    firefox
```
ArchLinux
```
sudo pacman -Syu --noconfirm

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
```
5. Compile!

  ArchLinux 
   ```
   cd dwm
   sudo make clean install
   cd ..
   cd dwmblocks
   sudo make clean install
   cd ..
   cd dmenu
   sudo make clean install
   cd
   ```
  BSD
   ```
   cd dwm
   sudo gmake clean install
   cd ..
   cd dwmblocks
   sudo gmake clean install
   cd ..
   cd dmenu
   sudo gmake clean install
   cd
   ```
6. Create a .xinitrc file, you can either make one on your own or there is a
   pre-made .xinitrc file in the repo both in the BSD and ArchLinux folders.

   there are some things your are going to want to change in my .xinitrc file before
   using, 1. GTK/QT dark-light themes, 2. wallpapers, I am using feh to set my wallpaper and it has a
   set directory for my computer, if you want to use a wallpaper then add the directory for your image.



# Legal
License Note: The suckless software configurations are released under the MIT/X11 license. 


## Screenshots

![Screenshot1](ArchLinux/demo1.bmp)

![Screenshot2](ArchLinux/demo2.bmp)





# Contact

email:
Space_Invader788@proton.me
