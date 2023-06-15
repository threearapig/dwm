/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:style=medium:size=16", "monospace:size=16"};
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
    [SchemeNorm] = { "#bbbbbb", "#333333", "#444444" },
    [SchemeSel] = { "#ffffff", "#37474F", "#42A5F5" },
    [SchemeHid] = { "#dddddd", NULL, NULL },
};
static const unsigned int alphas[][3]      = {
    /*               fg      bg        border*/
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { 
    "",
    "",
    "󰵮",
    "",
    "",
    "󰊠",
    "󰝚",
    "",
    "󰘅",
};

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title               tags mask     isfloating   monitor */
	{ NULL,       NULL,       "图片查看器",       0,            1,           -1 },
	{ NULL,       NULL,       "图片查看",         0,            1,           -1 },
	{ NULL,       NULL,       "阴阳师",           0,            1,           -1 },
	{ NULL,       NULL,       "QQ",               0,            1,           -1 },
	{ NULL,       NULL,       "微信",             0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "󰬛",      tile },    /* first entry is default */
	{ "󰬔",      monocle },
	{ "󰬎",      grid },
//	{ "[@]",      spiral },
//	{ "[\\]",     dwindle },
//	{ "H[]",      deck },
//	{ "TTT",      bstack },
//	{ "===",      bstackhoriz },
//	{ "###",      nrowgrid },
//	{ "---",      horizgrid },
//	{ ":::",      gaplessgrid },
//	{ "|M|",      centeredmaster },
//	{ ">M>",      centeredfloatingmaster },
//	{ "><>",      NULL },    /* no layout function means floating behavior */
//	{ NULL,       NULL },
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
//static char dmenumon[2]             = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[]       = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[]       = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]        = { "st", NULL };
static const char scratchpadname[]  = "scratchpad";
static const char *scratchpadcmd[]  = { "st", "-t", scratchpadname, "-g", "80x24", NULL };
static const char *browsercmd[]     = { "google-chrome-stable", NULL };
static const char *wpcmd[]          = { "/home/thejc/scripts/wp-change.sh", NULL };
static const char *upvol[]          = { "/home/thejc/scripts/vol-up.sh",  NULL };
static const char *downvol[]        = { "/home/thejc/scripts/vol-down.sh",  NULL };
static const char *mutevol[]        = { "/home/thejc/scripts/vol-toggle.sh",  NULL };
static const char *uplight[]        = { "/home/thejc/scripts/light-up.sh",  NULL };
static const char *downlight[]      = { "/home/thejc/scripts/light-down.sh",  NULL };
static const char *setcolemakcmd[]  = { "/home/thejc/scripts/setxmodmap-colemak.sh", NULL };
static const char *setqwertycmd[]   = { "/home/thejc/scripts/setxmodmap-qwerty.sh", NULL };
static const char *suspendcmd[]     = { "/home/thejc/scripts/suspend.sh", NULL };
static const char *screenshotcmd[]  = { "flameshot", "gui", NULL };

static const Key keys[] = {
	/* modifier                     key                 function        argument */
	{ MODKEY,                       XK_s,               spawn,          {.v = roficmd } },
	{ MODKEY,                       XK_Return,          spawn,          {.v = termcmd } },
   	{ MODKEY,                       XK_c,               spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_apostrophe,      togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_F2,              spawn,          {.v = downvol } },
	{ MODKEY,                       XK_F3,              spawn,          {.v = upvol   } },
	{ MODKEY,                       XK_F1,              spawn,          {.v = mutevol } },
	{ MODKEY,                       XK_F5,              spawn,          {.v = downlight } },
	{ MODKEY,                       XK_F6,              spawn,          {.v = uplight } },
  	{ MODKEY,                       XK_b,               spawn,          {.v = wpcmd } },
	{ MODKEY|ShiftMask,             XK_r,               spawn,          {.v = screenshotcmd } },
	{ MODKEY|ShiftMask,             XK_p,               spawn,          {.v = suspendcmd } },
	{ MODKEY|ShiftMask,             XK_w,               spawn,          {.v = setqwertycmd } },
	{ MODKEY|ShiftMask,             XK_m,               spawn,          {.v = setcolemakcmd } },
	{ MODKEY,                       XK_u,               focusstackvis,  {.i = -1 } },
	{ MODKEY,                       XK_e,               focusstackvis,  {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_u,               rotatestack,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_e,               rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Return,          zoom,           {0} },
	{ MODKEY,                       XK_n,               viewtoleft,     {0} },
	{ MODKEY,                       XK_i,               viewtoright,    {0} },
	{ MODKEY|ShiftMask,             XK_n,               tagtoleft,      {0} },
	{ MODKEY|ShiftMask,             XK_i,               tagtoright,     {0} },
	{ MODKEY,                       XK_h,               setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_o,               setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_b,               togglebar,      {0} },
	{ MODKEY,                       XK_q,               killclient,     {0} },
	{ MODKEY,                       XK_f,               fullscreen,     {0} },
	{ MODKEY,                       XK_Tab,             view,           {0} },
	{ MODKEY,                       XK_t,               setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,               setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_g,               setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_h,               incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,               incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,               showall,        {0} },
	{ MODKEY,                       XK_k,               hide,           {0} },
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
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
//	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
//	{ ClkLtSymbol,          0,              Button3,        setlayout,      {0} },
//	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
//	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
//	{ ClkStatusText,        0,              Button2,        spawn,          {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

