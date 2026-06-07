// Modify this file to change what commands output to your statusbar

static const Block blocks[] = {

    // spacer
    {
        " ",
        "",
        5,
        0
    },

    // Battery
    {
        "",
        "sh -c '\
        CAP=$(cat /sys/class/power_supply/BAT0/capacity); \
        STATUS=$(cat /sys/class/power_supply/BAT0/status); \
        if [ \"$STATUS\" = \"Charging\" ]; then ICON=\"󰂄\"; \
        elif [ $CAP -ge 90 ]; then ICON=\"󰁹\"; \
        elif [ $CAP -ge 70 ]; then ICON=\"󰂀\"; \
        elif [ $CAP -ge 50 ]; then ICON=\"󰁾\"; \
        elif [ $CAP -ge 30 ]; then ICON=\"󰁼\"; \
        else ICON=\"󰁺\"; fi; \
        echo \"${ICON} ${CAP}%\"'",
        30,
        0
    },

    // Wifi
    {
        "",
        "sh -c '\
        SIGNAL=$(nmcli -t -f active,signal dev wifi | grep \"^yes\" | cut -d: -f2); \
        if [ -z \"$SIGNAL\" ]; then \
            echo \"󰖪 Offline\"; \
        else \
            if [ $SIGNAL -ge 75 ]; then ICON=\"󰤨\"; \
            elif [ $SIGNAL -ge 50 ]; then ICON=\"󰤥\"; \
            elif [ $SIGNAL -ge 25 ]; then ICON=\"󰤢\"; \
            else ICON=\"󰤟\"; fi; \
            echo \"${ICON} ${SIGNAL}%\"; \
        fi'",
        10,
        0
    },

    // Date
    {
        "",
        "sh -c 'date +\"󰃭 %Y-%m-%d\"'",
        60,
        0
    },

    // Time
    {
        "",
        "sh -c 'date +\"󰥔 %H:%M\"'",
        5,
        0
    },

    // spacer
    {
        " ",
        "",
        5,
        0
    },
};

// delimiter
static char delim[] = "   ";
static unsigned int delimLen = 3;
