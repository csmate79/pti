#include <iostream>
#include <unistd.h> 
#include <stdlib.h> 
#include <math.h>   

using namespace std;

int main(){
    int width = 64 , height = 32;   
    int x = 10, y = 10;   
    int x1 = x, y1 = y;

    for (int i = 1; i < 2; i=i+0){ 

        usleep(50000);  
        system("clear");

        x += pow(-1, (x1-1)/(width-3));
        y += pow(-1, (y1-1)/(height-3));
        x1++;
        y1++;

        for(int i = 0; i < width; i++){ 
            cout <<".";
		
        }
        cout << "\n";

        for(int i = 0; i < y-1; i++){
            cout << "|";
            for(int j = 0; j < width-2; j++){  
                cout << " ";
            }
            cout << "|" << "\n";
        }

        cout << " ";   
        for(int i = 0; i < x-1; i++){  
            cout << " ";
        }
        cout << "O";
        for(int i = x+1; i < width-1; i++){ 
            cout << " ";
        }
        cout << "|" << "\n";

        for(int i = y; i < height-2; i++){
            cout << "|";
            for(int j = 0; j < width-2; j++){
                cout << " ";
            }
            cout << "|" << "\n";
        }

        for(int i = 0; i < x-1; i++){   
            cout << ".";
        }
        cout << " ";
        for(int i = x; i < width; i++){
            cout << ".";
        }

        cout << "\n\n" << "Koordinatak:" << "\nx:" << x << " y:" << y << endl;
    }
    return 0;
}
