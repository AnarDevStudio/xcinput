#include "LinuxInput.h"
#include <cstdio>
#include <unistd.h>
#include <termios.h>
#include <ncurses.h>

InputManager::InputManager() {
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    printf("Terminal is active\n");
}

InputManager::~InputManager() {
    printf("\033[?1003l\n"); fflush(stdout); // disable mouse tracking
    endwin(); // close ncurses safely
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("Terminal reset.\n");
}

void InputManager::StartMouseInput() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    printf("\033[?1003h\n"); fflush(stdout); // enable mouse movement reports
    printf("Mouse input started.\n");
}

void InputManager::GetMousePosition(bool isDebug) {
    ch = getch();
    if (ch == KEY_MOUSE) {
        if (getmouse(&event) == OK) {
            mouse_x = event.x;
            mouse_y = event.y;

            // Update button states
            mouse_left  = event.bstate & BUTTON1_PRESSED;
            mouse_right = event.bstate & BUTTON3_PRESSED;

            if (isDebug) {
                mvprintw(0, 0, "Mouse: (%d, %d) L:%d R:%d     ",
                         mouse_x, mouse_y, mouse_left, mouse_right);
                refresh();
            }
        }
    }
    usleep(10000);
}

void InputManager::StopInput() {
    printf("\033[?1003l\n"); fflush(stdout);
    endwin();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("Input stopped\n");
}

void InputManager::StartInput() {
    active = true;
    printf("Input Started\n");

    while (active) {
        int ch = getchar();
        switch (ch) {
            case 27: // ESC
                printf("Escape pressed, stopping input.\n");
                StopInput();
                active = false;
                break;
            case 32:
                printf("Space pressed\n");
                break;
            case 10:
            case 13:
                printf("Enter pressed\n");
                break;
            case 8:
            case 127:
                printf("Backspace pressed\n");
                break;
            default:
                if (ch != EOF)
                    printf("You pressed: %c (%d)\n", ch, ch);
                break;
        }
    }
}

char InputManager::isCharacterPushed() {
    pushed_character = getchar();
    return pushed_character;
}

void InputManager::IsMouseButtonPressed(bool &left, bool &right) {
    left  = mouse_left;
    right = mouse_right;
}
