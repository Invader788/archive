// This file defines the commands that output information to the status bar.
// After modifying this file, recompile the program using: make

static const Block blocks[] = {

  /*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/ //<-- header comment explaining the columns in your blocks

    // Keyboard layout indicator
    // Checks the keyboard LED state using xset and prints:
    // [RU] if Russian layout is active
    // [EN] if English layout is active
  /*    {"┇  ", "xset -q | grep LED | awk '{ if (substr($10,5,1) == 1) print \"[RU]\"; else print \"[EN]\"; }'", 0, 1}, */

    // Battery percentage
    // Reads battery capacity from system power supply information
    //{"", "echo \"$(cat /sys/class/power_supply/BAT0/capacity)%\"", 15, 0},

    // Weather temperature for Bradford Ontario
    // Uses wttr.in API and updates every 5 minutes (300 seconds)
    // {" ", "curl -m 2 -s 'wttr.in/Bradford-ON?format=%t'", 300, 0}, //-m 2 → maximum 2 seconds. prints the current temperature.
    //{" ", "curl -m 2 -s 'wttr.in/Bradford-ON?format=%c %t %C'", 300, 0}, //-m 2 → maximum 2 seconds. prints the icon + temp + condition.
  
    // Current date (YY-MM-DD)
    // Updates every 60 seconds
    {"", "date '+%y-%m-%d'", 60, 0},

    // Current time (HH:MM)
    // Updates every 5 seconds
    {"", "date '+%H:%M  '", 5, 0},
};


// Delimiter between status blocks
// '\0' means no delimiter
static char delim[] = "  |  ";
static unsigned int delimLen = 7;
