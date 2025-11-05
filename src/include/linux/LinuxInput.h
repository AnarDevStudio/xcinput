#ifndef LINUX_INPUT_H
#define LINUX_INPUT_H

#include <termios.h>   
#include <unistd.h>   
#include <cstdio>
#include <ncurses.h>

class InputManager {
public:
    termios oldt, newt;
    char pushed_character;        // pressed character
    bool active = true;           // input active
    bool mouse_left = false;      // left button state
    bool mouse_right = false;     // right button state
    int mouse_x = 0;              // mouse X
    int mouse_y = 0;              // mouse Y
    MEVENT event;                 // ncurses mouse event
    int ch = 0;                   // last input character

    InputManager();
    ~InputManager();
    char isCharacterPushed();
    void StopInput();
    void StartInput();
    void StartMouseInput();
    void GetMousePosition(bool isDebug);
    void IsMouseButtonPressed(bool &left, bool &right);
};

#endif // LINUX_INPUT_H
