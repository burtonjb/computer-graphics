// lua imports
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

#include <stdlib.h>

#include "../src/file_util.h"
#include "../src/image.h"

/*
 * Note: This file is now deprecated. Swig will build bindings to multiple
 * languages and I don't really want to maintain this.
 */

/*
 * Args are width, height, RGBA as this is temporary
 */
static int lua_make_image(lua_State *L) {
  // check and fetch the arguments
  uint16_t width = luaL_checknumber(L, 1);
  uint16_t height = luaL_checknumber(L, 2);
  uint8_t r = luaL_checknumber(L, 3);
  uint8_t g = luaL_checknumber(L, 4);
  uint8_t b = luaL_checknumber(L, 5);
  uint8_t a = luaL_checknumber(L, 6);

  Pixel p = {r, g, b, a};

  Image *image = make_filled_image(width, height, &p);

  // push the results
  lua_pushlightuserdata(L, image);

  // return number of results
  return 1;
}

/*
 * Arguments are RGBA values. Output is the pixel.
 */
static int lua_make_pixel(lua_State *L) {
  uint8_t r = luaL_checknumber(L, 1);
  uint8_t g = luaL_checknumber(L, 2);
  uint8_t b = luaL_checknumber(L, 3);
  uint8_t a = luaL_checknumber(L, 4);

  Pixel *pixel = malloc(sizeof(Pixel));
  pixel->red = r;
  pixel->green = g;
  pixel->blue = b;
  pixel->alpha = a;

  lua_pushlightuserdata(L, pixel);

  return 1;
}

/*
 * Args are Image, x, y, Pixel
 *
 * Returns nothing
 */
static int lua_write_pixel_to_image(lua_State *L) {
  Image *image = lua_touserdata(L, 1);
  uint16_t x = luaL_checknumber(L, 2);
  uint16_t y = luaL_checknumber(L, 3);
  Pixel *pixel = lua_touserdata(L, 4);

  write_pixel_to_image(image, x, y, pixel);

  return 0;
}

/*
 * Args are path, image pointer
 */
static int lua_write_file(lua_State *L) {
  const char *path = luaL_checkstring(L, 1);
  const Image *image =
      lua_touserdata(L, 2); // fixme: should eventually use checkudata

  write_pam(path, image);

  return 0;
}

// library to be registered
static const struct luaL_Reg image_lib[] = {
    {"make_image", lua_make_image},
    {"make_pixel", lua_make_pixel},
    {"write_pixel_to_image", lua_write_pixel_to_image},
    {"write_file", lua_write_file},
    {NULL, NULL} /* sentinel */
};

// name of this function is not flexible
int luaopen_image_lib(lua_State *L) {
  luaL_newlib(L, image_lib);
  return 1;
}
