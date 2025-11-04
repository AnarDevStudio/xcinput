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

            //input read
            switch (pushed_character)
            {
                case 27:
                    printf("You pressed: Escape\n");
                    break;
                case 32:
                    printf("You pressed: Space\n");
                    break;
                case 10:
                    printf("You pressed: Enter\n");
                    break;
                case 127:
                    printf("You pressed: Backspace\n");
                    break;
                default:
                    break;
            };   
        }
    };
};

int main(){
    TermiosManager termiosManager;
    termiosManager.StartInput();
    termiosManager.StopInput();
    return 0;
}