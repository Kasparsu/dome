#define _DEFAULT_SOURCE
#define NOMINMAX


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#ifndef DOME_VERSION
#define DOME_VERSION "0.0.0 - CUSTOM"
#endif

// Standard libs
#ifdef __MINGW32__
#include <windows.h>
#endif
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <libgen.h>
#include <time.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <wren.h>
#include <SDL.h>
#include <vendor.h>

// Import plugin-specific definitions
#define WIN_EXPORT
#include "dome.h"
// project-specific definitions
#define external DOME_EXPORT
#define internal DOME_INTERNAL static
#define global_variable static
#define local_persist static


#define INIT_TO_ZERO(Type, name)\
  Type name;\
  memset(&name, 0, sizeof(Type));

#define STRINGS_EQUAL(a, b) (strcmp(a, b) == 0)

#define VM_ABORT(vm, error) do {\
  wrenSetSlotString(vm, 0, error);\
  wrenAbortFiber(vm, 0); \
} while(false);

#define ASSERT_SLOT_TYPE(vm, slot, type, fieldName) \
  if (wrenGetSlotType(vm, slot) != WREN_TYPE_##type) { \
    VM_ABORT(vm, #fieldName " was not " #type); \
    return; \
  }



// Constants
// Screen dimension constants
#define GAME_WIDTH 320
#define GAME_HEIGHT 240
#define SCREEN_WIDTH GAME_WIDTH * 2
#define SCREEN_HEIGHT GAME_HEIGHT * 2

// Used in the io variable, but we need to catch it here
global_variable WrenHandle* bufferClass = NULL;
global_variable WrenHandle* keyboardClass = NULL;
global_variable WrenHandle* mouseClass = NULL;
global_variable WrenHandle* gamepadClass = NULL;
global_variable WrenHandle* updateInputMethod = NULL;

// These are set by cmd arguments
#ifdef DEBUG
global_variable bool DEBUG_MODE = true;
#else
global_variable bool DEBUG_MODE = false;
#endif
global_variable size_t AUDIO_BUFFER_SIZE = 2048;



// Game code
#include "math.c"
#include "strings.c"

#include "modules/map.c"

#include "plugin.h"
#include "engine.h"
#include "font/font8x8.h"
#include "io.c"

#include "audio/engine.h"
#include "audio/hashmap.c"
#include "audio/engine.c"
#include "audio/channel.c"

#include "debug.c"

#include "engine.c"

#include "api/io.c"
#include "api/audio.c"
#include "api/bitmap.c"
#include "api/canvas.c"
#include "api/core.c"
#include "plugin.c"


#ifndef __EMSCRIPTEN__
#include "tools/help.c"
#include "tools/fuse.c"
#include "tools/embed.c"
#include "tools/nest.c"
#endif

#include "modules/dome.c"
#include "modules/font.c"
#include "modules/io.c"
#include "modules/audio.c"
#include "modules/graphics.c"
#include "modules/image.c"
#include "modules/input.c"
#include "modules/json.c"
#include "modules/platform.c"
#include "modules/random.c"
#include "modules/plugin.c"
#include "modules/math.c"

// Comes last to register modules
#include "vm.c"
#include "game.c"


int main(int argc, char* argv[])
{

  printf("Hello");
          
}

