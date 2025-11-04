#include "termiosInput.h"

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
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("Input stopped\n");
    active = false;
}

// Input okumayı başlatır
void TermiosManager::StartInput() {
    active = true;
    while (active) {
        pushed_character = getchar();

        switch (pushed_character) {
            case 27: printf("You pressed: Escape\n"); break;
            case 32: printf("You pressed: Space\n"); break;
            case 10:
            case 13: printf("You pressed: Enter\n"); break;
            case 8:
            case 127: printf("You pressed: Backspace\n"); break;
            default: printf("You pressed: %c (%d)\n", pushed_character, pushed_character); break;
        }
    }
}

