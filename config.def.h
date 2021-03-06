/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMCLASS "URxvt"
#define TERMINAL "urxvtc"
#define BROWSERCLASS "firefox"
#define BROWSER "firefox"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const char *fonts[]          = {
    "monospace:size=11",
    "FontAwesome:size=13",
    "NotoColorEmoji:size=10:antialias=true:autohint=true"
};
static const char dmenufont[]       = "monospace:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#f79802";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class          instance    title       tags mask     isfloating   monitor */
    { "Virt-manager", NULL,       NULL,       1 << 7,            0,           -1 },
    { "Tor Browser",  NULL,       NULL,            0,            1,           -1 },
    { "qBittorrent",  NULL,       NULL,       1 << 8,            0,           -1 },
    { "Alacritty",    NULL,       NULL,       1 << 2,            0,           -1 },
    { "KeePassXC",    NULL,       NULL,       1 << 6,            0,           -1 },
    { "GeoGebra",     NULL,       NULL,       1 << 8,            0,           -1 },
    { BROWSERCLASS,   NULL,       NULL,       1 << 1,            0,           -1 },
    { "Arandr",       NULL,       NULL,            0,            1,           -1 },
    { "Gimp",         NULL,       NULL,       1 << 5,            0,           -1 },
    { "mpv",          NULL,       NULL,       1 << 4,            0,           -1 },
    { "obs",          NULL,       NULL,       1 << 5,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[T]",      tile },    /* first entry is default */
    { "[F]",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL , NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_e,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_q,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    /* ***** */
    /* BINDINGS FOR DMENU-SCRIPTS - START */
    { MODKEY,                       XK_u,     spawn,           {.v = (const char*[]){ "dmenuunicode", NULL } } },
    /* BINDINGS FOR DMENU-SCRIPTS - END */
    /* BINDINGS FOR DOCUMENTATION - START */
    { MODKEY,                       XK_F1,     spawn,          SHCMD("pdfmom /usr/local/share/dwm/docs.mom | zathura -") },
    /* BINDINGS FOR DOCUMENTATION - END */
    /* BINDINGS FOR GAPS - START */
    { MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
    { MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
    { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
    /* BINDINGS FOR GAPS - END */
    /* BINDINGS FOR PROGRAMS - START */
    { MODKEY|ShiftMask,             XK_b,      spawn,          {.v = (const char*[]){ BROWSER, NULL } } },
    { MODKEY|ShiftMask,             XK_f,      spawn,          {.v = (const char*[]){ "pcmanfm", NULL } } },
    { MODKEY|ShiftMask,             XK_v,      spawn,          {.v = (const char*[]){ "virt-manager", NULL } } },
    { MODKEY|ShiftMask,             XK_c,      spawn,          {.v = (const char*[]){ "alacritty", NULL } } },
    { MODKEY|ShiftMask,             XK_o,      spawn,          {.v = (const char*[]){ "obs", NULL } } },
    { MODKEY|ShiftMask,             XK_k,      spawn,          {.v = (const char*[]){ "keepassxc", NULL } } },
    { MODKEY|ShiftMask,             XK_m,      spawn,          {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
    { MODKEY|ShiftMask,             XK_t,      spawn,          {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
    /* BINDINGS FOR PROGRAMS - END   */
    /* BINDINGS FOR MPD - START */
    { MODKEY,                       XK_F6,     spawn,          {.v = (const char*[]){ "mpc", "toggle", NULL } } },
    { MODKEY,                       XK_F5,     spawn,          {.v = (const char*[]){ "mpc", "next", NULL } } },
    { MODKEY,                       XK_F7,     spawn,          {.v = (const char*[]){ "mpc", "prev", NULL } } },
    { 0,                XF86XK_AudioPrev,      spawn,          {.v = (const char*[]){ "mpc", "prev", NULL } } },
    { 0,                XF86XK_AudioNext,      spawn,          {.v = (const char*[]){ "mpc", "next", NULL } } },
    { 0,                XF86XK_AudioPause,     spawn,          {.v = (const char*[]){ "mpc", "pause", NULL } } },
    { 0,                XF86XK_AudioPlay,      spawn,          {.v = (const char*[]){ "mpc", "play", NULL } } },
    { 0,                XF86XK_AudioStop,      spawn,          {.v = (const char*[]){ "mpc", "stop", NULL } } },
    { 0,                XF86XK_AudioRewind,    spawn,          {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
    { 0,                XF86XK_AudioForward,   spawn,          {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
    { ShiftMask,        XF86XK_AudioRaiseVolume,   spawn,      {.v = (const char*[]){ "mpc", "volume", "+5", NULL } } },
    { ShiftMask,        XF86XK_AudioLowerVolume,   spawn,      {.v = (const char*[]){ "mpc", "volume", "-5", NULL } } },
    { ShiftMask,        XF86XK_AudioMute,          spawn,      {.v = (const char*[]){ "mpc", "volume", "0", NULL } } },
    /* BINDINGS FOR MPD - END   */
    /* BINDINGS FOR AUDIO - START */
    { 0,                XF86XK_AudioRaiseVolume,   spawn,      SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%") },
    { 0,                XF86XK_AudioLowerVolume,   spawn,      SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%") },
    { 0,                XF86XK_AudioMute,          spawn,      SHCMD("amixer -D pipewire set Master 1+ toggle") },
    /* BINDINGS FOR AUDIO - END   */
    /* BINDINGS FOR SCREEN - START   */
    { 0,            XF86XK_MonBrightnessUp,    spawn,          {.v = (const char*[]){ "xbacklight", "-inc", "15", NULL } } },
    { 0,            XF86XK_MonBrightnessDown,  spawn,          {.v = (const char*[]){ "xbacklight", "-dec", "15", NULL } } },
    /* BINDINGS FOR SCREEN - END */
    /* BINDINGS FOR STICKY - START   */
    { MODKEY,                       XK_s,      togglesticky,   {0} },
    /* BINDINGS FOR STICKY - END */
    /* BINDINGS FOR RECORDING - START   */
    { 0,                    XK_Print,          spawn,      SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
    { ShiftMask,            XK_Print,          spawn,      {.v = (const char*[]){ "maimpick", NULL } } },
    { MODKEY,               XK_Print,          spawn,      {.v = (const char*[]){ "dmenurecord", NULL } } },
    { MODKEY,               XK_Delete,         spawn,      {.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
    { MODKEY,               XK_Scroll_Lock,    spawn,      SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
    /* BINDINGS FOR RECORDING - END */
    /* ***** */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

