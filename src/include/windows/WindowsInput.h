#ifndef WINDOWS_INPUT_H
#define WINDOWS_INPUT_H
#include <unistd.h>   
#include <cstdio>
#include <windows.h>

class InputManager{
    InputManager();
    ~InputManager();
    char isCharacterPushed();
    void StopInput();
    void StartInput();
    void StartMouseInput();
    void GetMousePosition(bool isDebug);
    void IsMouseButtonPressed(bool &left, bool &right);
};


#endif
