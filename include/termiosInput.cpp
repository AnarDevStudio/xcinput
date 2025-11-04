#include "termiosInput.h"
#include <cstdio>
#include <unistd.h>

// Constructor: terminali aktif hale getirir
TermiosManager::TermiosManager() {
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    printf("Terminal is active\n");
}

// Destructor: terminal ayarlarını geri alır
TermiosManager::~TermiosManager() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("Terminal reset.\n");
}

// Input okumayı durdurur
void TermiosManager::StopInput() {
    active = false;       // loop'u durdur
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("Input stopped\n");
}

// Tek karakter oku
char TermiosManager::isCharacterPushed() {
    pushed_character = getchar();   
    return pushed_character;  
}

// Sürekli input oku (loop)
void TermiosManager::StartInput() {
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
