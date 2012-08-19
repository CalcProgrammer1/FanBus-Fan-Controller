lib_LTLIBRARIES = libSDL_draw.la

INCLUDES = `sdl-config --cflags` -I../include 

libSDL_draw_la_LDFLAGS =   \
  -release $(LT_RELEASE)  \
  -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)                             

libSDL_draw_la_SOURCES = SDL_draw.c
EXTRA_DIST = SDL_draw.c
