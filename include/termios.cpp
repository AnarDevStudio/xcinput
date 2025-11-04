#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <printf.h>
using namespace std;

class TermiosManager {
public:
    termios oldt, newt;
    char pushed_character;

    TermiosManager() {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        printf("Terminal is active\n");
    };

    void StartInput(){
        while (true)
        {
            pushed_character = getchar();
            printf("You pressed: %c\n", pushed_character);
        }   
    }
};

int main(){
    TermiosManager termiosManager;
    termiosManager.StartInput();
    return 0;
}