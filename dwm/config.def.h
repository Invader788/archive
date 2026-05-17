/* See LICENSE file for copyright and license details. */
#include "fibanacci.c"
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;
static const unsigned int snap      = 32;
static const int showbar            = 1;
static const int topbar             = 1;
static const int refreshrate        = 60;

static const char *fonts[] = {
    "MartianMono NF:style=Bold:size=11"
};

static const char dmenufont[] =
    "JetBrainsMonoNL NFP:size=20:style=Bold";

/* colors */
static const char col_gray1[] = "#1e1e1e";
static const char col_gray2[] = "#3a3a3a";
static const char col_gray3[] = "#c0c0c0";
static const char col_gray4[] = "#444444";s
static const char col_cyan[]  = "#ffffff";

static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_cyan,  col_gray4, col_gray4 },
};

/* tagging */
static const char *tags[] = { " - ", " - ", " - " };

static const Rule rules[] = {
    { "feh",       NULL, NULL, 0,        1, -1 },
    { "mpv",       NULL, NULL, 0,        1, -1 },
    { "firefox",   NULL, NULL, 1 << 0,   0, -1 },
    { "librewolf", NULL, NULL, 1 << 0,   0, -1 },
    { "Emacs",     NULL, NULL, 1 << 1,   0, -1 },
    { "kitty",     NULL, NULL, 1 << 2,   0, -1 },
};

/* layout(s) */
static const float mfact     = 0.55;
static const int nmaster     = 1;
static const int resizehints = 0;
static const int lockfullscreen = 1;

#include "fibonacci.c"
static const Layout layouts[] = {
    { "(f)",  spiral },
    { "><>",  NULL },
    { "[M]",  monocle },
    { "[]=",  tile },
    { "[\\]", dwindle },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
};

/* key definitions */
#define MODKEY Mod4Mask

#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define SHCMD(cmd) \
    { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0";

static const char *dmenucmd[] = {
    "dmenu_run",
    "-m", dmenumon,
    "-fn", dmenufont,
    "-nb", col_gray1,
    "-nf", col_gray3,
    "-sb", col_gray4,
    "-sf", col_cyan,
    NULL
};

static const char *termcmd[]        = { "alacritty", NULL };
static const char *filemanagercmd[] = { "thunar", NULL };
static const char *browsercmd[]     = { "qutebrowser", NULL };
static const char *flameshot[]      = { "flameshot", "gui", NULL };

/* key bindings */
static const Key keys[] = {

    /* apps */
    { MODKEY,                       XK_t,      spawn,          {.v = termcmd } },
    { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_f,      spawn,          {.v = filemanagercmd } },
    { MODKEY,                       XK_b,      spawn,          {.v = browsercmd } },

    /* windows */
    { MODKEY,                       XK_q,      killclient,     {0} },
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },

    /* focus */
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },

    /* master */
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_r,      zoom,           {0} },

    /* layouts */
    { MODKEY,                       XK_Return, setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_o,      setlayout,      {.v = &layouts[2]} },

    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

    /* monitor */
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },

    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

    /* media */
    { 0, XF86XK_AudioMute,
        spawn, SHCMD("pactl set-sink-mute 0 toggle") },

    { 0, XF86XK_AudioLowerVolume,
        spawn, SHCMD("pactl set-sink-volume 0 -3%") },

    { 0, XF86XK_AudioRaiseVolume,
        spawn, SHCMD("pactl set-sink-volume 0 +3%") },

    { 0, XF86XK_MonBrightnessUp,
        spawn, SHCMD("brightnessctl g +5%") },

    { 0, XF86XK_MonBrightnessDown,
        spawn, SHCMD("brightnessctl g 5%-") },

    { 0, XK_Print,
        spawn, {.v = flameshot} },

    /* tags */
    TAGKEYS(XK_z, 0)
    TAGKEYS(XK_x, 1)
    TAGKEYS(XK_c, 2)
};

/* button definitions */
static const Button buttons[] = {
    { ClkLtSymbol,  0,      Button1, setlayout,      {0} },
    { ClkWinTitle,  0,      Button2, zoom,           {0} },
    { ClkClientWin, MODKEY, Button1, movemouse,      {0} },
    { ClkClientWin, MODKEY, Button3, resizemouse,    {0} },
    { ClkTagBar,    0,      Button1, view,           {0} },
    { ClkTagBar,    0,      Button3, toggleview,     {0} },
    { ClkTagBar,    MODKEY, Button1, tag,            {0} },
    { ClkTagBar,    MODKEY, Button3, toggletag,      {0} },
};

