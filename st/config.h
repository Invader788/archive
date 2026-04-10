/* See LICENSE file for copyright and license details. */

/*
 * appearance
 */
static char *font = "MartianMono NF:style=Bold:size=11:antialias=true:autohint=true";
static char *font2[] = { "MartianMono:pixelsize=10:antialias=true:autohint=true" };
static int borderpx = 2;

/*
 * What program is execed by st
 */
static char *shell = "/bin/zsh";
char *utmp = NULL;
char *scroll = NULL;
char *stty_args = "stty raw pass8 nl -echo -iexten -cstopb 38400";
char *vtiden = "\033[?6c";

/* Kerning / character bounding-box multipliers */
static float cwscale = 1.0;
static float chscale = 1.0;

/* word delimiter string */
wchar_t *worddelimiters = L" ";

/* selection timeouts (in milliseconds) */
static unsigned int doubleclicktimeout = 300;
static unsigned int tripleclicktimeout = 600;

/* alt screens */
int allowaltscreen = 1;
int allowwindowops = 0;

/* draw latency */
static double minlatency = 8;
static double maxlatency = 33;

/* blinking timeout */
static unsigned int blinktimeout = 800;

/* cursor thickness */
static unsigned int cursorthickness = 2;

/* boxdraw */
const int boxdraw = 1;
const int boxdraw_bold = 0;
const int boxdraw_braille = 0;

/* bell volume */
static int bellvolume = 0;

/* default TERM */
char *termname = "st-256color";

/* spaces per tab */
unsigned int tabspaces = 8;

/* bg opacity */
float alpha = 0.45;
float alphaOffset = 0.0;
float alphaUnfocus;

/* Terminal colors */
static const char *colorname[] = {
    "#282828", "#cc241d", "#98971a", "#d79921",
    "#458588", "#b16286", "#689d6a", "#a89984",
    "#928374", "#fb4934", "#b8bb26", "#fabd2f",
    "#83a598", "#d3869b", "#8ec07c", "#ebdbb2",

    [255] = 0,
    "#add8e6", /* 256 -> cursor */
    "#555555", /* 257 -> rev cursor*/
    "#282828", /* 258 -> bg */
    "#ebdbb2", /* 259 -> fg */
};

/* Default colors */
unsigned int defaultfg = 259;
unsigned int defaultbg = 258;
unsigned int defaultcs = 256;
unsigned int defaultrcs = 257;
unsigned int background = 258;

/* Cursor shape */
static unsigned int cursorshape = 2;

/* Default size */
static unsigned int cols = 80;
static unsigned int rows = 24;

/* Mouse cursor */
static unsigned int mouseshape = XC_xterm;
static unsigned int mousefg = 7;
static unsigned int mousebg = 0;

static unsigned int defaultattr = 11;
static uint forcemousemod = ShiftMask;

/* Xresources preferences */
ResourcePref resources[] = {
    { "font", STRING, &font },
    { "fontalt0", STRING, &font2[0] },
    { "color0", STRING, &colorname[0] },
    { "color1", STRING, &colorname[1] },
    { "color2", STRING, &colorname[2] },
    { "color3", STRING, &colorname[3] },
    { "color4", STRING, &colorname[4] },
    { "color5", STRING, &colorname[5] },
    { "color6", STRING, &colorname[6] },
    { "color7", STRING, &colorname[7] },
    { "color8", STRING, &colorname[8] },
    { "color9", STRING, &colorname[9] },
    { "color10", STRING, &colorname[10] },
    { "color11", STRING, &colorname[11] },
    { "color12", STRING, &colorname[12] },
    { "color13", STRING, &colorname[13] },
    { "color14", STRING, &colorname[14] },
    { "color15", STRING, &colorname[15] },
    { "background", STRING, &colorname[258] },
    { "foreground", STRING, &colorname[259] },
    { "cursorColor", STRING, &colorname[256] },
    { "termname", STRING, &termname },
    { "shell", STRING, &shell },
    { "minlatency", INTEGER, &minlatency },
    { "maxlatency", INTEGER, &maxlatency },
    { "blinktimeout", INTEGER, &blinktimeout },
    { "bellvolume", INTEGER, &bellvolume },
    { "tabspaces", INTEGER, &tabspaces },
    { "borderpx", INTEGER, &borderpx },
    { "cwscale", FLOAT, &cwscale },
    { "chscale", FLOAT, &chscale },
    { "alpha", FLOAT, &alpha },
    { "alphaOffset", FLOAT, &alphaOffset },
};

