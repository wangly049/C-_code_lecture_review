#include<iostream>
#include<ctime>
#include<iomanip>

using namespace std;
/*
You can do your work based on this code. but if you submit this code for assignment10, you will get 0.
1.create a two-dementional array named GophersMap
   1.1 create the GophersMap array;
   1.2 place 10 gophers in the array;
   1.3 if the cell does not contain a gopher, sum the number of gophers in its adjcent 8 cells;
2.create the other two-demensional array, which works as the mask of GophersMap, which called Mask
3.define the user's action. Users have two action in this game. One is open a cell and the other is setting or removing gophers flag
   3.1 open a cell in Mask array. To achieve this action, we need to copy the value in GophersMap to Mask array. It has 3 situations:
       3.1.1 if the user open a cell containing a gophers, game over;
       3.1.2 if the user open a cell containing a number which indicates the amount of gophers around the cell,and the corresponding cell in Mask
            is '*', copy its number to Mask array;
       3.1.3 if the user open a cell containing '0', automatically open its adjacent cells without gophers
   3.2 set or remove the gophers flag
4.check win status
5.input symbols to open cell or set flat to begin the game.
6. the rule of the game: when the user open a cell with gophers game over(), (EndGameLose = True) player loose; when the player set all the gophers flag 
   correctly to cells containing the gophers, (CheckWinStatus = 1), the player win. besides the above two situations, the game loop. 
*/


char GophersMap[10][10];//declare GophersMap array
char Mask[10][10];//declare Mask array
char Symbol; // declare a input symbol
bool EndGameLose = false;
int FlagCounter = 0;
int GopherFlaggedCounter = 0;


void CreateGophersMap();//create GophersMaps array
void SetGophersMap();//set gophers and numbers in GophersMaps
void CreateMask();//create Mask array
void PrintMask(char [][10]);// print Mask array
void RevealeAdjacentCell(int, int);// reveal its adjacent cell if a cell contains 0 gophers
void OpenCell();//open the cell
void SetOrRemoveGophersFlag();//set or remove flag
bool CheckWinStatus();//check win status
void InputSymbol();//input a symbol to begin the game

int main(){
    CreateGophersMap();
    SetGophersMap();
    //PrintMask(GophersMap);

    CreateMask();
    while(!EndGameLose && !CheckWinStatus()){
        PrintMask(Mask);
        InputSymbol();
    }
    if(EndGameLose){
        PrintMask(Mask);
        cout << "The cell contains a gophers. Game Over." << endl;
    }
    if(CheckWinStatus()){
        PrintMask(Mask);
        cout << "You find all the gophers. You WIN!" << endl;
    }
}




//-------create GophersMap---------------
void CreateGophersMap(){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            GophersMap[i][j] = '0';
        }
    }
}
//------------place 10 gophers and if a cell does not contains gophers, sum the amount of gophers in its adjacent cell----------- 
void SetGophersMap(){
    //create 10 gophers randomly
    srand(time(NULL));
    for (int i = 0; i < 10; i++){
        int r = rand()%10;
        int c = rand()%10; 
        if (GophersMap[r][c] == '0'){
            GophersMap[r][c] = 'X';// X represents gophers.
            i++;
        }
    }
    //if a cell does not contains a gopher,sum the amount of gophers in its adjacent cells
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if (GophersMap[i][j] == 'X'){
                for (int r = i-1; r <= i+1; r++){
                    for (int c = j-1; c <= j+1; c++){
                        if(r >= 0 && r < 10 && c >= 0 && c < 10 && GophersMap[r][c] != 'X'){
                            GophersMap[r][c]++;
                        }

                    }
                }
            }
        }
    }

}
//----------create Mask array--------------------
void CreateMask(){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            Mask[i][j] = '*';
        }
    }
}
//-------------print Mask array------------------
void PrintMask(char arr[10][10]){
    cout << "   ";
    for (int i = 0; i < 10; i++){
        cout << setw(3) << i;
    }
    cout << endl;
    for (int i = 0; i < 37; i++){
        cout << "_";
    }
    cout << endl;
    for (int i = 0; i < 10; i++){
        cout << setw(3) << i << "|";
        for (int j = 0; j < 10; j++){
            cout << setw(3) << arr[i][j];
        }
        cout << endl;
    }
}
//----------reveal adjacent cells-------------
void RevealeAdjacentCell(int i, int j){
    if (Mask[i][j]== '*' && GophersMap[i][j] != 'X' && i >= 0 && i < 10 && j >= 0 && j < 10){
        Mask[i][j] = GophersMap[i][j];
        if (GophersMap[i][j] == '0'){
            for (int r = i-1; r <= i+1; r++){
                for(int c = j-1; c <= j+1; c++){
                    RevealeAdjacentCell(r,c);
                }
            }
        }
    }
}
//---------open cell, copy the value from GophersMap to Mask array-------
void OpenCell(){
    int i,j;
    do{
        cout << "Please enter a number between 0 - 9 as row number: " << endl;
        cout << "Please enter a number between 0 - 9 as column number: " << endl;
        cin >> i >> j;
    }while (i < 0 || i > 9 || j < 0 || j > 9);
    if (GophersMap[i][j] == 'X'){
        Mask[i][j] = 'X';
        EndGameLose = true;
    }else{RevealeAdjacentCell(i,j);}
}

//----------set or remove gophers flag---------------------
void SetOrRemoveGophersFlag(){
    int i,j;
    do {
        cout << "Please enter a number between 0 - 9 as row number: " << endl;
        cout << "Please enter a number between 0 - 9 as column number: " << endl;
        cin >> i >> j;
    }while (i < 0 || i > 9 || j < 0 || j > 9);
    if(Mask[i][j] == '*'){
        Mask[i][j] = 'F';
        FlagCounter++;
        if(GophersMap[i][j] == 'X'){
            GopherFlaggedCounter++;
        }
    }else if(Mask[i][j] == 'F'){
        Mask[i][j] = '*';
        FlagCounter--;
        if(GophersMap[i][j] == 'X'){
            GopherFlaggedCounter--;
        }
    }

}
//---------------check win status------------
bool CheckWinStatus(){
    if(FlagCounter == 10 && GopherFlaggedCounter == 10){
        return 1;
    }else{return 0;}
}
//------------input the symbol to open a cell or set a flag to begin the game-------
void InputSymbol(){
    cout << "enter a symbol to begin the game. 'o' represent open a cell; 'f' represent set a flag." << endl;
    cin >> Symbol;
    switch(Symbol){
        case 'o':
        OpenCell(); break;
        case 'f':
        SetOrRemoveGophersFlag(); break;
        default:
        InputSymbol();
    }

}
