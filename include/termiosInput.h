#ifndef TERMIO_MANAGER_H
#define TERMIO_MANAGER_H

#include <termios.h>   
#include <unistd.h>   
#include <cstdio>     // printf 

class TermiosManager {
public:
    termios oldt, newt;
    char pushed_character; //pushed character
    bool active = true;    //is input active

    TermiosManager();      //start the system
    ~TermiosManager();
    char isCharacterPushed(); //check if a character is pushed
    void StopInput();      //stop input reading
    void StartInput();     //start input reading
};

#endif // TERMIO_MANAGER_H
