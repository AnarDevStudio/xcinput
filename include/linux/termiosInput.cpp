#include "termiosInput.h"
#include <cstdio>
#include <unistd.h>
#include <SDL2/SDL.h>

// constructor
InputManager::InputManager() {
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    printf("Terminal is active\n");
}

// rest destructor
InputManager::~InputManager() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("Terminal reset.\n");
}

// stop input reading
void InputManager::StopInput() {
    active = false;       // loop'u durdur
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("Input stopped\n");
}

// just check if a character is pushed
char InputManager::isCharacterPushed() {
    pushed_character = getchar();   
    return pushed_character;  
}

// reed input continuously
void InputManager::StartInput() {
    active = true;
    printf("Input Started\n");

    while (active) {
        pushed_character = getchar();

        switch (pushed_character) {
            case 27:  // Escape tuşu ile dur
                printf("Escape pressed, stopping input.\n");
                StopInput();
                break;
            case 32:
                printf("Space pressed\n"); 
                break;
            case 10: case 13:
                printf("Enter pressed\n"); 
                break;
            case 8: case 127:
                printf("Backspace pressed\n"); 
                break;
            default:
                printf("You pressed: %c (%d)\n", pushed_character, pushed_character);
                break;
        }
    }
}
