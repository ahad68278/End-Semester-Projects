#include <iostream>
using namespace std;

// Initialize the board
void initBoard(char board[8][8])
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            board[i][j] = ' ';

    // Black pieces
    board[0][0] = 'R';
    board[0][1] = 'N';
    board[0][2] = 'B';
    board[0][3] = 'Q';
    board[0][4] = 'K';
    board[0][5] = 'B';
    board[0][6] = 'N';
    board[0][7] = 'R';
    for (int j = 0; j < 8; j++)
    {
        board[1][j] = 'P';
    }

    // White pieces
    for (int j = 0; j < 8; j++)
    {
        board[6][j] = 'p';
    }
    board[7][0] = 'r';
    board[7][1] = 'n';
    board[7][2] = 'b';
    board[7][3] = 'q';
    board[7][4] = 'k';
    board[7][5] = 'b';
    board[7][6] = 'n';
    board[7][7] = 'r';
}

// Print the board with row and column labels
void printBoard(char board[8][8])
{
    cout << endl
         << "    a   b   c   d   e   f   g   h" << endl;

    for (int i = 0; i < 8; i++)
    {
        cout << "  +---+---+---+---+---+---+---+---+\n";
        cout << 8 - i << " |";

        for (int j = 0; j < 8; j++)
        {
            cout << " " << board[i][j] << " |";
        }
        cout << " " << 8 - i << endl;
    }
    cout << "  +---+---+---+---+---+---+---+---+\n";
    cout << "    a   b   c   d   e   f   g   h" << endl;
    cout << " " << endl;
    // DUCKING Board took me 40 min to figure out the layer
}

// converting moves from char to int
void Movesconversion(char &currentmovebase1, int &currentmove2, char &futuremovebase1, int &futuremove2,
                     int &currentCol, int &currentRow, int &futureCol, int &futureRow)
{
    currentCol = currentmovebase1 - 'A';
    futureCol = futuremovebase1 - 'A';
    currentRow = 8 - currentmove2;
    futureRow = 8 - futuremove2;
}

// Inputing moves
void Inputmoves(char &currentmovebase1, int &currentmove2, char &futuremovebase1, int &futuremove2, int &currentCol, int &currentRow, int &futureCol, int &futureRow)
{
    while (true)
    {
        cout << "Enter Move: ";
        cin >> currentmovebase1 >> currentmove2 >> futuremovebase1 >> futuremove2;
        if ((currentmovebase1 >= 'A' && currentmovebase1 <= 'H') && (futuremovebase1 >= 'A' && futuremovebase1 <= 'H'))
        {
            Movesconversion(currentmovebase1, currentmove2, futuremovebase1, futuremove2,
                            currentCol, currentRow, futureCol, futureRow);
            break;
        }
        else
        {
            cout << "Invalid Input" << endl;
            continue;
        }
    }
}

// Moves validation
bool movesvalid(int &currentCol, int &currentRow, int &futureCol, int &futureRow)
{
    char currentmovebase1, futuremovebase1;
    int currentmove2, futuremove2;
    while (true)
    {
        Inputmoves(currentmovebase1, currentmove2, futuremovebase1, futuremove2, currentCol, currentRow, futureCol, futureRow); // inputing moves

        if ((currentCol >= 0 && currentCol < 8) && (currentRow >= 0 && currentRow < 8) // moves validation
            && (futureCol >= 0 && futureCol < 8) && (futureRow >= 0 && futureRow < 8))
        {
            // cout << "Valid Input" << endl;
            return true;
        }
        else
        {
            cout << "Invalid Move!!" << endl;
        }
    }
}

// Piece check
bool PlayerCh(char board[8][8], int currentCol, int currentRow, bool whiteTurn)
{
    char piece = board[currentRow][currentCol];
    if (board[currentRow][currentCol] == ' ') // if current move is empty
    {
        return false;
    }
    if (whiteTurn && islower(piece))
    {
        return true; // white's turn, lowercase piece
    }
    if (!whiteTurn && isupper(piece))
    {
        return true; // black's turn, uppercase piece
    }
    else
    {
        return false;
    }
}

