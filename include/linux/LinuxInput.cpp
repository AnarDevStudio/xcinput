#include "LinuxInput.h"
#include <cstdio>
#include <unistd.h>
#include <ncurses.h>

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

void InputManager::StartMouseInput() {
    initscr();              // Start curses mode
    cbreak();               // Line buffering disabled
    noecho();               // Don't echo() while we do getch
    keypad(stdscr, TRUE);   // We get F1, F2 etc..
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    printf("Mouse input started\n");
    refresh();
}
// get mouse position
void InputManager::GetMousePosition() {
    printf("\033[?1003h\n"); fflush(stdout); // hareket raporlamayı aç

    MEVENT event;
    int ch;

    while (true) {
        ch = getch(); // non-block mod olmasa bile sürekli olay bekler

        if (ch == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                mouse_x = event.x;
                mouse_y = event.y;

                // Terminalde her seferinde aynı satırı güncelle
                mvprintw(0, 0, "Mouse Position: (%d, %d)      ", mouse_x, mouse_y);
                refresh();
            }
        }

        usleep(10000); // 10 ms bekle
    }

    // Program sonlanınca terminali eski haline döndür
    printf("\033[?1003l\n");
    endwin();
}

// check mouse buttons
void InputManager::IsMouseButtonPressed(bool &left, bool &right) {
    left  = mouse_left;
    right = mouse_right;
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
