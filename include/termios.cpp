#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <printf.h>
using namespace std;

class TermiosManager {
public:
    termios oldt, newt;
    char pushed_character;
    bool active = true;

    TermiosManager() {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        printf("Terminal is active\n");
    };

    ~TermiosManager() {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        printf("Terminal reset.\n");
    }
 
    void StopInput(){
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        printf("Input stopped\n");
        active = false;
    };

    void StartInput(){
        active = true;
        while (active)
        {
            pushed_character = getchar();
            printf("You pressed: %c\n", pushed_character);
            
        }   
    }

   
};

int main(){
    TermiosManager termiosManager;
    termiosManager.StartInput();
    termiosManager.StopInput();
    return 0;
}