#include <iostream>
#include <string>
#include "include/linux/LinuxInput.h"
using namespace std;

int main(){
   InputManager inputManager; //call 

    while (true) {
        char a = inputManager.isCharacterPushed();

        if (a == 'w') {
            printf("Hello World\n");
            break;
        } 
        else {
            printf("%c", a);  
        }
    }
    
    return 0;
}
