#define MOD XCB_MOD_MASK_1
static const uint16_t movements[] = {20, 20, 20, 20};
static const bool resize_by_line = true;
static const float resize_keep_aspect_ratio = 1;
/* OffsetX OffsetY MaxWidth MaxHeight */
static const uint8_t offsets[] = {0, 25, 0, 25};
static const bool inverted_colors = true;
static const char *colors[] = {
    "#080808", /* FocusCol */
    "#333333", /* UnfocusCol */
    "#7a8c5c", /* FixedCol */
    "#ff6666", /* UnkilCol */
    "#cc9933", /* FixedUnKilCol */
    "#0d131a", /* OuterBorderCol */
    "#000000" /* EmptyCol */
};
/* Default position of the cursor (relative to the current window):
 * TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, MIDDLE
 */
#define CURSOR_POSITION MIDDLE
/* OuterBorder FullBorderWidth MagnetBorder ResizeBorder */
static const uint8_t borders[] = {2, 2, 2, 2};
/* Windows that won't have a border.
 * It uses substring comparison with what is found in the WM_NAME attribute of
 * the window. You can test this using `xprop WM_NAME`
 */
#define LOOK_INTO "WM_NAME"
static const char *ignore_names[] = {"bar", "xclock"};
static const char *menucmd[] = {"dmenu_run", "-b", NULL};
static const char *termcmd[] = {"urxvt", NULL};
static const char *iconcmd[] = {"set-icons", NULL};
static void
halfandcentered(const Arg *arg)
{
    Arg arg2 = {.i = TWOBWM_MAXHALF_VERTICAL_LEFT};
    maxhalf(&arg2);
    Arg arg3 = {.i = TWOBWM_TELEPORT_CENTER};
    teleport(&arg3);
}
/*
 * Command to execute when switching from sloppy focus to click to focus
 * The strings "Sloppy" and "Click" will be passed as the last argument
 * If NULL this is ignored
 */
static const char *sloppy_switch_cmd[] = {};
static void
toggle_sloppy(const Arg *arg)
{
    is_sloppy = !is_sloppy;
    if (arg->com != NULL && LENGTH(arg->com) > 0)
    {
        start(arg);
    }
}
/* Check /usr/include/X11/keysymdef.h for the list of all keys.
 * 0x000000 is for no modkey.
 * If you are having trouble finding the right keycode use the `xev` to get it.
 */
