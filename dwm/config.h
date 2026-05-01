#include "fibanacci.c"

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 3;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const unsigned int gappih         = 5;   /* horiz inner gap between windows */
static const unsigned int gappiv         = 5;   /* vert inner gap between windows */
static const unsigned int gappoh         = 5;   /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 5;   /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 0;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const int statusmon               = 'A';
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int showsystray             = 0;   /* 0 means no systray */

/* Indicators */
static int tagindicatortype              = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;

/* Fonts */
static const char *fonts[]               = { "MartianMono NF:style=Bold:size=11:antialias=true:autohint=true" };
static const char dmenufont[]            = "JetBrainsMonoNL NFP:size=20:style=Bold";

static char c000000[]                    = "#000000";

/* Colors - Monochrome Gray */

static char normfgcolor[]        = "#d4d4d4";  // light gray text
static char normbgcolor[]        = "#1e1e1e";  // dark background
static char normbordercolor[]    = "#3a3a3a";
static char normfloatcolor[]     = "#3a3a3a";

static char selfgcolor[]         = "#ffffff";  // bright white for focus
static char selbgcolor[]         = "#444444";  // medium gray highlight
static char selbordercolor[]     = "#666666";
static char selfloatcolor[]      = "#666666";

static char titlenormfgcolor[]   = "#c0c0c0";
static char titlenormbgcolor[]   = "#1e1e1e";
static char titlenormbordercolor[] = "#3a3a3a";
static char titlenormfloatcolor[]  = "#3a3a3a";

static char titleselfgcolor[]    = "#ffffff";
static char titleselbgcolor[]    = "#444444";
static char titleselbordercolor[] = "#666666";
static char titleselfloatcolor[]  = "#666666";

static char tagsnormfgcolor[]    = "#c0c0c0";
static char tagsnormbgcolor[]    = "#1e1e1e";
static char tagsnormbordercolor[] = "#3a3a3a";
static char tagsnormfloatcolor[]  = "#3a3a3a";

static char tagsselfgcolor[]     = "#ffffff";
static char tagsselbgcolor[]     = "#444444";
static char tagsselbordercolor[] = "#666666";
static char tagsselfloatcolor[]  = "#666666";

static char hidnormfgcolor[]     = "#888888";
static char hidselfgcolor[]      = "#aaaaaa";
static char hidnormbgcolor[]     = "#1e1e1e";
static char hidselbgcolor[]      = "#2a2a2a";

static char urgfgcolor[]         = "#ffffff";
static char urgbgcolor[]         = "#2a2a2a";
static char urgbordercolor[]     = "#888888";
static char urgfloatcolor[]      = "#888888";

