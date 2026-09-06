


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






# dwm 
A simple customizable window manager I use






# dmenu & dwmblocks
I use dmenu and dwmblocks alongside dwm, 
dmenu - open apps 
dwmblocks - provide time, date, battery, and network information

# Compatibility
Although I have only used this dwm configuration on ArchLinux and FreeBSD
it will probably work on different Operating systems as well.







# Legal
License Note: The suckless software configurations are released under the MIT/X11 license. 


## Screenshots

![Screenshot1](ArchLinux/demo1.bmp)

![Screenshot2](ArchLinux/demo2.bmp)





# Contact

contact:

Space_Invader788@proton.me
