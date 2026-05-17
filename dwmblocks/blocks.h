static const Block blocks[] = {

  //Battery
    {" ", "echo \"$(cat /sys/class/power_supply/BAT0/capacity)%\"", 15, 0},
  
    //Date (YY-MM-DD)
    {" ", "date '+%y-%m-%d'", 60, 0},

    //Time (HH:MM)
    {" ", "date '+%H:%M  '", 5, 0},
};

// Delimiter between status blocks
static char delim[] = "  | ";
static unsigned int delimLen = 7;
