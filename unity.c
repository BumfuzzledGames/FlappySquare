// $ cc unity.c $(sdl2-config --cflags --libs)
#include "src/draw.c"
#include "src/event.c"
#include "src/font.c"
#include "src/main.c"
#include "src/screen.c"
#include "src/screens/game.c"
#include "src/screens/game_over.c"
#include "src/screens/start.c"
#include "src/util.c"
#include "src/window.c"

#ifdef _WIN32
// $ cc -nostartfiles unity.c $(sdl2-config --cflags --libs)
#if __i686__
__attribute((force_align_arg_pointer))
#endif
void WinMainCRTStartup(void)
{
    __declspec(dllimport) void __stdcall ExitProcess(int);
    ExitProcess(SDL_main(0, 0));
}
#endif
