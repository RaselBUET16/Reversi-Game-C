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



int main(){
   char board[26][26];
   memset(board,'U',sizeof(board));
   int boardSize=6;
   printf("Enter the size of board\n");
//    scanf("%d",&boardSize);
    printBoard(board,boardSize);
    
}