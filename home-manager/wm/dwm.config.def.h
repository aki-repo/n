/* See LICENSE file for copyright and license details. */
      2 
      3 /* appearance */
      4 static const unsigned int borderpx  = 1;        /* border pixel of windows */
      5 static const unsigned int snap      = 32;       /* snap pixel */
      6 static const int showbar            = 1;        /* 0 means no bar */
      7 static const int topbar             = 1;        /* 0 means bottom bar */
      8 static const char *fonts[]          = { "monospace:size=10" };
      9 static const char dmenufont[]       = "monospace:size=10";
     10 static const char col_gray1[]       = "#222222";
     11 static const char col_gray2[]       = "#444444";
     12 static const char col_gray3[]       = "#bbbbbb";
     13 static const char col_gray4[]       = "#eeeeee";
     14 static const char col_cyan[]        = "#005577";
     15 static const char *colors[][3]      = {
     16 	/*               fg         bg         border   */
     17 	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
     18 	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
     19 };
     20 
     21 /* tagging */
     22 static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
     23 
     24 static const Rule rules[] = {
     25 	/* xprop(1):
     26 	 *	WM_CLASS(STRING) = instance, class
     27 	 *	WM_NAME(STRING) = title
     28 	 */
     29 	/* class      instance    title       tags mask     isfloating   monitor */
     30 	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
     31 	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
     32 };
     33 
     34 /* layout(s) */
     35 static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
     36 static const int nmaster     = 1;    /* number of clients in master area */
     37 static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
     38 static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
     39 
     40 static const Layout layouts[] = {
     41 	/* symbol     arrange function */
     42 	{ "[]=",      tile },    /* first entry is default */
     43 	{ "><>",      NULL },    /* no layout function means floating behavior */
     44 	{ "[M]",      monocle },
     45 };
     46 
     47 /* key definitions */
     48 #define MODKEY Mod4Mask
     49 #define TAGKEYS(KEY,TAG) \
     50 	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
     51 	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
     52 	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
     53 	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
     54 
     55 /* helper for spawning shell commands in the pre dwm-5.0 fashion */
     56 #define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
     57 
     58 /* commands */
     59 static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
     60 static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
     61 static const char *termcmd[]  = { "st", NULL };
     62 
     63 static const Key keys[] = {
     64 	/* modifier                     key        function        argument */
     65 	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
     66 	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
     67 	{ MODKEY,                       XK_b,      togglebar,      {0} },
     68 	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
     69 	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
     70 	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
     71 	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
     72 	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
     73 	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
     74 	{ MODKEY,                       XK_Return, zoom,           {0} },
     75 	{ MODKEY,                       XK_Tab,    view,           {0} },
     76 	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
     77 	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
     78 	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
     79 	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
     80 	{ MODKEY,                       XK_space,  setlayout,      {0} },
     81 	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
     82 	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
     83 	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
     84 	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
     85 	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
     86 	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
     87 	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
     88 	TAGKEYS(                        XK_1,                      0)
     89 	TAGKEYS(                        XK_2,                      1)
     90 	TAGKEYS(                        XK_3,                      2)
     91 	TAGKEYS(                        XK_4,                      3)
     92 	TAGKEYS(                        XK_5,                      4)
     93 	TAGKEYS(                        XK_6,                      5)
     94 	TAGKEYS(                        XK_7,                      6)
     95 	TAGKEYS(                        XK_8,                      7)
     96 	TAGKEYS(                        XK_9,                      8)
     97 	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
     98 };
     99 
    100 /* button definitions */
    101 /* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
    102 static const Button buttons[] = {
    103 	/* click                event mask      button          function        argument */
    104 	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    105 	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    106 	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
    107 	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    108 	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    109 	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    110 	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    111 	{ ClkTagBar,            0,              Button1,        view,           {0} },
    112 	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
    113 	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    114 	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    115 };
    116 
