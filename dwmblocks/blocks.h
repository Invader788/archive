static const Block blocks[] = {

    // Battery
    {
        "",
        "sh -c 'CAP=$(cat /sys/class/power_supply/BAT0/capacity); "
        "echo \"^c#a6e3a1^󰁹 ${CAP}%^d^\"'",
        30,
        0
    },

    // WiFi
    {
        "",
        "sh -c 'SSID=$(iwgetid -r); "
        "echo \"^c#89b4fa^󰖩 ${SSID}^d^\"'",
        30,
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

// Delimiter
static char delim[] = "^c#6c7086^ | ^d^";
static unsigned int delimLen = 18;