// Pawn Move Validation
bool PawnValid(char board[8][8], int currentRow, int currentCol, int futureRow, int futureCol, bool whiteTurn)
{
    char piece = board[currentRow][currentCol];
    char target = board[futureRow][futureCol];
    int direction; // to move pawn by 1 distance
    if (whiteTurn)
    {
        direction = -1; // for white pawn
    }
    else
    {
        direction = 1; // for balck pawn
    }
    if (futureCol == currentCol && futureRow == currentRow + direction && target == ' ') // if pawn moves from its original position
    {
        return true;
    }
    if (futureCol == currentCol && futureRow == currentRow + direction * 2) // for first move of pawn +2
    {
        int startRow;
        if (whiteTurn)
        {
            startRow = 6; // for white pawn first move array
        }
        else
        {
            startRow = 1; // for white pawn first move array
        }
        if (currentRow == startRow && board[currentRow + direction][currentCol] == ' ' && target == ' ') // to see if there is a piece in way or not
        {
            return true;
        }
    }
    if ((futureCol == currentCol + 1 || futureCol == currentCol - 1) && futureRow == currentRow + direction)
    {
        if (target != ' ' && ((whiteTurn && isupper(target)) || (!whiteTurn && islower(target)))) // to capture a piece if it is diagonally ahead
        {
            return true;
        }
    }
    return false;
}

// Rook Move Validation
bool RookValid(char board[8][8], int currentRow, int currentCol, int futureRow, int futureCol, bool whiteTurn)
{
    char piece = board[currentRow][currentCol];
    char target = board[futureRow][futureCol];
    if (currentRow != futureRow && currentCol != futureCol)
    {
        return false;
    }
    // to move Rook by whole array board
    if (currentRow == futureRow)
    {
        int startCol = min(currentCol, futureCol) + 1; // where can it start traveling
        int endCol = max(currentCol, futureCol) - 1;   // where can its range end traveling
        // for Rooks col
        for (int c = startCol; c <= endCol; c++) // check to see if path is free to travel
        {
            if (board[currentRow][c] != ' ')
            {
                return false; // if there is a piece in b/t the destination = no travel
            }
        }
        if (target == ' ')
        {
            return true;
        }
        if (whiteTurn && isupper(target))
        {
            return true;
        }
        if (!whiteTurn && islower(target))
        {
            return true;
        }
    }
    // for Rooks Row
    else if (currentCol == futureCol)
    {
        int startRow = min(currentRow, futureRow) + 1;
        int endRow = max(currentRow, futureRow) - 1;
        for (int r = startRow; r <= endRow; r++)
        {
            if (board[r][currentCol] != ' ')
            {
                return false;
            }
        }
        if (target == ' ')
        {
            return true;
        }
        if (whiteTurn && isupper(target))
        {
            return true;
        }
        if (!whiteTurn && islower(target))
        {
            return true;
        }
    }
    return false;
}

// Knight Move Validation
bool KnightValid(char board[8][8], int currentRow, int currentCol, int futureRow, int futureCol, bool whiteTurn)
{
    char target = board[futureRow][futureCol];
    int rowDiff = (currentRow - futureRow); // for how far is it going
    int colDiff = (currentCol - futureCol);
    // for postive rowDiff and colDiff converstion
    if (rowDiff < 0)
    {
        rowDiff = -(rowDiff);
    }
    if (colDiff < 0)
    {
        colDiff = -(colDiff);
    }
    // only move in below condtion if not then wronge move
    if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)))
    {
        return false;
    }
    if (target == ' ')
    {
        return true;
    }
    if (whiteTurn && isupper(target))
    {
        return true;
    }
    if (!whiteTurn && islower(target))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Bishop Move Validation
