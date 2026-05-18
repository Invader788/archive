//Modify this file to change what commands output to your statusbar, and recompile using the make command.

static const Block blocks[] = {

    // Battery
    {
        " ",
        "sh -c '\
        CAP=$(cat /sys/class/power_supply/BAT0/capacity); \
        STATUS=$(cat /sys/class/power_supply/BAT0/status); \
        if [ \"$STATUS\" = \"Charging\" ]; then ICON=\"󰂄\"; \
        elif [ $CAP -ge 90 ]; then ICON=\"󰁹\"; \
        elif [ $CAP -ge 70 ]; then ICON=\"󰂀\"; \
        elif [ $CAP -ge 50 ]; then ICON=\"󰁾\"; \
        elif [ $CAP -ge 30 ]; then ICON=\"󰁼\"; \
        else ICON=\"󰁺\"; fi; \
        echo \"^c#a6e3a1^${ICON} ${CAP}%^d^\"'",
        30,
        0
    },

//Wifi
    
    {
    "",
    "sh -c '\
    SIGNAL=$(nmcli -t -f active,signal dev wifi | grep \"^yes\" | cut -d: -f2); \
    if [ -z \"$SIGNAL\" ]; then \
        echo \"^c#f38ba8^󰖪 Offline^d^\"; \
    else \
        if [ $SIGNAL -ge 75 ]; then ICON=\"󰤨\"; \
        elif [ $SIGNAL -ge 50 ]; then ICON=\"󰤥\"; \
        elif [ $SIGNAL -ge 25 ]; then ICON=\"󰤢\"; \
        else ICON=\"󰤟\"; fi; \
        echo \"^c#89b4fa^${ICON} ${SIGNAL}%^d^\"; \
    fi'",
    10,
    0
},

    // Date
    {
        "",
        "sh -c 'echo \"^c#f9e2af^󰃭 $(date +\"%Y-%m-%d\")^d^\"'",
        60,
        0
    },

    // Time
    {
        "",
        "sh -c 'echo \"^c#f38ba8^󰥔 $(date +\"%H:%M\") ^d^\"'",
        5,
        0
    },
};

// Delimiter between blocks
static char delim[] = "^c#6c7086^ | ^d^";
static unsigned int delimLen = 18;
