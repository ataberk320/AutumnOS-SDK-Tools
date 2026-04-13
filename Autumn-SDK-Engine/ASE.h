#ifndef SDK_ENG_H
#define SDK_ENG_H

static int l_create_rect(lua_State *L);

static int l_set_gradient(lua_State *L);

static int l_set_border(lua_State *L);

static int l_set_font(lua_State *L);

static int l_set_image(lua_State *L);

static int l_create_panel(lua_State *L);
    
static int l_create_button(lua_State *L);

int luaopen_autumn(lua_State *L);

int main(int argc, char *argv[]);

#endif