static key keys[] = {
    /* Modifier | Key | Function | Argument */
    {MOD, XK_Tab, focusnext, {.i = TWOBWM_FOCUS_NEXT}},
    {MOD | SHIFT, XK_Tab, focusnext, {.i = TWOBWM_FOCUS_PREVIOUS}},
    {MOD, XK_q, deletewin, {}},
    {MOD | SHIFT, XK_k, resizestep, {.i = TWOBWM_RESIZE_UP}},
    {MOD | SHIFT, XK_j, resizestep, {.i = TWOBWM_RESIZE_DOWN}},
    {MOD | SHIFT, XK_l, resizestep, {.i = TWOBWM_RESIZE_RIGHT}},
    {MOD | SHIFT, XK_h, resizestep, {.i = TWOBWM_RESIZE_LEFT}},
    {MOD | SHIFT | CONTROL, XK_k, resizestep, {.i = TWOBWM_RESIZE_UP_SLOW}},
    {MOD | SHIFT | CONTROL, XK_j, resizestep, {.i = TWOBWM_RESIZE_DOWN_SLOW}},
    {MOD | SHIFT | CONTROL, XK_l, resizestep, {.i = TWOBWM_RESIZE_RIGHT_SLOW}},
    {MOD | SHIFT | CONTROL, XK_h, resizestep, {.i = TWOBWM_RESIZE_LEFT_SLOW}},
    {MOD, XK_k, movestep, {.i = TWOBWM_MOVE_UP}},
    {MOD, XK_j, movestep, {.i = TWOBWM_MOVE_DOWN}},
    {MOD, XK_l, movestep, {.i = TWOBWM_MOVE_RIGHT}},
    {MOD, XK_h, movestep, {.i = TWOBWM_MOVE_LEFT}},
    {MOD | CONTROL, XK_k, movestep, {.i = TWOBWM_MOVE_UP_SLOW}},
    {MOD | CONTROL, XK_j, movestep, {.i = TWOBWM_MOVE_DOWN_SLOW}},
    {MOD | CONTROL, XK_l, movestep, {.i = TWOBWM_MOVE_RIGHT_SLOW}},
    {MOD | CONTROL, XK_h, movestep, {.i = TWOBWM_MOVE_LEFT_SLOW}},
    {MOD, XK_g, teleport, {.i = TWOBWM_TELEPORT_CENTER}},
    {MOD | SHIFT, XK_g, teleport, {.i = TWOBWM_TELEPORT_CENTER_Y}},
    {MOD | CONTROL, XK_g, teleport, {.i = TWOBWM_TELEPORT_CENTER_X}},
    {MOD, XK_y, teleport, {.i = TWOBWM_TELEPORT_TOP_LEFT}},
    {MOD, XK_u, teleport, {.i = TWOBWM_TELEPORT_TOP_RIGHT}},
    {MOD, XK_b, teleport, {.i = TWOBWM_TELEPORT_BOTTOM_LEFT}},
    {MOD, XK_n, teleport, {.i = TWOBWM_TELEPORT_BOTTOM_RIGHT}},
    {MOD, XK_Home, resizestep_aspect, {.i = TWOBWM_RESIZE_KEEP_ASPECT_GROW}},
    {MOD, XK_End, resizestep_aspect, {.i = TWOBWM_RESIZE_KEEP_ASPECT_SHRINK}},
    {MOD, XK_w, maximize, {}},
    {MOD | SHIFT, XK_w, fullscreen, {}},
    {MOD, XK_m, maxvert_hor, {.i = TWOBWM_MAXIMIZE_VERTICALLY}},
    {MOD | SHIFT, XK_m, maxvert_hor, {.i = TWOBWM_MAXIMIZE_HORIZONTALLY}},
    {MOD | SHIFT, XK_y, maxhalf, {.i = TWOBWM_MAXHALF_VERTICAL_LEFT}},
    {MOD | SHIFT, XK_u, maxhalf, {.i = TWOBWM_MAXHALF_VERTICAL_RIGHT}},
    {MOD | SHIFT, XK_b, maxhalf, {.i = TWOBWM_MAXHALF_HORIZONTAL_BOTTOM}},
    {MOD | SHIFT, XK_n, maxhalf, {.i = TWOBWM_MAXHALF_HORIZONTAL_TOP}},
    {MOD | SHIFT | CONTROL,
     XK_y,
     maxhalf,
     {.i = TWOBWM_MAXHALF_FOLD_VERTICAL}},
    {MOD | SHIFT | CONTROL,
     XK_b,
     maxhalf,
     {.i = TWOBWM_MAXHALF_FOLD_HORIZONTAL}},
    {MOD | SHIFT | CONTROL,
     XK_u,
     maxhalf,
     {.i = TWOBWM_MAXHALF_UNFOLD_VERTICAL}},
    {MOD | SHIFT | CONTROL,
     XK_n,
     maxhalf,
     {.i = TWOBWM_MAXHALF_UNFOLD_HORIZONTAL}},
    {MOD, XK_comma, changescreen, {.i = TWOBWM_NEXT_SCREEN}},
    {MOD, XK_period, changescreen, {.i = TWOBWM_PREVIOUS_SCREEN}},
    {MOD, XK_r, raiseorlower, {}},
    {MOD, XK_v, nextworkspace, {}},
    {MOD, XK_c, prevworkspace, {}},
    {MOD | SHIFT, XK_v, sendtonextworkspace, {}},
    {MOD | SHIFT, XK_c, sendtoprevworkspace, {}},
    {MOD, XK_i, hide, {}},
    {MOD, XK_a, unkillable, {}},
    {MOD, XK_t, always_on_top, {}},
    {MOD, XK_f, fix, {}},
    {MOD, XK_Up, cursor_move, {.i = TWOBWM_CURSOR_UP_SLOW}},
    {MOD, XK_Down, cursor_move, {.i = TWOBWM_CURSOR_DOWN_SLOW}},
    {MOD, XK_Right, cursor_move, {.i = TWOBWM_CURSOR_RIGHT_SLOW}},
    {MOD, XK_Left, cursor_move, {.i = TWOBWM_CURSOR_LEFT_SLOW}},
    {MOD | SHIFT, XK_Up, cursor_move, {.i = TWOBWM_CURSOR_UP}},
    {MOD | SHIFT, XK_Down, cursor_move, {.i = TWOBWM_CURSOR_DOWN}},
    {MOD | SHIFT, XK_Right, cursor_move, {.i = TWOBWM_CURSOR_RIGHT}},
    {MOD | SHIFT, XK_Left, cursor_move, {.i = TWOBWM_CURSOR_LEFT}},
    {MOD, XK_d, start, {.com = termcmd}},
    {MOD, XK_o, start, {.com = iconcmd}},
    {MOD, XK_x, start, {.com = menucmd}},
    {MOD | CONTROL, XK_q, twobwm_exit, {.i = 0}},
    {MOD | CONTROL, XK_r, twobwm_restart, {.i = 0}},
    {MOD, XK_space, halfandcentered, {.i = 0}},
    {MOD, XK_s, toggle_sloppy, {.com = sloppy_switch_cmd}},
    {MOD, XK_1, changeworkspace, {.i = 1}},
    {MOD | SHIFT, XK_1, sendtoworkspace, {.i = 1}},
    {MOD, XK_2, changeworkspace, {.i = 2}},
    {MOD | SHIFT, XK_2, sendtoworkspace, {.i = 2}},
    {MOD, XK_3, changeworkspace, {.i = 3}},
    {MOD | SHIFT, XK_3, sendtoworkspace, {.i = 3}},
    {MOD, XK_4, changeworkspace, {.i = 4}},
    {MOD | SHIFT, XK_4, sendtoworkspace, {.i = 4}},
    {MOD, XK_5, changeworkspace, {.i = 5}},
    {MOD | SHIFT, XK_5, sendtoworkspace, {.i = 5}},
    {MOD, XK_6, changeworkspace, {.i = 6}},
    {MOD | SHIFT, XK_6, sendtoworkspace, {.i = 6}},
    {MOD, XK_7, changeworkspace, {.i = 7}},
    {MOD | SHIFT, XK_7, sendtoworkspace, {.i = 7}},
    {MOD, XK_8, changeworkspace, {.i = 8}},
    {MOD | SHIFT, XK_8, sendtoworkspace, {.i = 8}},
    {MOD, XK_9, changeworkspace, {.i = 9}},
    {MOD | SHIFT, XK_9, sendtoworkspace, {.i = 9}}};
/* The last argument makes it a root window only event. */
static Button buttons[] = {
    {MOD, XCB_BUTTON_INDEX_1, mousemotion, {.i = TWOBWM_MOVE}, false},
    {MOD, XCB_BUTTON_INDEX_3, mousemotion, {.i = TWOBWM_RESIZE}, false},
    {0, XCB_BUTTON_INDEX_3, start, {.com = menucmd}, true},
    {MOD | SHIFT, XCB_BUTTON_INDEX_1, changeworkspace, {.i = 0}, false},
    {MOD | SHIFT, XCB_BUTTON_INDEX_3, changeworkspace, {.i = 1}, false},
    {MOD | ALT, XCB_BUTTON_INDEX_1, changescreen, {.i = 1}, false},
    {MOD | ALT, XCB_BUTTON_INDEX_3, changescreen, {.i = 0}, false}};
