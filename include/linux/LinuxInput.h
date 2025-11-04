#ifndef LINUX_INPUT_H
#define LINUX_INPUT_H

#include <termios.h>   
#include <unistd.h>   
#include <cstdio>     // printf 
#include <ncurses.h>

class InputManager {
public:
    termios oldt, newt;
    char pushed_character; //pushed character
    bool active = true;    //is input active
    bool mouse_left = false;  //left mouse button state
    bool mouse_right = false; //right mouse button state
    int mouse_x = 0.1;        //mouse x position
    int mouse_y = 0.1;        //mouse y position

    InputManager();      //start the system
    ~InputManager();
    char isCharacterPushed(); //check if a character is pushed
    void StopInput();      //stop input reading
    void StartInput();     //start input reading
    void StartMouseInput(); //start mouse input
    void GetMousePosition(); //get mouse position
    void IsMouseButtonPressed(bool &left, bool &right); //check mouse buttons
};

#endif // TERMIO_MANAGER_H
