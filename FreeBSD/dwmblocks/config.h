// dwmblocks config.h - Date and Time only with side + between padding

static const Block blocks[] = {
    // Left spacer
    {
        "   ",
        "",
        5,
        0
    },

    // Date
    {
        "",
        "sh -c 'date +\"󰃭 %Y-%m-%d\"'",
        60,
        0
    },

    // Spacer between Date and Time
    {
        "  ",
        "",
        5,
        0
    },

    // Time
    {
        "",
        "sh -c 'date +\"󰥔 %H:%M\"'",
        5,
        0
    },

    // Right spacer
    {
        "   ",
        "",
        5,
        0
    },
};

// delimiter
static char delim[] = " ";
static unsigned int delimLen = 4;

