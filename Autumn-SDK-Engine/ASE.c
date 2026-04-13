#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "AutumnAPI.h"

static int l_create_rect(lua_State *L) {
    int w = luaL_checkinteger(L, 1);
    int h = luaL_checkinteger(L, 2);
    uint32_t color = luaL_checkinteger(L, 3);
    int radius = luaL_checkinteger(L, 4);
    lv_obj_t * rect = lv_obj_create(lv_scr_act());
    lv_obj_set_size(rect, w, h);
    lv_obj_set_style_bg_color(rect, lv_color_hex(color), 0);
    lv_obj_set_style_radius(rect, radius, 0);
    lv_obj_center(rect);
    lua_pushlightuserdata(L, rect);
    return 1;
}

static int l_set_gradient(lua_State *L) {
    lv_obj_t * obj = (lv_obj_t *)lua_touserdata(L, 1);
    uint32_t color1 = luaL_checkinteger(L, 2);
    uint32_t color2 = luaL_checkinteger(L, 3);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(color2),0);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, 0);
    lv_obj_set_style_bg_main_stop(obj, 0, 0);
    lv_obj_set_style_bg_grad_stop(obj, 255, 0);
    return 0;
}

static int l_set_border(lua_State *L) {
    lv_obj_t * obj = (lv_obj_t *)lua_touserdata(L, 1);
    int width = luaL_checkinteger(L, 2);
    uint32_t color = luaL_checkinteger(L, 3);
    lv_obj_set_style_border_width(obj, width, 0);
    lv_obj_set_style_border_color(obj, lv_color_hex(color), 0);
    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, 0);
    return 0;
}

static int l_set_font(lua_State *L) {
    lv_obj_t * obj = (lv_obj_t *)lua_touserdata(L, 1);
    const char * font_path = luaL_checkstring(L, 2);
    int size = luaL_checkinteger(L, 3);
    // lv_obj_set_style_text_font(obj, custom_font, 0);
    return 0;
}

static int l_set_image(lua_State *L) {
    lv_obj_t * obj = (lv_obj_t *)lua_touserdata(L, 1);
    const char * path = luaL_checkstring(L, 2);
    lv_img_set_src(obj, path); 
    return 0;
}

static int l_create_panel(lua_State *L) {
    lv_obj_t * parent = (lv_obj_t *)lua_touserdata(L, 1);
    lv_obj_t * panel = lv_obj_create(parent ? parent : lv_scr_act());
    
    // Varsayılan AutumnOS Panel Stili (Temiz Çerçeve)
    lv_obj_set_style_border_width(panel, 1, 0);
    lv_obj_set_style_border_side(panel, LV_BORDER_SIDE_FULL, 0);
    lv_obj_set_style_border_color(panel, lv_color_hex(0x444444), 0);
    lv_obj_set_style_radius(panel, 0, 0);
    
    lua_pushlightuserdata(L, panel);
    return 1;
}

static int l_create_button(lua_State *L) {
    lv_obj_t * parent = (lv_obj_t *)lua_touserdata(L, 1);
    lv_obj_t * btn = lv_btn_create(parent ? parent : lv_scr_act());
    lv_obj_set_style_border_width(btn, 1, 0);
    lv_obj_set_style_border_color(btn, lv_color_hex(0x000000), 0);
    lv_obj_set_style_radius(btn, 0, 0); 
    lua_pushlightuserdata(L, btn);
    return 1;
}

static const struct luaL_Reg autumn_eng[] = {
    {"CreatePanel", l_create_panel},
    {"CreateButton", l_create_button},
    {"SetImage", l_set_image},
    {"SetFont", l_set_font},
    {"SetBorder", l_set_border},
    {NULL, NULL}
};

int luaopen_autumn(lua_State *L) {
    luaL_newlib(L, autumn_eng);
    return 1;
}

int main(int argc, char *argv[]) {
    lv_init();
    // lv_png_init();
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaL_requiref(L, "Autumn", luaopen_autumn, 1);
    lua_pop(L, 1);
    if (luaL_dofile(L, "/apps/main.lua")) {
        fprintf(stderr, "AutumnOS Engine Error: %s\n", lua_tostring(L, -1));
    }
    while(1) {
        lv_timer_handler();
        usleep(5000);
    }

    lua_close(L);
    return 0;
}
