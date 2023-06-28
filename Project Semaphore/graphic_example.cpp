//----------------------------------------------------------------------------------------------------
// An example of graphical program using WinBGIm graphic library
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
// Notes on working with VSCode (in Computer Lab)
//   You don't want to open any .cpp file directly in VSCode.
//   Instead, you want to open a folder first. Then open your .cpp file.
//   VSCode works mostly based on (what so called "workspace").
//   Which in this case, you need to work inside a folder.
//
//   So, for this program (graphic_example.cpp), in order to run it,
//     1). open the folder named "c:\vscode_cpp_workspace" into VSCode
//     2). open this program file (i.e. graphic_example.cpp) into VSCode
//     3). In debug mode choose "WinBGI program"
//     4). Start debugging or running by pressing F5
//
// If you want to use your own folder, copy the folder ".vscode" from "vscode_cpp_workspace"
// and put it inside your own folder.
//----------------------------------------------------------------------------------------------------

#include <graphics.h>
#include <cstdlib>
#include <ctime>

int main()
{

    int screenWidth = getmaxwidth();
    int screenHeight = getmaxheight();
    int x, y, radius, color;

    initwindow(screenWidth, screenHeight, "An example of graphical program using WinBGIm library");

    srand(time(NULL));
    while (!kbhit())
    {
        x = rand() % screenWidth;
        y = rand() % screenHeight;
        radius = rand() % ((screenHeight / 4) + 50);
        color = COLOR(rand() % 255, rand() % 255, rand() % 255);

        setcolor(color);
        setfillstyle(SOLID_FILL, color);
        fillellipse(x, y, radius, radius);

        delay(10);
    }

    getch();

    return 0;
}
