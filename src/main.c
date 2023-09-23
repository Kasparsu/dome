#include <windows.h>


int main()
{
    HANDLE std_out = GetStdHandle(STD_OUTPUT_HANDLE);
    if (std_out == INVALID_HANDLE_VALUE) {
        return 66;
    }
    //AttachConsole(ATTACH_PARENT_PROCESS);
    if (!WriteConsole(std_out, "Hello World!", 12, NULL, NULL)) {
        return 67;
    }

   return 0;
}