/* Mouse shortcuts */
static MouseShortcut mshortcuts[] = {
    { XK_NO_MOD, Button4, kscrollup, {.i = 1} },
    { XK_NO_MOD, Button5, kscrolldown, {.i = 1} },
    { XK_ANY_MOD, Button2, selpaste, {.i = 0}, 1 },
    { ShiftMask, Button4, ttysend, {.s = "\033[5;2~"} },
    { XK_ANY_MOD, Button4, ttysend, {.s = "\031"} },
    { ShiftMask, Button5, ttysend, {.s = "\033[6;2~"} },
    { XK_ANY_MOD, Button5, ttysend, {.s = "\005"} },
};

/* Keyboard shortcuts */
#define MODKEY Mod1Mask
#define TERMMOD (Mod1Mask|ShiftMask)

static char *openurlcmd[] = { "/bin/zsh", "-c", "st-urlhandler -o", "externalpipe", NULL };
static char *copyurlcmd[] = { "/bin/zsh", "-c", "st-urlhandler -c", "externalpipe", NULL };
static char *copyoutput[] = { "/bin/zsh", "-c", "st-copyout", "externalpipe", NULL };

static Shortcut shortcuts[] = {
    { XK_ANY_MOD, XK_Break, sendbreak, {.i = 0} },
    { ControlMask, XK_Print, toggleprinter, {.i = 0} },
    { ShiftMask, XK_Print, printscreen, {.i = 0} },
    { XK_ANY_MOD, XK_Print, printsel, {.i = 0} },

    { TERMMOD, XK_Prior, zoom, {.f = +1} },
    { TERMMOD, XK_Next, zoom, {.f = -1} },
    { TERMMOD, XK_Home, zoomreset, {.f = 0} },

    { TERMMOD, XK_Up, zoom, {.f = +1} },
    { TERMMOD, XK_Down, zoom, {.f = -1} },
    { TERMMOD, XK_K, zoom, {.f = +1} },
    { TERMMOD, XK_J, zoom, {.f = -1} },

    /* === ZOOM SHORTCUTS (Ctrl+Shift because Ctrl+Z is used by shell) === */
    { ControlMask|ShiftMask, XK_Z, zoom, {.f = +1.0} },  // Ctrl + Shift + Z = Zoom In (bigger font)
    { ControlMask|ShiftMask, XK_X, zoom, {.f = -1.0} },  // Ctrl + Shift + X = Zoom Out (smaller font)

    { TERMMOD, XK_C, clipcopy, {.i = 0} },
    { TERMMOD, XK_V, clippaste, {.i = 0} },
    { MODKEY, XK_c, clipcopy, {.i = 0} },
    { MODKEY, XK_v, clippaste, {.i = 0} },
    { ShiftMask, XK_Insert, clippaste, {.i = 0} },
    { ShiftMask, XK_Insert, selpaste, {.i = 0} },

    { TERMMOD, XK_Num_Lock, numlock, {.i = 0} },

    { MODKEY, XK_k, kscrollup, {.i = 1} },
    { MODKEY, XK_j, kscrolldown, {.i = 1} },
    { MODKEY, XK_Up, kscrollup, {.i = 1} },
    { MODKEY, XK_Down, kscrolldown, {.i = 1} },
    { MODKEY, XK_u, kscrollup, {.i = -1} },
    { MODKEY, XK_d, kscrolldown, {.i = -1} },

    { MODKEY, XK_s, changealpha, {.f = -0.05} },
    { MODKEY, XK_a, changealpha, {.f = +0.05} },

    { MODKEY, XK_l, externalpipe, {.v = openurlcmd } },
    { MODKEY, XK_y, externalpipe, {.v = copyurlcmd } },
    { MODKEY, XK_o, externalpipe, {.v = copyoutput } },
};

