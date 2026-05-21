
/* =========================
 * APPEARANCE
 * ========================= */

static const unsigned int borderpx  = 2;
static const unsigned int snap      = 32;
static const int showbar            = 1;
static const int topbar             = 1;

/* FONT */
static const char *fonts[] = {
    "MartianMono Nerd Font:size=11"
};

/* =========================
 * COLORS (HOLLOW / OUTLINE STYLE)
 * ========================= */

static const char col_bg[]     = "#0f111a";
static const char col_fg[]     = "#c0caf5";
static const char col_muted[]  = "#565f89";

static const char col_blue[]   = "#7aa2f7";
static const char col_green[]  = "#9ece6a";
static const char col_red[]    = "#f7768e";

/*
 * IMPORTANT CHANGE:
 * bg == bg everywhere → removes fill effect
 * only border/fg changes = outline look
 */
static const char *colors[][3] = {
    /*               fg         bg         border */
    [SchemeNorm] = { col_fg, col_bg, col_bg },
    [SchemeSel]  = { col_blue, col_bg, col_blue },
};

/* =========================
 * TAGS (EMPTY TEXT STYLE)
 * ========================= */

static const char *tags[] = {
    "1",
    "2",
    "3",
};
