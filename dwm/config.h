/* See LICENSE file for copyright and license details. */

#include "fibonacci.c"
#include <X11/XF86keysym.h>

/* =========================
 * APPEARANCE
 * ========================= */

static const unsigned int borderpx  = 2;
static const unsigned int snap      = 32;
static const int showbar            = 1;
static const int topbar             = 1;
static const int refreshrate        = 60;

/* fonts */
static const char *fonts[] = {
    "MartianMono Nerd Font:size=11"
};

static const char dmenufont[] =
    "MartianMono Nerd Font:size=14";

/* =========================
 * COLORS (clean dark, no filled accents)
 * ========================= */

static const char col_bg[]     = "#0f111a";
static const char col_bg2[]    = "#1a1b26";
static const char col_fg[]     = "#c0caf5";
static const char col_muted[]  = "#565f89";

static const char col_blue[]   = "#7aa2f7";

/* schemes: fg, bg, border */
static const char *colors[][3] = {
    /* normal: soft text on dark bg */
    [SchemeNorm] = { col_fg,  col_bg,  col_bg2 },

    /* selected: blue text, no blue fill */
    [SchemeSel]  = { col_blue, col_bg, col_blue },
};

/* =========================
 * TAGS
 * ========================= */

static const char *tags[] = {
    "1",
    "2",
    "3",
};

/* =========================
 * RULES
 * ========================= */

static const Rule rules[] = {
    { "feh",       NULL, NULL, 0,        1, -1 },
    { "mpv",       NULL, NULL, 0,        1, -1 },
    { "firefox",   NULL, NULL, 1 << 0,   0, -1 },
    { "librewolf", NULL, NULL, 1 << 0,   0, -1 },
    { "Emacs",     NULL, NULL, 1 << 1,   0, -1 },
    { "kitty",     NULL, NULL, 1 << 2,   0, -1 },
};

/* =========================
 * LAYOUTS
 * ========================= */

static const float mfact     = 0.72;
static const int nmaster     = 1;
static const int resizehints = 0;
static const int lockfullscreen = 1;

static const Layout layouts[] = {
    { "[S]", spiral },
    { "[D]", dwindle },
    { "[T]", tile },
    { "[F]", NULL },
};

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
    "-sf", col_blue,
    NULL
};

static const char *termcmd[]        = { "alacritty", NULL };
static const char *filemanagercmd[] = { "thunar", NULL };
static const char *browsercmd[]     = { "qutebrowser", NULL };
static const char *flameshot[]      = { "flameshot", "gui", NULL };

/* =========================
 * KEYBINDINGS
 * ========================= */

static const Key keys[] = {

    { MODKEY, XK_t, spawn, {.v = termcmd } },
    { MODKEY, XK_d, spawn, {.v = dmenucmd } },
    { MODKEY, XK_f, spawn, {.v = filemanagercmd } },
    { MODKEY, XK_b, spawn, {.v = browsercmd } },

    { MODKEY, XK_q, killclient, {0} },
    { MODKEY|ShiftMask, XK_q, quit, {0} },

    { MODKEY, XK_j, focusstack, {.i = +1 } },
    { MODKEY, XK_k, focusstack, {.i = -1 } },

    { MODKEY, XK_h, setmfact, {.f = -0.05} },
    { MODKEY, XK_l, setmfact, {.f = +0.05} },

    { MODKEY, XK_r, zoom, {0} },

    { MODKEY, XK_a, setlayout, {.v = &layouts[0]} },
    { MODKEY, XK_s, setlayout, {.v = &layouts[1]} },
    { MODKEY, XK_w, setlayout, {.v = &layouts[2]} },
    { MODKEY, XK_e, setlayout, {.v = &layouts[3]} },

    { MODKEY, XK_space, setlayout, {0} },
    { MODKEY|ShiftMask, XK_space, togglefloating, {0} },

    { MODKEY, XK_comma, focusmon, {.i = -1 } },
    { MODKEY, XK_period, focusmon, {.i = +1 } },

    { MODKEY|ShiftMask, XK_comma, tagmon, {.i = -1 } },
    { MODKEY|ShiftMask, XK_period, tagmon, {.i = +1 } },

    /* media */
    { 0, XF86XK_AudioMute,
        spawn, SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") },

    { 0, XF86XK_AudioLowerVolume,
        spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -3%") },

    { 0, XF86XK_AudioRaiseVolume,
        spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +3%") },

    { 0, XF86XK_MonBrightnessUp,
        spawn, SHCMD("brightnessctl set +5%") },

    { 0, XF86XK_MonBrightnessDown,
        spawn, SHCMD("brightnessctl set 5%-") },

    { 0, XK_Print,
        spawn, {.v = flameshot} },

    TAGKEYS(XK_z, 0),
    TAGKEYS(XK_x, 1),
    TAGKEYS(XK_c, 2),
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
