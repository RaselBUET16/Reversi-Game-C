#include<stdio.h>
#include<string.h>
#include<stdbool.h>
// int boardSize=6;
// char board[26][26];

// function to print the board
void printBoard(char board[][26], int boardSize)
{
    int i, j;
    //print colm name in char
    printf("  ");
    for(i=0; i<boardSize; i++)
    {
        printf("%c ", i+97);
    }
    printf("\n");
    //print row name in int
    for(i=0; i<boardSize; i++)
    {
        printf("%c ", i+97);
        for(j=0; j<boardSize; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

//checks whether the specified (row, col) lies within the board dimensions
bool postitionIn(int boardSize,int row, int col)
{
    if(row>=0 && row<boardSize && col>=0 && col<boardSize)
    {
        return true;
    }
    else
    {
        return false;
    }
}



int main(){
   char board[26][26];
   memset(board,'U',sizeof(board));
   int boardSize=6;
   printf("Enter the size of board\n");
//    scanf("%d",&boardSize);
    printBoard(board,boardSize);
    
}