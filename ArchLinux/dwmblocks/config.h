// dwmblocks blocks.h

static const Block blocks[] = {

    // Left padding
    {
        "   ",
        "",
        5,
        0
    },

    // Wi-Fi — gray
    {
        "",
        "sh -c 'printf \"^b#757575^^c#1e1e2e^ 󰤨 %s ^d^\" \"$(iwgetid -r 2>/dev/null || echo Offline)\"'",
        5,
        0
    },

    // Padding
    {
        "  ",
        "",
        5,
        0
    },

    // Battery — green
    {
        "",
        "sh -c 'printf \"^b#757575^^c#1e1e2e^ 󰁹 %s%% ^d^\" \"$(cat /sys/class/power_supply/BAT0/capacity)\"'",
        10,
        0
    },

    // Padding
    {
        "  ",
        "",
        5,
        0
    },

    // Date — gray
    {
        "",
        "sh -c 'printf \"^b#757575^^c#1e1e2e^ 󰃭 %s ^d^\" \"$(date +\"%Y-%m-%d\")\"'",
        60,
        0
    },

    // Padding
    {
        "  ",
        "",
        5,
        0
    },

    // Time — gray
    {
        "",
        "sh -c 'printf \"^b#757575^^c#1e1e2e^ 󰥔 %s ^d^\" \"$(date +\"%H:%M\")\"'",
        5,
        0
    },

    // Right padding
    {
        "",
        "",
        5,
        0
    },
};

// No delimiter
static char delim[] = "";
static unsigned int delimLen = 1;
