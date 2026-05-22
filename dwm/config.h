/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* =========================
 * APPEARANCE
 * ========================= */

static const unsigned int borderpx = 0;
static const unsigned int snap     = 32;
static const int showbar           = 1;
static const int topbar            = 1;

/* --- BARPADDING (detached bar look) --- */
static const int vertpad = 16;
static const int sidepad = 16;

/* --- BAR HEIGHT (THICKER BAR) --- */
static const int user_bh = 40;

/* =========================
 * VANITYGAPS
 * ========================= */

static const unsigned int gappih = 16;
static const unsigned int gappiv = 16;
static const unsigned int gappoh = 20;
static const unsigned int gappov = 20;

/* keep gaps even with one window */
static const int smartgaps = 0;

#define FORCE_VSPLIT 1
#include "vanitygaps.c"
/* =========================
 * FONTS
 * ========================= */

static const char *fonts[] = {
    "MartianMono Nerd Font:size=11"
};

static const char dmenufont[] =
    "MartianMono Nerd Font:size=14";

/* =========================
 * COLORS
 * ========================= */

static const char col_bg[]   = "#0f111a";
static const char col_bg2[]  = "#1a1b26";
static const char col_fg[]   = "#c0caf5";

static const char *colors[][3] = {
    [SchemeNorm] = { col_fg, col_bg, col_bg },
    [SchemeSel]  = { col_fg, col_bg2, col_bg2 },
};

/* =========================
 * TAGS
 * ========================= */

static const char *tags[] = {
    " - ",
    " - ",
    " - ",
};

/* =========================
 * RULES
 * ========================= */

static const Rule rules[] = {
    { "feh",       NULL, NULL, 0,      1, -1 },
    { "mpv",       NULL, NULL, 0,      1, -1 },
    { "firefox",   NULL, NULL, 1 << 0, 0, -1 },
    { "LibreWolf", NULL, NULL, 1 << 0, 0, -1 },
    { "Emacs",     NULL, NULL, 1 << 1, 0, -1 },
};

/* =========================
 * LAYOUTS
 * ========================= */

static const float mfact        = 0.72;
static const int nmaster        = 1;
static const int resizehints    = 0;
static const int lockfullscreen = 1;

static const Layout layouts[] = {
    { "[S]", spiral },
    { "[D]", dwindle },
    { "[T]", tile },
    { "[F]", NULL },
};

/* =========================
 * COMMANDS
 * ========================= */

static const char *termcmd[]      = { "alacritty", NULL };
static const char *filecmd[]      = { "thunar", NULL };
static const char *browsercmd[]   = { "qutebrowser", NULL };
static const char *flameshotcmd[] = { "flameshot", "gui", NULL };

/* --- VOLUME CONTROLS --- */
static const char *vol_up[]   = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *vol_down[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *vol_mute[] = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };

/* =========================
 * KEY DEFINITIONS
 * ========================= */

#define MODKEY Mod4Mask

#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY, view,       {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY, toggleview, {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY, tag,        {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY, toggletag,  {.ui = 1 << TAG} }

#define SHCMD(cmd) \
    { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* =========================
 * APPS
 * ========================= */

static char dmenumon[2] = "0";

static const char *dmenucmd[] = {
    "dmenu_run",
    "-m", dmenumon,
    "-fn", dmenufont,
    "-nb", col_bg,
    "-nf", col_fg,
    "-sb", col_bg2,
    "-sf", col_fg,
    NULL
};

/* =========================
 * KEYBINDINGS
 * ========================= */

static const Key keys[] = {

    /* apps */
    { MODKEY, XK_t, spawn, {.v = termcmd } },
    { MODKEY, XK_f, spawn, {.v = filecmd } },
    { MODKEY, XK_b, spawn, {.v = browsercmd } },
    { MODKEY, XK_d, spawn, {.v = dmenucmd } },

    /* system */
    { MODKEY, XK_q, killclient, {0} },
    { MODKEY|ShiftMask, XK_q, quit, {0} },

    /* focus */
    { MODKEY, XK_j, focusstack, {.i = +1 } },
    { MODKEY, XK_k, focusstack, {.i = -1 } },

    /* resize master */
    { MODKEY, XK_h, setmfact, {.f = -0.05} },
    { MODKEY, XK_l, setmfact, {.f = +0.05} },

    { MODKEY, XK_r, zoom, {0} },

    /* layouts */
    { MODKEY, XK_w, setlayout, {.v = &layouts[0]} },
    { MODKEY, XK_a, setlayout, {.v = &layouts[1]} },
    { MODKEY, XK_s, setlayout, {.v = &layouts[2]} },
    { MODKEY, XK_e, setlayout, {.v = &layouts[3]} },

    { MODKEY, XK_space, setlayout, {0} },
    { MODKEY|ShiftMask, XK_space, togglefloating, {0} },

    /* gaps */
    { MODKEY, XK_minus, incrgaps, {.i = -5 } },
    { MODKEY, XK_equal, incrgaps, {.i = +5 } },
    { MODKEY|ShiftMask, XK_equal, defaultgaps, {0} },
    { MODKEY|ShiftMask, XK_minus, togglegaps, {0} },

    /* screenshot */
    { 0, XK_Print, spawn, {.v = flameshotcmd } },

    /* tags */
    TAGKEYS(XK_z, 0),
    TAGKEYS(XK_x, 1),
    TAGKEYS(XK_c, 2),

    /* =========================
     * VOLUME CONTROLS
     * ========================= */
    { 0, XF86XK_AudioRaiseVolume, spawn, {.v = vol_up } },
    { 0, XF86XK_AudioLowerVolume, spawn, {.v = vol_down } },
    { 0, XF86XK_AudioMute,        spawn, {.v = vol_mute } },
};

/* =========================
 * BUTTONS
 * ========================= */

static const Button buttons[] = {
    { ClkLtSymbol,  0,      Button1, setlayout,   {0} },
    { ClkWinTitle,  0,      Button2, zoom,        {0} },
    { ClkClientWin, MODKEY, Button1, movemouse,   {0} },
    { ClkClientWin, MODKEY, Button3, resizemouse, {0} },
    { ClkTagBar,    0,      Button1, view,        {0} },
    { ClkTagBar,    0,      Button3, toggleview,  {0} },
    { ClkTagBar,    MODKEY, Button1, tag,         {0} },
    { ClkTagBar,    MODKEY, Button3, toggletag,   {0} },
};
