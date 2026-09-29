/* =========================
 * DWM BLOCKS
 * ========================= */

static const Block blocks[] = {

    /* Left padding */
    {
        "   ",
        "",
        5,
        0
    },


       /* =========================
     * TEMPORARY VOLUME
     * ========================= */
    {
        "",
        "sh -c '\
        file=/tmp/dwm-volume; \
        [ ! -f \"$file\" ] && exit 0; \
        now=$(date +%s); \
        then=$(cat \"$file\" 2>/dev/null); \
        [ -z \"$then\" ] && exit 0; \
        [ $((now - then)) -ge 2 ] && exit 0; \
        volume=$(wpctl get-volume @DEFAULT_AUDIO_SINK@ 2>/dev/null | awk '\\''{printf \"%d\", $2 * 100 + 0.5}'\\''); \
        [ -z \"$volume\" ] && exit 0; \
        if wpctl get-volume @DEFAULT_AUDIO_SINK@ 2>/dev/null | grep -q MUTED; then \
            printf \"^c#D8DEE9^ 󰖁 Muted ^d^\"; \
        else \
            printf \"^c#D8DEE9^ 󰕾 %s%% ^d^\" \"$volume\"; \
        fi \
        '",
        1,
        0
    },

    /* =========================
     * WI-FI
     * ========================= */
    {
        "",
        "sh -c '\
        ssid=$(iwgetid -r 2>/dev/null); \
        [ -z \"$ssid\" ] && command -v nmcli >/dev/null 2>&1 && \
            ssid=$(nmcli -t -f active,ssid dev wifi 2>/dev/null | awk -F: '\\''$1 == \"yes\" {print $2; exit}'\\''); \
        quality=$(awk \"NR==3 {print int(\\$3 * 100 / 70)}\" /proc/net/wireless 2>/dev/null); \
        [ -z \"$quality\" ] && command -v nmcli >/dev/null 2>&1 && \
            quality=$(nmcli -t -f active,signal dev wifi 2>/dev/null | awk -F: '\\''$1 == \"yes\" {print $2; exit}'\\''); \
        [ -z \"$ssid\" ] && { printf \"^c#D8DEE9^ 󰤭 Offline ^d^\"; exit; }; \
        [ -z \"$quality\" ] && quality=0; \
        if [ \"$quality\" -ge 80 ]; then icon=\"󰤨\"; \
        elif [ \"$quality\" -ge 60 ]; then icon=\"󰤥\"; \
        elif [ \"$quality\" -ge 40 ]; then icon=\"󰤢\"; \
        elif [ \"$quality\" -ge 20 ]; then icon=\"󰤟\"; \
        else icon=\"󰤯\"; fi; \
        printf \"^c#D8DEE9^ %s %s ^d^\" \"$icon\" \"$ssid\" \
        '",
        5,
        0
    },

    /* Padding */
    {
        " ",
        "",
        5,
        0
    },

    /* =========================
     * BATTERY
     * ========================= */
    {
        "",
        "sh -c '\
        bat=$(cat /sys/class/power_supply/BAT0/capacity 2>/dev/null || echo 0); \
        status=$(cat /sys/class/power_supply/BAT0/status 2>/dev/null); \
        if [ \"$status\" = \"Charging\" ]; then \
            icon=\"󰂄\"; \
        elif [ \"$bat\" -ge 90 ]; then \
            icon=\"󰁹\"; \
        elif [ \"$bat\" -ge 80 ]; then \
            icon=\"󰂂\"; \
        elif [ \"$bat\" -ge 70 ]; then \
            icon=\"󰂁\"; \
        elif [ \"$bat\" -ge 60 ]; then \
            icon=\"󰂀\"; \
        elif [ \"$bat\" -ge 50 ]; then \
            icon=\"󰁿\"; \
        elif [ \"$bat\" -ge 40 ]; then \
            icon=\"󰁾\"; \
        elif [ \"$bat\" -ge 30 ]; then \
            icon=\"󰁽\"; \
        elif [ \"$bat\" -ge 20 ]; then \
            icon=\"󰁼\"; \
        elif [ \"$bat\" -ge 10 ]; then \
            icon=\"󰁻\"; \
        else \
            icon=\"󰂎\"; \
        fi; \
        printf \"^c#D8DEE9^ %s %s%% ^d^\" \"$icon\" \"$bat\" \
        '",
        10,
        0
    },

 

    /* =========================
     * DATE
     * ========================= */
    {
        "",
        "sh -c 'printf \"^c#D8DEE9^ 󰃭 %s ^d^\" \"$(date +\"%Y-%m-%d\")\"'",
        60,
        0
    },

    /* Padding */
    {
        " ",
        "",
        5,
        0
    },

    /* =========================
     * TIME
     * ========================= */
    {
        "",
        "sh -c 'printf \"^c#D8DEE9^ 󰥔 %s ^d^\" \"$(date +\"%H:%M\")\"'",
        5,
        0
    },

    /* Right padding */
    {
        " ",
        " ",
        5,
        0
    },
};

static char delim[] = "";
static unsigned int delimLen = 1;




