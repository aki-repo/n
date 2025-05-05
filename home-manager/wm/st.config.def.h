* See LICENSE file for copyright and license details. */
      2 
      3 /*
      4  * appearance
      5  *
      6  * font: see http://freedesktop.org/software/fontconfig/fontconfig-user.html
      7  */
      8 static char *font = "Liberation Mono:pixelsize=12:antialias=true:autohint=true";
      9 static int borderpx = 2;
     10 
     11 /*
     12  * What program is execed by st depends of these precedence rules:
     13  * 1: program passed with -e
     14  * 2: scroll and/or utmp
     15  * 3: SHELL environment variable
     16  * 4: value of shell in /etc/passwd
     17  * 5: value of shell in config.h
     18  */
     19 static char *shell = "/bin/sh";
     20 char *utmp = NULL;
     21 /* scroll program: to enable use a string like "scroll" */
     22 char *scroll = NULL;
     23 char *stty_args = "stty raw pass8 nl -echo -iexten -cstopb 38400";
     24 
     25 /* identification sequence returned in DA and DECID */
     26 char *vtiden = "\033[?6c";
     27 
     28 /* Kerning / character bounding-box multipliers */
     29 static float cwscale = 1.0;
     30 static float chscale = 1.0;
     31 
     32 /*
     33  * word delimiter string
     34  *
     35  * More advanced example: L" `'\"()[]{}"
     36  */
     37 wchar_t *worddelimiters = L" ";
     38 
     39 /* selection timeouts (in milliseconds) */
     40 static unsigned int doubleclicktimeout = 300;
     41 static unsigned int tripleclicktimeout = 600;
     42 
     43 /* alt screens */
     44 int allowaltscreen = 1;
     45 
     46 /* allow certain non-interactive (insecure) window operations such as:
     47    setting the clipboard text */
     48 int allowwindowops = 0;
     49 
     50 /*
     51  * draw latency range in ms - from new content/keypress/etc until drawing.
     52  * within this range, st draws when content stops arriving (idle). mostly it's
     53  * near minlatency, but it waits longer for slow updates to avoid partial draw.
     54  * low minlatency will tear/flicker more, as it can "detect" idle too early.
     55  */
     56 static double minlatency = 2;
     57 static double maxlatency = 33;
     58 
     59 /*
     60  * blinking timeout (set to 0 to disable blinking) for the terminal blinking
     61  * attribute.
     62  */
     63 static unsigned int blinktimeout = 800;
     64 
     65 /*
     66  * thickness of underline and bar cursors
     67  */
     68 static unsigned int cursorthickness = 2;
     69 
     70 /*
     71  * bell volume. It must be a value between -100 and 100. Use 0 for disabling
     72  * it
     73  */
     74 static int bellvolume = 0;
     75 
     76 /* default TERM value */
     77 char *termname = "st-256color";
     78 
     79 /*
     80  * spaces per tab
     81  *
     82  * When you are changing this value, don't forget to adapt the »it« value in
     83  * the st.info and appropriately install the st.info in the environment where
     84  * you use this st version.
     85  *
     86  *	it#$tabspaces,
     87  *
     88  * Secondly make sure your kernel is not expanding tabs. When running `stty
     89  * -a` »tab0« should appear. You can tell the terminal to not expand tabs by
     90  *  running following command:
     91  *
     92  *	stty tabs
     93  */
     94 unsigned int tabspaces = 8;
     95 
     96 /* Terminal colors (16 first used in escape sequence) */
     97 static const char *colorname[] = {
     98 	/* 8 normal colors */
     99 	"black",
    100 	"red3",
    101 	"green3",
    102 	"yellow3",
    103 	"blue2",
    104 	"magenta3",
    105 	"cyan3",
    106 	"gray90",
    107 
    108 	/* 8 bright colors */
    109 	"gray50",
    110 	"red",
    111 	"green",
    112 	"yellow",
    113 	"#5c5cff",
    114 	"magenta",
    115 	"cyan",
    116 	"white",
    117 
    118 	[255] = 0,
    119 
    120 	/* more colors can be added after 255 to use with DefaultXX */
    121 	"#cccccc",
    122 	"#555555",
    123 	"gray90", /* default foreground colour */
    124 	"black", /* default background colour */
    125 };
    126 
    127 
    128 /*
    129  * Default colors (colorname index)
    130  * foreground, background, cursor, reverse cursor
    131  */
    132 unsigned int defaultfg = 258;
    133 unsigned int defaultbg = 259;
    134 unsigned int defaultcs = 256;
    135 static unsigned int defaultrcs = 257;
    136 
    137 /*
    138  * Default shape of cursor
    139  * 2: Block ("█")
    140  * 4: Underline ("_")
    141  * 6: Bar ("|")
    142  * 7: Snowman ("☃")
    143  */
    144 static unsigned int cursorshape = 2;
    145 
    146 /*
    147  * Default columns and rows numbers
    148  */
    149 
    150 static unsigned int cols = 80;
    151 static unsigned int rows = 24;
    152 
    153 /*
    154  * Default colour and shape of the mouse cursor
    155  */
    156 static unsigned int mouseshape = XC_xterm;
    157 static unsigned int mousefg = 7;
    158 static unsigned int mousebg = 0;
    159 
    160 /*
    161  * Color used to display font attributes when fontconfig selected a font which
    162  * doesn't match the ones requested.
    163  */
    164 static unsigned int defaultattr = 11;
    165 
    166 /*
    167  * Force mouse select/shortcuts while mask is active (when MODE_MOUSE is set).
    168  * Note that if you want to use ShiftMask with selmasks, set this to an other
    169  * modifier, set to 0 to not use it.
    170  */
    171 static uint forcemousemod = ShiftMask;
    172 
    173 /*
    174  * Internal mouse shortcuts.
    175  * Beware that overloading Button1 will disable the selection.
    176  */
    177 static MouseShortcut mshortcuts[] = {
    178 	/* mask                 button   function        argument       release */
    179 	{ XK_ANY_MOD,           Button2, selpaste,       {.i = 0},      1 },
    180 	{ ShiftMask,            Button4, ttysend,        {.s = "\033[5;2~"} },
    181 	{ XK_ANY_MOD,           Button4, ttysend,        {.s = "\031"} },
    182 	{ ShiftMask,            Button5, ttysend,        {.s = "\033[6;2~"} },
    183 	{ XK_ANY_MOD,           Button5, ttysend,        {.s = "\005"} },
    184 };
    185 
    186 /* Internal keyboard shortcuts. */
    187 #define MODKEY Mod1Mask
    188 #define TERMMOD (ControlMask|ShiftMask)
    189 
    190 static Shortcut shortcuts[] = {
    191 	/* mask                 keysym          function        argument */
    192 	{ XK_ANY_MOD,           XK_Break,       sendbreak,      {.i =  0} },
    193 	{ ControlMask,          XK_Print,       toggleprinter,  {.i =  0} },
    194 	{ ShiftMask,            XK_Print,       printscreen,    {.i =  0} },
    195 	{ XK_ANY_MOD,           XK_Print,       printsel,       {.i =  0} },
    196 	{ TERMMOD,              XK_Prior,       zoom,           {.f = +1} },
    197 	{ TERMMOD,              XK_Next,        zoom,           {.f = -1} },
    198 	{ TERMMOD,              XK_Home,        zoomreset,      {.f =  0} },
    199 	{ TERMMOD,              XK_C,           clipcopy,       {.i =  0} },
    200 	{ TERMMOD,              XK_V,           clippaste,      {.i =  0} },
    201 	{ TERMMOD,              XK_Y,           selpaste,       {.i =  0} },
    202 	{ ShiftMask,            XK_Insert,      selpaste,       {.i =  0} },
    203 	{ TERMMOD,              XK_Num_Lock,    numlock,        {.i =  0} },
    204 };
    205 
    206 /*
    207  * Special keys (change & recompile st.info accordingly)
    208  *
    209  * Mask value:
    210  * * Use XK_ANY_MOD to match the key no matter modifiers state
    211  * * Use XK_NO_MOD to match the key alone (no modifiers)
    212  * appkey value:
    213  * * 0: no value
    214  * * > 0: keypad application mode enabled
    215  * *   = 2: term.numlock = 1
    216  * * < 0: keypad application mode disabled
    217  * appcursor value:
    218  * * 0: no value
    219  * * > 0: cursor application mode enabled
    220  * * < 0: cursor application mode disabled
    221  *
    222  * Be careful with the order of the definitions because st searches in
    223  * this table sequentially, so any XK_ANY_MOD must be in the last
    224  * position for a key.
    225  */
    226 
    227 /*
    228  * If you want keys other than the X11 function keys (0xFD00 - 0xFFFF)
    229  * to be mapped below, add them to this array.
    230  */
    231 static KeySym mappedkeys[] = { -1 };
    232 
    233 /*
    234  * State bits to ignore when matching key or button events.  By default,
    235  * numlock (Mod2Mask) and keyboard layout (XK_SWITCH_MOD) are ignored.
    236  */
    237 static uint ignoremod = Mod2Mask|XK_SWITCH_MOD;
    238 
    239 /*
    240  * This is the huge key array which defines all compatibility to the Linux
    241  * world. Please decide about changes wisely.
    242  */
    243 static Key key[] = {
    244 	/* keysym           mask            string      appkey appcursor */
    245 	{ XK_KP_Home,       ShiftMask,      "\033[2J",       0,   -1},
    246 	{ XK_KP_Home,       ShiftMask,      "\033[1;2H",     0,   +1},
    247 	{ XK_KP_Home,       XK_ANY_MOD,     "\033[H",        0,   -1},
    248 	{ XK_KP_Home,       XK_ANY_MOD,     "\033[1~",       0,   +1},
    249 	{ XK_KP_Up,         XK_ANY_MOD,     "\033Ox",       +1,    0},
    250 	{ XK_KP_Up,         XK_ANY_MOD,     "\033[A",        0,   -1},
    251 	{ XK_KP_Up,         XK_ANY_MOD,     "\033OA",        0,   +1},
    252 	{ XK_KP_Down,       XK_ANY_MOD,     "\033Or",       +1,    0},
    253 	{ XK_KP_Down,       XK_ANY_MOD,     "\033[B",        0,   -1},
    254 	{ XK_KP_Down,       XK_ANY_MOD,     "\033OB",        0,   +1},
    255 	{ XK_KP_Left,       XK_ANY_MOD,     "\033Ot",       +1,    0},
    256 	{ XK_KP_Left,       XK_ANY_MOD,     "\033[D",        0,   -1},
    257 	{ XK_KP_Left,       XK_ANY_MOD,     "\033OD",        0,   +1},
    258 	{ XK_KP_Right,      XK_ANY_MOD,     "\033Ov",       +1,    0},
    259 	{ XK_KP_Right,      XK_ANY_MOD,     "\033[C",        0,   -1},
    260 	{ XK_KP_Right,      XK_ANY_MOD,     "\033OC",        0,   +1},
    261 	{ XK_KP_Prior,      ShiftMask,      "\033[5;2~",     0,    0},
    262 	{ XK_KP_Prior,      XK_ANY_MOD,     "\033[5~",       0,    0},
    263 	{ XK_KP_Begin,      XK_ANY_MOD,     "\033[E",        0,    0},
    264 	{ XK_KP_End,        ControlMask,    "\033[J",       -1,    0},
    265 	{ XK_KP_End,        ControlMask,    "\033[1;5F",    +1,    0},
    266 	{ XK_KP_End,        ShiftMask,      "\033[K",       -1,    0},
    267 	{ XK_KP_End,        ShiftMask,      "\033[1;2F",    +1,    0},
    268 	{ XK_KP_End,        XK_ANY_MOD,     "\033[4~",       0,    0},
    269 	{ XK_KP_Next,       ShiftMask,      "\033[6;2~",     0,    0},
    270 	{ XK_KP_Next,       XK_ANY_MOD,     "\033[6~",       0,    0},
    271 	{ XK_KP_Insert,     ShiftMask,      "\033[2;2~",    +1,    0},
    272 	{ XK_KP_Insert,     ShiftMask,      "\033[4l",      -1,    0},
    273 	{ XK_KP_Insert,     ControlMask,    "\033[L",       -1,    0},
    274 	{ XK_KP_Insert,     ControlMask,    "\033[2;5~",    +1,    0},
    275 	{ XK_KP_Insert,     XK_ANY_MOD,     "\033[4h",      -1,    0},
    276 	{ XK_KP_Insert,     XK_ANY_MOD,     "\033[2~",      +1,    0},
    277 	{ XK_KP_Delete,     ControlMask,    "\033[M",       -1,    0},
    278 	{ XK_KP_Delete,     ControlMask,    "\033[3;5~",    +1,    0},
    279 	{ XK_KP_Delete,     ShiftMask,      "\033[2K",      -1,    0},
    280 	{ XK_KP_Delete,     ShiftMask,      "\033[3;2~",    +1,    0},
    281 	{ XK_KP_Delete,     XK_ANY_MOD,     "\033[P",       -1,    0},
    282 	{ XK_KP_Delete,     XK_ANY_MOD,     "\033[3~",      +1,    0},
    283 	{ XK_KP_Multiply,   XK_ANY_MOD,     "\033Oj",       +2,    0},
    284 	{ XK_KP_Add,        XK_ANY_MOD,     "\033Ok",       +2,    0},
    285 	{ XK_KP_Enter,      XK_ANY_MOD,     "\033OM",       +2,    0},
    286 	{ XK_KP_Enter,      XK_ANY_MOD,     "\r",           -1,    0},
    287 	{ XK_KP_Subtract,   XK_ANY_MOD,     "\033Om",       +2,    0},
    288 	{ XK_KP_Decimal,    XK_ANY_MOD,     "\033On",       +2,    0},
    289 	{ XK_KP_Divide,     XK_ANY_MOD,     "\033Oo",       +2,    0},
    290 	{ XK_KP_0,          XK_ANY_MOD,     "\033Op",       +2,    0},
    291 	{ XK_KP_1,          XK_ANY_MOD,     "\033Oq",       +2,    0},
    292 	{ XK_KP_2,          XK_ANY_MOD,     "\033Or",       +2,    0},
    293 	{ XK_KP_3,          XK_ANY_MOD,     "\033Os",       +2,    0},
    294 	{ XK_KP_4,          XK_ANY_MOD,     "\033Ot",       +2,    0},
    295 	{ XK_KP_5,          XK_ANY_MOD,     "\033Ou",       +2,    0},
    296 	{ XK_KP_6,          XK_ANY_MOD,     "\033Ov",       +2,    0},
    297 	{ XK_KP_7,          XK_ANY_MOD,     "\033Ow",       +2,    0},
    298 	{ XK_KP_8,          XK_ANY_MOD,     "\033Ox",       +2,    0},
    299 	{ XK_KP_9,          XK_ANY_MOD,     "\033Oy",       +2,    0},
    300 	{ XK_Up,            ShiftMask,      "\033[1;2A",     0,    0},
    301 	{ XK_Up,            Mod1Mask,       "\033[1;3A",     0,    0},
    302 	{ XK_Up,         ShiftMask|Mod1Mask,"\033[1;4A",     0,    0},
    303 	{ XK_Up,            ControlMask,    "\033[1;5A",     0,    0},
    304 	{ XK_Up,      ShiftMask|ControlMask,"\033[1;6A",     0,    0},
    305 	{ XK_Up,       ControlMask|Mod1Mask,"\033[1;7A",     0,    0},
    306 	{ XK_Up,ShiftMask|ControlMask|Mod1Mask,"\033[1;8A",  0,    0},
    307 	{ XK_Up,            XK_ANY_MOD,     "\033[A",        0,   -1},
    308 	{ XK_Up,            XK_ANY_MOD,     "\033OA",        0,   +1},
    309 	{ XK_Down,          ShiftMask,      "\033[1;2B",     0,    0},
    310 	{ XK_Down,          Mod1Mask,       "\033[1;3B",     0,    0},
    311 	{ XK_Down,       ShiftMask|Mod1Mask,"\033[1;4B",     0,    0},
    312 	{ XK_Down,          ControlMask,    "\033[1;5B",     0,    0},
    313 	{ XK_Down,    ShiftMask|ControlMask,"\033[1;6B",     0,    0},
    314 	{ XK_Down,     ControlMask|Mod1Mask,"\033[1;7B",     0,    0},
    315 	{ XK_Down,ShiftMask|ControlMask|Mod1Mask,"\033[1;8B",0,    0},
    316 	{ XK_Down,          XK_ANY_MOD,     "\033[B",        0,   -1},
    317 	{ XK_Down,          XK_ANY_MOD,     "\033OB",        0,   +1},
    318 	{ XK_Left,          ShiftMask,      "\033[1;2D",     0,    0},
    319 	{ XK_Left,          Mod1Mask,       "\033[1;3D",     0,    0},
    320 	{ XK_Left,       ShiftMask|Mod1Mask,"\033[1;4D",     0,    0},
    321 	{ XK_Left,          ControlMask,    "\033[1;5D",     0,    0},
    322 	{ XK_Left,    ShiftMask|ControlMask,"\033[1;6D",     0,    0},
    323 	{ XK_Left,     ControlMask|Mod1Mask,"\033[1;7D",     0,    0},
    324 	{ XK_Left,ShiftMask|ControlMask|Mod1Mask,"\033[1;8D",0,    0},
    325 	{ XK_Left,          XK_ANY_MOD,     "\033[D",        0,   -1},
    326 	{ XK_Left,          XK_ANY_MOD,     "\033OD",        0,   +1},
    327 	{ XK_Right,         ShiftMask,      "\033[1;2C",     0,    0},
    328 	{ XK_Right,         Mod1Mask,       "\033[1;3C",     0,    0},
    329 	{ XK_Right,      ShiftMask|Mod1Mask,"\033[1;4C",     0,    0},
    330 	{ XK_Right,         ControlMask,    "\033[1;5C",     0,    0},
    331 	{ XK_Right,   ShiftMask|ControlMask,"\033[1;6C",     0,    0},
    332 	{ XK_Right,    ControlMask|Mod1Mask,"\033[1;7C",     0,    0},
    333 	{ XK_Right,ShiftMask|ControlMask|Mod1Mask,"\033[1;8C",0,   0},
    334 	{ XK_Right,         XK_ANY_MOD,     "\033[C",        0,   -1},
    335 	{ XK_Right,         XK_ANY_MOD,     "\033OC",        0,   +1},
    336 	{ XK_ISO_Left_Tab,  ShiftMask,      "\033[Z",        0,    0},
    337 	{ XK_Return,        Mod1Mask,       "\033\r",        0,    0},
    338 	{ XK_Return,        XK_ANY_MOD,     "\r",            0,    0},
    339 	{ XK_Insert,        ShiftMask,      "\033[4l",      -1,    0},
    340 	{ XK_Insert,        ShiftMask,      "\033[2;2~",    +1,    0},
    341 	{ XK_Insert,        ControlMask,    "\033[L",       -1,    0},
    342 	{ XK_Insert,        ControlMask,    "\033[2;5~",    +1,    0},
    343 	{ XK_Insert,        XK_ANY_MOD,     "\033[4h",      -1,    0},
    344 	{ XK_Insert,        XK_ANY_MOD,     "\033[2~",      +1,    0},
    345 	{ XK_Delete,        ControlMask,    "\033[M",       -1,    0},
    346 	{ XK_Delete,        ControlMask,    "\033[3;5~",    +1,    0},
    347 	{ XK_Delete,        ShiftMask,      "\033[2K",      -1,    0},
    348 	{ XK_Delete,        ShiftMask,      "\033[3;2~",    +1,    0},
    349 	{ XK_Delete,        XK_ANY_MOD,     "\033[P",       -1,    0},
    350 	{ XK_Delete,        XK_ANY_MOD,     "\033[3~",      +1,    0},
    351 	{ XK_BackSpace,     XK_NO_MOD,      "\177",          0,    0},
    352 	{ XK_BackSpace,     Mod1Mask,       "\033\177",      0,    0},
    353 	{ XK_Home,          ShiftMask,      "\033[2J",       0,   -1},
    354 	{ XK_Home,          ShiftMask,      "\033[1;2H",     0,   +1},
    355 	{ XK_Home,          XK_ANY_MOD,     "\033[H",        0,   -1},
    356 	{ XK_Home,          XK_ANY_MOD,     "\033[1~",       0,   +1},
    357 	{ XK_End,           ControlMask,    "\033[J",       -1,    0},
    358 	{ XK_End,           ControlMask,    "\033[1;5F",    +1,    0},
    359 	{ XK_End,           ShiftMask,      "\033[K",       -1,    0},
    360 	{ XK_End,           ShiftMask,      "\033[1;2F",    +1,    0},
    361 	{ XK_End,           XK_ANY_MOD,     "\033[4~",       0,    0},
    362 	{ XK_Prior,         ControlMask,    "\033[5;5~",     0,    0},
    363 	{ XK_Prior,         ShiftMask,      "\033[5;2~",     0,    0},
    364 	{ XK_Prior,         XK_ANY_MOD,     "\033[5~",       0,    0},
    365 	{ XK_Next,          ControlMask,    "\033[6;5~",     0,    0},
    366 	{ XK_Next,          ShiftMask,      "\033[6;2~",     0,    0},
    367 	{ XK_Next,          XK_ANY_MOD,     "\033[6~",       0,    0},
    368 	{ XK_F1,            XK_NO_MOD,      "\033OP" ,       0,    0},
    369 	{ XK_F1, /* F13 */  ShiftMask,      "\033[1;2P",     0,    0},
    370 	{ XK_F1, /* F25 */  ControlMask,    "\033[1;5P",     0,    0},
    371 	{ XK_F1, /* F37 */  Mod4Mask,       "\033[1;6P",     0,    0},
    372 	{ XK_F1, /* F49 */  Mod1Mask,       "\033[1;3P",     0,    0},
    373 	{ XK_F1, /* F61 */  Mod3Mask,       "\033[1;4P",     0,    0},
    374 	{ XK_F2,            XK_NO_MOD,      "\033OQ" ,       0,    0},
    375 	{ XK_F2, /* F14 */  ShiftMask,      "\033[1;2Q",     0,    0},
    376 	{ XK_F2, /* F26 */  ControlMask,    "\033[1;5Q",     0,    0},
    377 	{ XK_F2, /* F38 */  Mod4Mask,       "\033[1;6Q",     0,    0},
    378 	{ XK_F2, /* F50 */  Mod1Mask,       "\033[1;3Q",     0,    0},
    379 	{ XK_F2, /* F62 */  Mod3Mask,       "\033[1;4Q",     0,    0},
    380 	{ XK_F3,            XK_NO_MOD,      "\033OR" ,       0,    0},
    381 	{ XK_F3, /* F15 */  ShiftMask,      "\033[1;2R",     0,    0},
    382 	{ XK_F3, /* F27 */  ControlMask,    "\033[1;5R",     0,    0},
    383 	{ XK_F3, /* F39 */  Mod4Mask,       "\033[1;6R",     0,    0},
    384 	{ XK_F3, /* F51 */  Mod1Mask,       "\033[1;3R",     0,    0},
    385 	{ XK_F3, /* F63 */  Mod3Mask,       "\033[1;4R",     0,    0},
    386 	{ XK_F4,            XK_NO_MOD,      "\033OS" ,       0,    0},
    387 	{ XK_F4, /* F16 */  ShiftMask,      "\033[1;2S",     0,    0},
    388 	{ XK_F4, /* F28 */  ControlMask,    "\033[1;5S",     0,    0},
    389 	{ XK_F4, /* F40 */  Mod4Mask,       "\033[1;6S",     0,    0},
    390 	{ XK_F4, /* F52 */  Mod1Mask,       "\033[1;3S",     0,    0},
    391 	{ XK_F5,            XK_NO_MOD,      "\033[15~",      0,    0},
    392 	{ XK_F5, /* F17 */  ShiftMask,      "\033[15;2~",    0,    0},
    393 	{ XK_F5, /* F29 */  ControlMask,    "\033[15;5~",    0,    0},
    394 	{ XK_F5, /* F41 */  Mod4Mask,       "\033[15;6~",    0,    0},
    395 	{ XK_F5, /* F53 */  Mod1Mask,       "\033[15;3~",    0,    0},
    396 	{ XK_F6,            XK_NO_MOD,      "\033[17~",      0,    0},
    397 	{ XK_F6, /* F18 */  ShiftMask,      "\033[17;2~",    0,    0},
    398 	{ XK_F6, /* F30 */  ControlMask,    "\033[17;5~",    0,    0},
    399 	{ XK_F6, /* F42 */  Mod4Mask,       "\033[17;6~",    0,    0},
    400 	{ XK_F6, /* F54 */  Mod1Mask,       "\033[17;3~",    0,    0},
    401 	{ XK_F7,            XK_NO_MOD,      "\033[18~",      0,    0},
    402 	{ XK_F7, /* F19 */  ShiftMask,      "\033[18;2~",    0,    0},
    403 	{ XK_F7, /* F31 */  ControlMask,    "\033[18;5~",    0,    0},
    404 	{ XK_F7, /* F43 */  Mod4Mask,       "\033[18;6~",    0,    0},
    405 	{ XK_F7, /* F55 */  Mod1Mask,       "\033[18;3~",    0,    0},
    406 	{ XK_F8,            XK_NO_MOD,      "\033[19~",      0,    0},
    407 	{ XK_F8, /* F20 */  ShiftMask,      "\033[19;2~",    0,    0},
    408 	{ XK_F8, /* F32 */  ControlMask,    "\033[19;5~",    0,    0},
    409 	{ XK_F8, /* F44 */  Mod4Mask,       "\033[19;6~",    0,    0},
    410 	{ XK_F8, /* F56 */  Mod1Mask,       "\033[19;3~",    0,    0},
    411 	{ XK_F9,            XK_NO_MOD,      "\033[20~",      0,    0},
    412 	{ XK_F9, /* F21 */  ShiftMask,      "\033[20;2~",    0,    0},
    413 	{ XK_F9, /* F33 */  ControlMask,    "\033[20;5~",    0,    0},
    414 	{ XK_F9, /* F45 */  Mod4Mask,       "\033[20;6~",    0,    0},
    415 	{ XK_F9, /* F57 */  Mod1Mask,       "\033[20;3~",    0,    0},
    416 	{ XK_F10,           XK_NO_MOD,      "\033[21~",      0,    0},
    417 	{ XK_F10, /* F22 */ ShiftMask,      "\033[21;2~",    0,    0},
    418 	{ XK_F10, /* F34 */ ControlMask,    "\033[21;5~",    0,    0},
    419 	{ XK_F10, /* F46 */ Mod4Mask,       "\033[21;6~",    0,    0},
    420 	{ XK_F10, /* F58 */ Mod1Mask,       "\033[21;3~",    0,    0},
    421 	{ XK_F11,           XK_NO_MOD,      "\033[23~",      0,    0},
    422 	{ XK_F11, /* F23 */ ShiftMask,      "\033[23;2~",    0,    0},
    423 	{ XK_F11, /* F35 */ ControlMask,    "\033[23;5~",    0,    0},
    424 	{ XK_F11, /* F47 */ Mod4Mask,       "\033[23;6~",    0,    0},
    425 	{ XK_F11, /* F59 */ Mod1Mask,       "\033[23;3~",    0,    0},
    426 	{ XK_F12,           XK_NO_MOD,      "\033[24~",      0,    0},
    427 	{ XK_F12, /* F24 */ ShiftMask,      "\033[24;2~",    0,    0},
    428 	{ XK_F12, /* F36 */ ControlMask,    "\033[24;5~",    0,    0},
    429 	{ XK_F12, /* F48 */ Mod4Mask,       "\033[24;6~",    0,    0},
    430 	{ XK_F12, /* F60 */ Mod1Mask,       "\033[24;3~",    0,    0},
    431 	{ XK_F13,           XK_NO_MOD,      "\033[1;2P",     0,    0},
    432 	{ XK_F14,           XK_NO_MOD,      "\033[1;2Q",     0,    0},
    433 	{ XK_F15,           XK_NO_MOD,      "\033[1;2R",     0,    0},
    434 	{ XK_F16,           XK_NO_MOD,      "\033[1;2S",     0,    0},
    435 	{ XK_F17,           XK_NO_MOD,      "\033[15;2~",    0,    0},
    436 	{ XK_F18,           XK_NO_MOD,      "\033[17;2~",    0,    0},
    437 	{ XK_F19,           XK_NO_MOD,      "\033[18;2~",    0,    0},
    438 	{ XK_F20,           XK_NO_MOD,      "\033[19;2~",    0,    0},
    439 	{ XK_F21,           XK_NO_MOD,      "\033[20;2~",    0,    0},
    440 	{ XK_F22,           XK_NO_MOD,      "\033[21;2~",    0,    0},
    441 	{ XK_F23,           XK_NO_MOD,      "\033[23;2~",    0,    0},
    442 	{ XK_F24,           XK_NO_MOD,      "\033[24;2~",    0,    0},
    443 	{ XK_F25,           XK_NO_MOD,      "\033[1;5P",     0,    0},
    444 	{ XK_F26,           XK_NO_MOD,      "\033[1;5Q",     0,    0},
    445 	{ XK_F27,           XK_NO_MOD,      "\033[1;5R",     0,    0},
    446 	{ XK_F28,           XK_NO_MOD,      "\033[1;5S",     0,    0},
    447 	{ XK_F29,           XK_NO_MOD,      "\033[15;5~",    0,    0},
    448 	{ XK_F30,           XK_NO_MOD,      "\033[17;5~",    0,    0},
    449 	{ XK_F31,           XK_NO_MOD,      "\033[18;5~",    0,    0},
    450 	{ XK_F32,           XK_NO_MOD,      "\033[19;5~",    0,    0},
    451 	{ XK_F33,           XK_NO_MOD,      "\033[20;5~",    0,    0},
    452 	{ XK_F34,           XK_NO_MOD,      "\033[21;5~",    0,    0},
    453 	{ XK_F35,           XK_NO_MOD,      "\033[23;5~",    0,    0},
    454 };
    455 
    456 /*
    457  * Selection types' masks.
    458  * Use the same masks as usual.
    459  * Button1Mask is always unset, to make masks match between ButtonPress.
    460  * ButtonRelease and MotionNotify.
    461  * If no match is found, regular selection is used.
    462  */
    463 static uint selmasks[] = {
    464 	[SEL_RECTANGULAR] = Mod1Mask,
    465 };
    466 
    467 /*
    468  * Printable characters in ASCII, used to estimate the advance width
    469  * of single wide characters.
    470  */
    471 static char ascii_printable[] =
    472 	" !\"#$%&'()*+,-./0123456789:;<=>?"
    473 	"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
    474 	"`abcdefghijklmnopqrstuvwxyz{|}~";