static char *colors[][ColCount] = {
    [SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
    [SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
    [SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
    [SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
    [SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
    [SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
    [SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
    [SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
    [SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};

/* Tags */
static char *tagicons[][NUMTAGS] = {
  [DEFAULT_TAGS]        = { "1", "2", "3" },
  [ALTERNATIVE_TAGS]    = { "A", "B", "C" },
  [ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>" },
};

/* Rules */
static const Rule rules[] = {
    RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
    RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
    RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
    RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
    RULE(.class = "feh", .isfloating = 1)
    RULE(.class = "mpv", .isfloating = 1)
    RULE(.class = "Signal", .tags = 1 << 0)
    RULE(.class = "Emacs", .tags = 1 << 1)
    RULE(.class = "KeePassXC", .tags = 1 << 2)
    RULE(.class = "firefox", .tags = 1 << 0)
    RULE(.class = "librewolf", .tags = 1 << 0)
    RULE(.class = "Chromium", .tags = 1 << 2)
    RULE(.class = "Mullvad Browser", .tags = 1 << 2)
    RULE(.class = "Pavucontrol", .tags = 1 << 2)
    RULE(.class = "kitty", .tags = 1 << 2)
    RULE(.class = "Thunar", .tags = 1 << 0)
};

/* Bar rules */
static const BarRule barrules[] = {
    { -1,        0,     BAR_ALIGN_LEFT,   width_tags,               draw_tags,                click_tags,              hover_tags,              "tags" },
    {  0,        0,     BAR_ALIGN_RIGHT,  width_systray,            draw_systray,             click_systray,           NULL,                    "systray" },
    { -1,        0,     BAR_ALIGN_LEFT,   width_ltsymbol,           draw_ltsymbol,            click_ltsymbol,          NULL,                    "layout" },
    { statusmon, 0,     BAR_ALIGN_RIGHT,  width_status,             draw_status,              click_status,            NULL,                    "status" },
    { -1,        0,     BAR_ALIGN_NONE,   width_awesomebar,         draw_awesomebar,          click_awesomebar,        NULL,                    "awesomebar" },
};

/* Layouts */
static const float mfact     = 0.5; 
static const int nmaster     = 1;   
static const int resizehints = 0;   
static const int lockfullscreen = 1; 

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "(f)",      spiral },    
    { "><>",      NULL },    
    { "[M]",      monocle },
    { "[]=",      tile },   /* Fibonacci Spiral */
    { "[\\]",     dwindle },  /* Fibonacci Dwindle */
};

/* Key definitions */
#include <X11/XF86keysym.h>
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Commands */
static char dmenumon[2] = "0"; 
static const char *dmenucmd[] = {
    "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL
};

static const char *termcmd[]        = { "alacritty", NULL };
static const char *flameshot[]      = { "flameshot", "gui", NULL };
static const char *filemanagercmd[] = { "thunar", NULL };
static const char *floatingbrowser[] = { "qutebrowser", NULL };

static const Key keys[] = {
    /* Basic functionality */
    { MODKEY,                       XK_t,          spawn,                  {.v = termcmd } },
    { MODKEY,                       XK_q,          killclient,             {0} },
    { MODKEY|ShiftMask,             XK_q,          quit,                   {0} },
    { MODKEY|ShiftMask,             XK_r,          quit,                   {1} },
    { MODKEY,                       XK_f,          spawn,                  {.v = filemanagercmd } },
    { MODKEY,                       XK_d,          spawn,                  {.v = dmenucmd } },
    { MODKEY,                       XK_b,          spawn,                  {.v = floatingbrowser } },
    { MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
    { MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
    { MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
    { MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Return,     zoom,                   {0} },
    { MODKEY,                       XK_Tab,        view,                   {0} },

    /* Layout Selection */
    { MODKEY,                       XK_Return,     setlayout,              {.v = &layouts[0]} }, // Tile
    { MODKEY,                       XK_o,          setlayout,              {.v = &layouts[1]} }, // Floating
    { MODKEY,                       XK_m,          setlayout,              {.v = &layouts[2]} }, // Monocle
    { MODKEY,                       XK_s,          setlayout,              {.v = &layouts[3]} }, // Spiral
    { MODKEY|ShiftMask,             XK_s,          setlayout,              {.v = &layouts[4]} }, // Dwindle
    { MODKEY,                       XK_space,      setlayout,              {0} },
    { MODKEY|ShiftMask,             XK_space,      togglefloating,         {0} },

    /* Monitor and Tags */
    { MODKEY,                       XK_0,          view,                   {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~0 } },
    { MODKEY,                       XK_comma,      focusmon,               {.i = -1 } },
    { MODKEY,                       XK_period,     focusmon,               {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } },

    /* Media keys */
    { 0,                            XF86XK_AudioMute,          spawn,      SHCMD("pactl set-sink-mute 0 toggle") },
    { 0,                            XF86XK_AudioLowerVolume,   spawn,      SHCMD("pactl set-sink-volume 0 -3%") },
    { 0,                            XF86XK_AudioRaiseVolume,   spawn,      SHCMD("pactl set-sink-volume 0 +3%") },
    { 0,                            XF86XK_MonBrightnessUp,    spawn,      SHCMD("brightnessctl g +5%") },
    { 0,                            XF86XK_MonBrightnessDown,  spawn,      SHCMD("brightnessctl g 5%-") },
    { 0,                            XK_Print,                  spawn,      {.v = flameshot} },
    { 0,                            XK_ISO_Next_Group,         spawn,      SHCMD("pkill -RTMIN+10 dwmblocks") },

    /* Tag Keys (Z, X, C) */
    TAGKEYS(                        XK_z,                                  0)
    TAGKEYS(                        XK_x,                                  1)
    TAGKEYS(                        XK_c,                                  2)    
};

/* Button definitions */
static const Button buttons[] = {
    { ClkLtSymbol,          0,                    Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,                    Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,                    Button1,        togglewin,      {0} },
    { ClkWinTitle,          0,                    Button3,        showhideclient, {0} },
    { ClkWinTitle,          0,                    Button2,        zoom,           {0} },
    { ClkStatusText,        0,                    Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,               Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,               Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,               Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,                    Button1,        view,           {0} },
    { ClkTagBar,            0,                    Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,               Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,               Button3,        toggletag,      {0} },
};
