#include <stdio.h>
#include <string.h>
#include <stdbool.h>
// int boardSize=6;
// char board[26][26];

// function to print the board
void printBoard(char board[][26], int boardSize)
{
    int i, j;
    // print colm name in char
    printf("  ");
    for (i = 0; i < boardSize; i++)
    {
        printf("%c", i + 97);
    }
    printf("\n");
    // print row name in int
    for (i = 0; i < boardSize; i++)
    {
        printf("%c ", i + 97);
        for (j = 0; j < boardSize; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

// checks whether the specified (row, col) lies within the board dimensions
bool positionIn(int boardSize, int row, int col)
{
    if (row >= 0 && row < boardSize && col >= 0 && col < boardSize)
    {
        return true;
    }
    else
    {
        return false;
    }
}

char flipColor(char color)
{
    return (color == 'W') ? 'B' : 'W';
}

bool checkLegalInDirection(char board[][26], int boardSize, int row, int col, char colour, int deltaRow, int deltaCol)
{
    if (deltaCol == 0 && deltaRow == 0)
    {
        return false;
    }
    int forward = 0;
    int newRow = row + deltaRow;
    int newCol = col + deltaCol;
    char flippedColor = flipColor(colour);
    // printf("newRow: %d, newCol: %d, flippedColor=%c \n", newRow, newCol, flippedColor);
    // go forward until you find a piece of the opposite colour or reach the end of the board
    while (positionIn(boardSize, newRow, newCol) && board[newRow][newCol] == flippedColor)
    {
        newRow += deltaRow;
        newCol += deltaCol;
        forward++;
    }
    // printf("forward: %d\n", forward);
    // forward 0 means that there is no piece of the opposite colour in the direction
    if (forward == 0)
    {
        return false;
    }
    // if there is a piece of the opposite colour in the direction, check if there is a piece of the same colour in the direction
    if (positionIn(boardSize, newRow, newCol) && board[newRow][newCol] == colour)
    {
        return true;
    }
    return false;
}

// get available moving direction for a given colour and position
void availableMovingDirectionAtGivenPosAndColour(char board[][26], int boardSize, int row, int col, char colour)
{
    int i, j;
    for (i = -1; i <= 1; i++)
    {
        for (j = -1; j <= 1; j++)
        {
            if (checkLegalInDirection(board, boardSize, row, col, colour, i, j))
            {
                printf("row=%c col=%c rowdir=%d coldir=%d \n", row + 97, col + 97, i, j);
            }
        }
    }
}

bool isAvailableForMovingAtGivenPosAndColour(char board[][26], int boardSize, int row, int col, char colour)
{
    int i, j;
    if (board[row][col] != 'U')
    {
        return false;
    }
    for (i = -1; i <= 1; i++)
    {
        for (j = -1; j <= 1; j++)
        {
            if (checkLegalInDirection(board, boardSize, row, col, colour, i, j))
            {
                return true;
            }
        }
    }
    return false;
}

int printAvailablePositionsForColorGiven(char board[][26], int boardSize, char colour)
{
    int i, j;
    int count = 0;
    for (i = 0; i < boardSize; i++)
    {
        for (j = 0; j < boardSize; j++)
        {
            if (board[i][j] == 'U')
            {
                // availableMovingDirectionAtPos(board, boardSize, i, j, colour);
                if (isAvailableForMovingAtGivenPosAndColour(board, boardSize, i, j, colour))
                {
                    printf("%c%c \n", i + 97, j + 97);
                    count++;
                }
            }
        }
    }
    return count;
}

int getAvailablePositionsForColorGiven(char board[][26], int boardSize, char colour)
{
    int i, j;
    int count = 0;
    for (i = 0; i < boardSize; i++)
    {
        for (j = 0; j < boardSize; j++)
        {
            if (board[i][j] == 'U')
            {
                // availableMovingDirectionAtPos(board, boardSize, i, j, colour);
                if (isAvailableForMovingAtGivenPosAndColour(board, boardSize, i, j, colour))
                {
                    count++;
                }
            }
        }
    }
    return count;
}
bool updateBoard(char board[][26], int boardSize, char color, char row, char col)
{
    int i, j;
    int rowIndex = row - 97;
    int colIndex = col - 97;
    if (color != 'W' && color != 'B')
    {
        printf("Invalid color: %c\n", color);
        return false;
    }
    if (positionIn(boardSize, rowIndex, colIndex) == false)
    {
        printf("Invalid move!\n");
        return false;
    }
    if (board[rowIndex][colIndex] != 'U')
    {
        printf("Invalid move!\n");
        return false;
    }
    int updateFlag = 0;
    for (i = -1; i <= 1; i++)
    {
        for (j = -1; j <= 1; j++)
        {
            if (checkLegalInDirection(board, boardSize, rowIndex, colIndex, color, i, j))
            {
                updateFlag = 1;
                int newRow = rowIndex + i;
                int newCol = colIndex + j;
                while (board[newRow][newCol] == flipColor(color))
                {
                    board[newRow][newCol] = color;
                    newRow += i;
                    newCol += j;
                }
            }
        }
    }
    if (updateFlag == 1)
    {
        // printf("Valid Move!\n");
        board[rowIndex][colIndex] = color;
        return true;
    }
    else
    {
        printf("Invalid Move!\n");
        return false;
    }
}

void initializeBoard(char board[][26], int boardSize)
{
    int i = (boardSize / 2) - 1;
    board[i][i] = 'W';
    board[i][i + 1] = 'B';
    board[i + 1][i] = 'B';
    board[i + 1][i + 1] = 'W';
}
void EnterBoardConfiguration(char board[][26], int boardSize)
{
    char input[4];
    while (true)
    {
        scanf("%s", input);
        if (input[0] == '!')
        {
            break;
        }
        else
        {
            int row = input[1] - 97;
            int col = input[2] - 97;
            if (positionIn(boardSize, row, col))
            {
                board[row][col] = input[0];
            }
        }
    }
    printBoard(board, boardSize);
}

bool computerMove(char board[][26], int boardSize, char colour)
{
    int i, j;
    int row, col;
    int max = 0;
    int newRow, newCol;
    int availableFlag = 0;
    for (i = 0; i < boardSize; i++)
    {
        for (j = 0; j < boardSize; j++)
        {
            if (isAvailableForMovingAtGivenPosAndColour(board, boardSize, i, j, colour))
            {
                availableFlag = 1;
                int count = 0;
                for (int k = -1; k <= 1; k++)
                {
                    for (int l = -1; l <= 1; l++)
                    {
                        newRow = i + k;
                        newCol = j + l;
                        if (checkLegalInDirection(board, boardSize, i, j, colour, k, l))
                        {
                            while (board[newRow][newCol] == flipColor(colour))
                            {
                                newRow += k;
                                newCol += l;
                                count++;
                            }
                        }
                    }
                }
                if (count > max)
                {
                    max = count;
                    row = i;
                    col = j;
                }
            }
        }
    }
    if (availableFlag == 0)
    {
        return false;
    }
    printf("Computer place %c at: %c%c\n", colour, row + 97, col + 97);
    updateBoard(board, boardSize, colour, row + 97, col + 97);
    return true;
}

bool humanMove(char board[][26], int boardSize, char colour)
{
    char input[3];
    scanf("%s", input);
    //  printf("%c%c%c\n", colour, input[0], input[1]);
    return updateBoard(board, boardSize, colour, input[0], input[1]);
}
int coinCountOfGivenColorInBoard(char board[][26], int boardSize, char colour)
{
    int i, j;
    int count = 0;
    for (i = 0; i < boardSize; i++)
    {
        for (j = 0; j < boardSize; j++)
        {
            if (board[i][j] == colour)
            {
                count++;
            }
        }
    }
    return count;
}

bool checkIfGameOver(char board[][26], int boardSize)
{
    int countW = getAvailablePositionsForColorGiven(board, boardSize, 'W');
    int countB = getAvailablePositionsForColorGiven(board, boardSize, 'B');
    if (countW == 0 && countB == 0)
    {
        countW = coinCountOfGivenColorInBoard(board, boardSize, 'W');
        countB = coinCountOfGivenColorInBoard(board, boardSize, 'B');
        if (countW > countB)
        {
            printf("W player wins.\n");
        }
        else if (countB > countW)
        {
            printf("B player wins.\n");
        }
        else
        {
            printf("Draw!\n");
        }
        return true;
    }
    return false;
}

int main()
{
    char board[26][26];
    int boardSize = 6;
    memset(board, 'U', sizeof(board));
    printf("Enter the Board dimension :");
    scanf("%d", &boardSize);
    getchar();
    initializeBoard(board, boardSize);
    printf("Computer plays (B/W): ");
    char computerColor;
    scanf("%c", &computerColor);
    getchar();
    char humanColor = flipColor(computerColor);
    printBoard(board, boardSize);
    bool isComputerTurn = computerColor=='B'?true:false;
    while (true)
    {
        bool over = checkIfGameOver(board, boardSize);
            if (over == true)
            {
                break;
            }
        if (isComputerTurn)
        {
            
            over = computerMove(board, boardSize, computerColor);
            if (over == true)
            {
                printBoard(board, boardSize);
            }
            else
            {
                printf("%c Player has no move.\n", computerColor);
            }
            isComputerTurn = !isComputerTurn;

        }
        else
        {
            if (getAvailablePositionsForColorGiven(board, boardSize, humanColor) == 0)
            {
                printf("%c Player has no move.\n", humanColor);
            }
            else
            {
                printf("Enter move for color %c (RowCol): ", humanColor);
                over = humanMove(board, boardSize, humanColor);
                if (over == false)
                {
                    printBoard(board, boardSize);
                    printf("%c Player Wins!\n",computerColor);
                    break;
                }
                printBoard(board, boardSize);
            }

            isComputerTurn = !isComputerTurn;
        }
    }
    return 0;
}
    // char board[26][26];
    // int boardSize = 6;
    // memset(board, 'U', sizeof(board));
    // printf("Enter the Board dimension :");
    // scanf("%d", &boardSize);
    // initializeBoard(board, boardSize);
    // printBoard(board, boardSize);
    // printf("Enter board configuration :\n");
    // EnterBoardConfiguration(board, boardSize);
    // char input[4];
    // bool updateFlag = true;
    // while (updateFlag)
    // {
    //     printf("Available moves for A:\n");
    //     getAvailablePositionsInBoard(board, boardSize, 'W');
    //     printf("Available moves for B:\n");
    //     getAvailablePositionsInBoard(board, boardSize, 'B');
    //     printf("Enter a move: \n");
    //     scanf("%s", input);
    //     updateFlag=updateBoard(board, boardSize, input[0], input[1], input[2]);
    //     printBoard(board, boardSize);
    // }