/* Special keys */
static KeySym mappedkeys[] = { -1 };
static uint ignoremod = Mod2Mask | XK_SWITCH_MOD;

/* Key mapping table */
static Key key[] = {
    { XK_KP_Home, ShiftMask, "\033[2J", 0, -1},
    { XK_KP_Home, ShiftMask, "\033[1;2H", 0, +1},
    { XK_KP_Home, XK_ANY_MOD, "\033[H", 0, -1},
    { XK_KP_Home, XK_ANY_MOD, "\033[1~", 0, +1},
    { XK_KP_Up, XK_ANY_MOD, "\033Ox", +1, 0},
    { XK_KP_Up, XK_ANY_MOD, "\033[A", 0, -1},
    { XK_KP_Up, XK_ANY_MOD, "\033OA", 0, +1},
    { XK_KP_Down, XK_ANY_MOD, "\033Or", +1, 0},
    { XK_KP_Down, XK_ANY_MOD, "\033[B", 0, -1},
    { XK_KP_Down, XK_ANY_MOD, "\033OB", 0, +1},
    { XK_KP_Left, XK_ANY_MOD, "\033Ot", +1, 0},
    { XK_KP_Left, XK_ANY_MOD, "\033[D", 0, -1},
    { XK_KP_Left, XK_ANY_MOD, "\033OD", 0, +1},
    { XK_KP_Right, XK_ANY_MOD, "\033Ov", +1, 0},
    { XK_KP_Right, XK_ANY_MOD, "\033[C", 0, -1},
    { XK_KP_Right, XK_ANY_MOD, "\033OC", 0, +1},
    { XK_KP_Prior, ShiftMask, "\033[5;2~", 0, 0},
    { XK_KP_Prior, XK_ANY_MOD, "\033[5~", 0, 0},
    { XK_KP_Begin, XK_ANY_MOD, "\033[E", 0, 0},
    { XK_KP_End, ControlMask, "\033[J", -1, 0},
    { XK_KP_End, ControlMask, "\033[1;5F", +1, 0},
    { XK_KP_End, ShiftMask, "\033[K", -1, 0},
    { XK_KP_End, ShiftMask, "\033[1;2F", +1, 0},
    { XK_KP_End, XK_ANY_MOD, "\033[4~", 0, 0},
    { XK_KP_Next, ShiftMask, "\033[6;2~", 0, 0},
    { XK_KP_Next, XK_ANY_MOD, "\033[6~", 0, 0},
    { XK_KP_Insert, ShiftMask, "\033[2;2~", +1, 0},
    { XK_KP_Insert, ShiftMask, "\033[4l", -1, 0},
    { XK_KP_Insert, ControlMask, "\033[L", -1, 0},
    { XK_KP_Insert, ControlMask, "\033[2;5~", +1, 0},
    { XK_KP_Insert, XK_ANY_MOD, "\033[4h", -1, 0},
    { XK_KP_Insert, XK_ANY_MOD, "\033[2~", +1, 0},
    { XK_KP_Delete, ControlMask, "\033[M", -1, 0},
    { XK_KP_Delete, ControlMask, "\033[3;5~", +1, 0},
    { XK_KP_Delete, ShiftMask, "\033[2K", -1, 0},
    { XK_KP_Delete, ShiftMask, "\033[3;2~", +1, 0},
    { XK_KP_Delete, XK_ANY_MOD, "\033[P", -1, 0},
    { XK_KP_Delete, XK_ANY_MOD, "\033[3~", +1, 0},
    { XK_KP_Multiply, XK_ANY_MOD, "\033Oj", +2, 0},
    { XK_KP_Add, XK_ANY_MOD, "\033Ok", +2, 0},
    { XK_KP_Enter, XK_ANY_MOD, "\033OM", +2, 0},
    { XK_KP_Enter, XK_ANY_MOD, "\r", -1, 0},
    { XK_KP_Subtract, XK_ANY_MOD, "\033Om", +2, 0},
    { XK_KP_Decimal, XK_ANY_MOD, "\033On", +2, 0},
    { XK_KP_Divide, XK_ANY_MOD, "\033Oo", +2, 0},
    { XK_KP_0, XK_ANY_MOD, "\033Op", +2, 0},
    { XK_KP_1, XK_ANY_MOD, "\033Oq", +2, 0},
    { XK_KP_2, XK_ANY_MOD, "\033Or", +2, 0},
    { XK_KP_3, XK_ANY_MOD, "\033Os", +2, 0},
    { XK_KP_4, XK_ANY_MOD, "\033Ot", +2, 0},
    { XK_KP_5, XK_ANY_MOD, "\033Ou", +2, 0},
    { XK_KP_6, XK_ANY_MOD, "\033Ov", +2, 0},
    { XK_KP_7, XK_ANY_MOD, "\033Ow", +2, 0},
    { XK_KP_8, XK_ANY_MOD, "\033Ox", +2, 0},
    { XK_KP_9, XK_ANY_MOD, "\033Oy", +2, 0},

    { XK_Up, ShiftMask, "\033[1;2A", 0, 0},
    { XK_Up, Mod1Mask, "\033[1;3A", 0, 0},
    { XK_Up, ShiftMask|Mod1Mask,"\033[1;4A", 0, 0},
    { XK_Up, ControlMask, "\033[1;5A", 0, 0},
    { XK_Up, ShiftMask|ControlMask,"\033[1;6A", 0, 0},
    { XK_Up, ControlMask|Mod1Mask,"\033[1;7A", 0, 0},
    { XK_Up,ShiftMask|ControlMask|Mod1Mask,"\033[1;8A", 0, 0},
    { XK_Up, XK_ANY_MOD, "\033[A", 0, -1},
    { XK_Up, XK_ANY_MOD, "\033OA", 0, +1},

    { XK_Down, ShiftMask, "\033[1;2B", 0, 0},
    { XK_Down, Mod1Mask, "\033[1;3B", 0, 0},
    { XK_Down, ShiftMask|Mod1Mask,"\033[1;4B", 0, 0},
    { XK_Down, ControlMask, "\033[1;5B", 0, 0},
    { XK_Down, ShiftMask|ControlMask,"\033[1;6B", 0, 0},
    { XK_Down, ControlMask|Mod1Mask,"\033[1;7B", 0, 0},
    { XK_Down,ShiftMask|ControlMask|Mod1Mask,"\033[1;8B",0, 0},
    { XK_Down, XK_ANY_MOD, "\033[B", 0, -1},
    { XK_Down, XK_ANY_MOD, "\033OB", 0, +1},

    { XK_Left, ShiftMask, "\033[1;2D", 0, 0},
    { XK_Left, Mod1Mask, "\033[1;3D", 0, 0},
    { XK_Left, ShiftMask|Mod1Mask,"\033[1;4D", 0, 0},
    { XK_Left, ControlMask, "\033[1;5D", 0, 0},
    { XK_Left, ShiftMask|ControlMask,"\033[1;6D", 0, 0},
    { XK_Left, ControlMask|Mod1Mask,"\033[1;7D", 0, 0},
    { XK_Left,ShiftMask|ControlMask|Mod1Mask,"\033[1;8D",0, 0},
    { XK_Left, XK_ANY_MOD, "\033[D", 0, -1},
    { XK_Left, XK_ANY_MOD, "\033OD", 0, +1},

    { XK_Right, ShiftMask, "\033[1;2C", 0, 0},
    { XK_Right, Mod1Mask, "\033[1;3C", 0, 0},
    { XK_Right, ShiftMask|Mod1Mask,"\033[1;4C", 0, 0},
    { XK_Right, ControlMask, "\033[1;5C", 0, 0},
    { XK_Right, ShiftMask|ControlMask,"\033[1;6C", 0, 0},
    { XK_Right, ControlMask|Mod1Mask,"\033[1;7C", 0, 0},
    { XK_Right,ShiftMask|ControlMask|Mod1Mask,"\033[1;8C",0, 0},
    { XK_Right, XK_ANY_MOD, "\033[C", 0, -1},
    { XK_Right, XK_ANY_MOD, "\033OC", 0, +1},

    { XK_ISO_Left_Tab, ShiftMask, "\033[Z", 0, 0},
    { XK_Return, Mod1Mask, "\033\r", 0, 0},
    { XK_Return, XK_ANY_MOD, "\r", 0, 0},
    { XK_Insert, ShiftMask, "\033[4l", -1, 0},
    { XK_Insert, ShiftMask, "\033[2;2~", +1, 0},
    { XK_Insert, ControlMask, "\033[L", -1, 0},
    { XK_Insert, ControlMask, "\033[2;5~", +1, 0},
    { XK_Insert, XK_ANY_MOD, "\033[4h", -1, 0},
    { XK_Insert, XK_ANY_MOD, "\033[2~", +1, 0},
    { XK_Delete, ControlMask, "\033[M", -1, 0},
    { XK_Delete, ControlMask, "\033[3;5~", +1, 0},
    { XK_Delete, ShiftMask, "\033[2K", -1, 0},
    { XK_Delete, ShiftMask, "\033[3;2~", +1, 0},
    { XK_Delete, XK_ANY_MOD, "\033[P", -1, 0},
    { XK_Delete, XK_ANY_MOD, "\033[3~", +1, 0},
    { XK_BackSpace, XK_NO_MOD, "\177", 0, 0},
    { XK_BackSpace, Mod1Mask, "\033\177", 0, 0},

    { XK_Home, ShiftMask, "\033[2J", 0, -1},
    { XK_Home, ShiftMask, "\033[1;2H", 0, +1},
    { XK_Home, XK_ANY_MOD, "\033[H", 0, -1},
    { XK_Home, XK_ANY_MOD, "\033[1~", 0, +1},
    { XK_End, ControlMask, "\033[J", -1, 0},
    { XK_End, ControlMask, "\033[1;5F", +1, 0},
    { XK_End, ShiftMask, "\033[K", -1, 0},
    { XK_End, ShiftMask, "\033[1;2F", +1, 0},
    { XK_End, XK_ANY_MOD, "\033[4~", 0, 0},

    { XK_Prior, ControlMask, "\033[5;5~", 0, 0},
    { XK_Prior, ShiftMask, "\033[5;2~", 0, 0},
    { XK_Prior, XK_ANY_MOD, "\033[5~", 0, 0},
    { XK_Next, ControlMask, "\033[6;5~", 0, 0},
    { XK_Next, ShiftMask, "\033[6;2~", 0, 0},
    { XK_Next, XK_ANY_MOD, "\033[6~", 0, 0},

    { XK_F1,  XK_NO_MOD, "\033OP", 0, 0},
    { XK_F2,  XK_NO_MOD, "\033OQ", 0, 0},
    { XK_F3,  XK_NO_MOD, "\033OR", 0, 0},
    { XK_F4,  XK_NO_MOD, "\033OS", 0, 0},
    { XK_F5,  XK_NO_MOD, "\033[15~", 0, 0},
    { XK_F6,  XK_NO_MOD, "\033[17~", 0, 0},
    { XK_F7,  XK_NO_MOD, "\033[18~", 0, 0},
    { XK_F8,  XK_NO_MOD, "\033[19~", 0, 0},
    { XK_F9,  XK_NO_MOD, "\033[20~", 0, 0},
    { XK_F10, XK_NO_MOD, "\033[21~", 0, 0},
    { XK_F11, XK_NO_MOD, "\033[23~", 0, 0},
    { XK_F12, XK_NO_MOD, "\033[24~", 0, 0},
};

static uint selmasks[] = {
    [SEL_RECTANGULAR] = Mod1Mask,
};

static char ascii_printable[] =
" !\"#$%&'()*+,-./0123456789:;<=>?"
"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
"`abcdefghijklmnopqrstuvwxyz{|}~";
