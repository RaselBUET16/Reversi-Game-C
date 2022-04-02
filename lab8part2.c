#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>


struct availableMove{
	char *list;
	int size;
};
struct node{
	char x;
	char y;
	int value;
};


struct availableMove generateValidMoves(char board[][26],int boardSize,char colour );
int evaluate(char board[][26], int boardSize, int colour);
struct node getMin(char board[][26],int boardSize , char colour , struct availableMove avail,int depth);
struct node getMax(char board[][26],int boardSize , char colour , struct availableMove avail,int depth);
int computerTurn(char board[][26],int boardSize , char colour,int depth );


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
bool updateBoard(char board[][26], int boardSize, char color, char row, char col,char dummy)
{
    int i, j;
    int rowIndex = row - 97;
    int colIndex = col - 97;
    if (color != 'W' && color != 'B')
    {
        if(!dummy)printf("Invalid color: %c\n", color);
        return false;
    }
    if (positionIn(boardSize, rowIndex, colIndex) == false)
    {
        if(!dummy)printf("Invalid move!\n");
        return false;
    }
    if (board[rowIndex][colIndex] != 'U')
    {
        if(!dummy)printf("Invalid move!\n");
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
        if(!dummy)printf("Invalid Move!\n");
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
    updateBoard(board, boardSize, colour, row + 97, col + 97,false);
    return true;
}

bool humanMove(char board[][26], int boardSize, char colour)
{
    char input[3];
    scanf("%s", input);
    //  printf("%c%c%c\n", colour, input[0], input[1]);
    return updateBoard(board, boardSize, colour, input[0], input[1],false);
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
            
            over = computerTurn(board, boardSize, computerColor,4);
            // over = computerMove(board, boardSize, computerColor);
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

struct availableMove generateValidMoves(char board[][26],int boardSize,char colour ){
	char * ret = (char *) malloc(sizeof(char) * 3 * 26 * 26);
	int cnt = 0 ;
	memset(ret,0,sizeof(char) * 3 * 26 * 26);
	for (int i = 0 ; i < boardSize ; i++){
		for (int j = 0 ; j < boardSize; j++){
			if(board[i][j] != 'U') continue;
			bool checked_valid = false;
			int num=0;
			for (int  k = -1; k <=1 && !checked_valid; k++){
				for (int l = -1 ; l <=1 ; l++){
					if ( (!k) && (!l) ) continue;
					if ((num=checkLegalInDirection(board,boardSize,i,j,colour,k,l)) ==true) { // '=' in purpose dont't change !!!!! 
						checked_valid = true;
						break;
					}
				}
			}
			if (checked_valid){
				*(ret+3*cnt) =(char)'a'+i;
				*(ret+3*cnt + 1) =(char)'a'+j;
				*(ret+3*cnt++ + 2) =num;
			}
		}
	}
	struct availableMove ret_pack;
	ret_pack.list = ret;
	ret_pack.size = cnt;
	return ret_pack;
}

int evaluate(char board[][26], int boardSize, int colour){
	int table[8][8] ={{500,-25,10,5,5,10,-25,500},
 					{-25,-45,1,1,1,1,-45,-25},
 					{10,1,3,2,2,3,1,10},
 					{5,1,2,1,1,2,1,5},
 					{5,1,2,1,1,2,1,5},
 					{10,1,3,2,2,3,1,10},
 					{-25,-45,1,1,1,1,-45,-25},
 					{500,-25,10,5,5,10,-25,500}};
	int B = 0 , W = 0 ;
	for(int i = 0; i < boardSize ; i++){
		for (int j = 0 ; j < boardSize ; j++){
			if (board[i][j]=='B') B+=table[i][j];
			if (board[i][j]=='W') W+=2*table[i][j];
		}
	}
	int delta = B-W+20*getAvailablePositionsForColorGiven(board,boardSize,'B')-20*getAvailablePositionsForColorGiven(board,boardSize,'W');
	// printf("%d\n",delta );
	return colour=='B'?delta:-delta;
}


struct node getMin(char board[][26],int boardSize , char colour , struct availableMove avail,int depth){
	if (!depth){
		struct node ret ;
		ret.x = 0 ;
		ret.y = 0 ;
		ret.value = evaluate(board, boardSize,colour);
		return ret;
	}
	struct node ret ;
	int min = 0x7fffff;
	int min_index = 0;
	for (int i = 0 ; i < avail.size ; i++){
		char cpBoard[26][26];
		memcpy(cpBoard,board,sizeof(cpBoard));
		updateBoard(cpBoard,boardSize,colour,*(avail.list+3*i), *(avail.list + 3*i + 1 ) ,true);
		struct availableMove available = generateValidMoves(cpBoard,flipColor(colour),boardSize);
		int value = getMax(cpBoard,boardSize,colour,available,depth-1).value;
		if (value < min){
			min = value;
			min_index = i ;
		}
	}
	ret.x=*(avail.list+3*min_index);
	ret.y=*(avail.list+3*min_index+1);
	ret.value = min;
	return ret ;
}
struct node getMax(char board[][26],int boardSize , char colour , struct availableMove avail,int depth){
	if (!depth){
		struct node ret ;
		ret.x = 0 ;
		ret.y = 0 ;
		ret.value = evaluate(board, boardSize,colour);
		return ret;
	}
	struct node ret ;
	int max = -0x7fffff;
	int maxIndex = 0;
	for (int i = 0 ; i < avail.size ; i++){
		char cpBoard[26][26];
		memcpy(cpBoard,board,sizeof(cpBoard));
		updateBoard(cpBoard,boardSize,colour,*(avail.list+3*i), *(avail.list + 3*i + 1 ) ,true);
		struct availableMove available = generateValidMoves(cpBoard,boardSize,flipColor(colour));
		int value = getMin(cpBoard,boardSize,colour,available,depth-1).value;
		if (value > max){
			max = value;
			maxIndex = i ;
		}
	}
	ret.x=*(avail.list+3*maxIndex);
	ret.y=*(avail.list+3*maxIndex+1);
	ret.value = max;
	return ret ;
}
int computerTurn(char board[][26],int boardSize , char colour,int depth ){
	if (depth==0) return evaluate(board,boardSize,colour);
	struct availableMove available = generateValidMoves(board, boardSize, colour);
	struct node decision = getMax(board,boardSize,colour,available,depth);
	printf("Computer places %c at %c%c.\n", colour, decision.x ,decision.y);
	return updateBoard(board, boardSize, colour, decision.x, decision.y,false);
}
