#include <iostream>
#include <string>
#include "include/linux/termiosInput.h"
using namespace std;

int main(){
    InputManager inputManager;
    char inp = inputManager.isCharacterPushed();
    cout << inp << " karakteri basıldı." << endl;
    while (true)
    {   
        char inp = inputManager.isCharacterPushed();
        if (inputManager.isCharacterPushed() == 'a')
        {
            cout << "a karakteri basıldı, çıkılıyor." << endl;
            break;
        } 
    }
    
    return 0;
}
