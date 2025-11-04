#include <iostream>
#include <string>
#include "include/linux/LinuxInput.h"
using namespace std;

int main(){
    InputManager inputManager;
    inputManager.StartMouseInput();
    inputManager.GetMousePosition();
    
    return 0;
}