bool BishopValid(char board[8][8], int currentRow, int currentCol, int futureRow, int futureCol, bool whiteTurn)
{
    char target = board[futureRow][futureCol];
    int rowDiff = currentRow - futureRow; // for how far is it going
    int colDiff = currentCol - futureCol;
    // for postive rowDiff and colDiff converstion
    if (rowDiff < 0)
    {
        rowDiff = -(rowDiff);
    }
    if (colDiff < 0)
    {
        colDiff = -(colDiff);
    }
    if (rowDiff != colDiff) // not diagonal
    {
        return false;
    }
    // row distance travel
    int rowstep;
    if (futureRow > currentRow)
    {
        rowstep = 1;
    }
    else
    {
        rowstep = -1;
    }
    // col distance travel
    int colstep;
    if (futureCol > currentCol)
    {
        colstep = 1;
    }
    else
    {
        colstep = -1;
    }

    int r = currentRow + rowstep; // for moving down the array
    int c = currentCol + colstep; // for moving up the array
    // loop to keep going reach destination
    while (r != futureRow)
    {
        if (board[r][c] != ' ')
        {
            return false;
        }
        r = r + rowstep;
        c = c + colstep;
    }
    if (target == ' ')
    {
        return true;
    }
    if (whiteTurn && isupper(target))
    {
        return true;
    }
    if (!whiteTurn && islower(target))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// King Move Validation
bool KingValid(char board[8][8], int currentRow, int currentCol, int futureRow, int futureCol, bool whiteTurn)
{
    char target = board[futureRow][futureCol];
    int rowDiff = (currentRow - futureRow);
    int colDiff = (currentCol - futureCol);
    // move convertion for moving up or down the array
    if (rowDiff < 0)
    {
        rowDiff = -(rowDiff);
    }
    if (colDiff < 0)
    {
        colDiff = -(colDiff);
    }
    // can't move more then 1 square
    if (rowDiff > 1 || colDiff > 1 || (rowDiff == 0 && colDiff == 0))
    {
        return false;
    }
    if (target == ' ')
    {
        return true;
    }
    if (whiteTurn && isupper(target))
    {
        return true;
    }
    if (!whiteTurn && islower(target))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Move to chech which piece
bool MoveCh(char board[8][8], int currentRow, int currentCol,
            int futureRow, int futureCol, bool whiteTurn)
{
    char piece = board[currentRow][currentCol];

    if (piece == 'p' || piece == 'P')
    {
        return PawnValid(board, currentRow, currentCol, futureRow, futureCol, whiteTurn);
    }
    else if (piece == 'r' || piece == 'R')
    {
        return RookValid(board, currentRow, currentCol, futureRow, futureCol, whiteTurn);
    }
    else if (piece == 'n' || piece == 'N')
    {
        return KnightValid(board, currentRow, currentCol, futureRow, futureCol, whiteTurn);
    }
    else if (piece == 'b' || piece == 'B')
    {
        return BishopValid(board, currentRow, currentCol, futureRow, futureCol, whiteTurn);
    }
    else if (piece == 'q' || piece == 'Q')
    {
        return RookValid(board, currentRow, currentCol, futureRow, futureCol, whiteTurn) ||
               BishopValid(board, currentRow, currentCol, futureRow, futureCol, whiteTurn);
    }
    else if (piece == 'k' || piece == 'K')
    {
        return KingValid(board, currentRow, currentCol, futureRow, futureCol, whiteTurn);
    }

    return false;
}

// GameEnd
bool KingExists(char board[8][8], char kingChar)
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (board[r][c] == kingChar)
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    char board[8][8];
    int currentmove2, futuremove2, currentCol, currentRow, futureCol, futureRow;
    char currentmovebase1, futuremovebase1;
    bool whiteTurn = true;
    initBoard(board);
    while (true)
    {
        printBoard(board);

        if (whiteTurn)
        {
            cout << "White's turn" << endl;
        }
        else
        {
            cout << "Black's turn" << endl;
        }
        cout << "Please Enter Move like E 4 D 2:" << endl;

        movesvalid(currentCol, currentRow, futureCol, futureRow);
        if (!PlayerCh(board, currentCol, currentRow, whiteTurn))
        {
            cout << "Wrong player or empty square! Try again." << endl;
            continue;
        }
        if (MoveCh(board, currentRow, currentCol, futureRow, futureCol, whiteTurn))
        {
            board[futureRow][futureCol] = board[currentRow][currentCol];
            board[currentRow][currentCol] = ' ';

            if (!KingExists(board, 'k'))
            {
                cout << "Black wins! White king is gone." << endl;
                break;
            }

            if (!KingExists(board, 'K'))
            {
                cout << "White wins! Black king is gone." << endl;
                break;
            }
        }
        else
        {
            cout << "Invalid move! Try again." << endl;
            continue;
        }
        whiteTurn = !whiteTurn;
    }
    return 0;
}
