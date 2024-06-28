#ifndef _CHESSBOARD_H__
#define _CHESSBOARD_H__

#include "ChessPiece.hh"
#include "KingPiece.hh"
#include <list>
#include <vector>
#include <sstream>

namespace Student
{
    class ChessBoard
    {
    std::pair<int, int> lastMoveFrom;
    //std::pair<int, int> lastMoveTo;
    ChessPiece* lastMovedPiece = nullptr;
    private:
        int numRows = 0;
        int numCols = 0;
        Color turn = White;
        //bool lastMoveWasDoublePawnMove;
        bool hasKingMoved;
        bool hasRookMoved[2];
        /**
         * @brief
         * A 2D vector of pointers to ChessPiece objects.
         * board.at(row) returns the entire row.
         * board.at(row).at(col) returns a pointer to a ChessPiece object.
         * *(board.at(row).at(col)) returns the ChessPiece object itself.
         */
        std::vector<std::vector<ChessPiece* >> board;
        //std::pair<int, int> lastDoubleStepPawnPos;
        int lastMoveFromRow;
    int lastMoveFromColumn;
    int lastMoveToRow;
    int lastMoveToColumn;
    Color lastMovePieceColor;
    Type lastMovePieceType;
    //bool lastMoveWasDoublePawnMove;
    bool hasMoved;


    public:
        std::pair<int, int> lastMoveTo;
        bool isEmpty(int row, int col)const;
        bool lastMoveWasDoublePawnMove;
        std::pair<int, int> lastDoubleStepPawnPos;
        void isValidScan(int n, int m);
        float scoreBoard();
        float getHighestNextScore();
        bool executeCastling(int fromRow, int fromColumn, int toRow, int toColumn);
        bool executeEnPassant(int fromRow, int fromColumn, int toRow, int toColumn);
        void updateTurn();
        /**
         * @brief
         * Allocates memory on the heap for the board.
         * Remember to initialise all pointers to nullptr.
         * @param numRow
         * Number of rows of the chess board.
         * @param numCol
         * Number of columns of the chessboard
         */
        ChessBoard(int numRow, int numCol);
        virtual ~ChessBoard();

        /**
         * @return
         * Number of rows in chess board.
         */
        int getNumRows() { return numRows; }

        /**
         * @return
         * Number of columns in chess board.
         */
        int getNumCols() { return numCols; }

        /**
         * @return
         * Pointer to a piece.
         */
        ChessPiece *getPiece(int r, int c)const { return board.at(r).at(c); }

        /**
         * @brief
         * Allocates memory for a new chess piece and assigns its
         * address to the corresponding pointer in the 'board' variable.
         * Remove any existing piece first before adding the new piece.
         * @param col
         * Color of the piece to be created.
         * @param ty
         * Type of the piece to be created.
         * @param startRow
         * Starting row of the piece to be created.
         * @param startColumn
         * Starting column of the piece to be created.
         */
        void createChessPiece(Color col, Type ty, int startRow, int startColumn);

        /**
         * @brief
         * Performs the move if the move is valid.
         * Account for the turn, staying within bounds and validity of the move.
         * This function is only needed for Part 2 and Part 3.
         * You can define a dummy implementation for Part 1 to get the code to compile.
         * @param fromRow
         * The row of the piece to be moved.
         * @param fromColumn
         * The column of the piece to be moved.
         * @param toRow
         * The row of the destination position.
         * @param toColumn
         * The column of the destination position.
         * @return
         * A boolean indicating whether move was executed successfully.
         */
        bool movePiece(int fromRow, int fromColumn, int toRow, int toColumn);
        bool isWithinBoard(int row, int column);
        bool isEnemyPiece(int row, int col, Color color)const ;

        /**
         * @brief
         * Checks if a move is valid without accounting for turns.
         * @param fromRow
         * The row of the piece to be moved.
         * @param fromColumn
         * The column of the piece to be moved.
         * @param toRow
         * The row of the destination position.
         * @param toColumn
         * The column of the destination position.
         * @return
         * Returns true if move may be executed without accounting for turn.
         */
        bool isValidMove(int fromRow, int fromColumn, int toRow, int toColumn);


        /**
         * @brief
         * Checks if the piece at a position is under threat.
         * @param row
         * Row of piece being checked.
         * @param column
         * Column of piece being checked.
         * @return
         * Returns true if a piece exists at the stated position, and an opponent
         * piece may move to the position.
         */
        bool isPieceUnderThreat(int row, int column);
        bool isPathClear(int fromRow, int fromColumn, int toRow, int toColumn) const;

        /**
         * @brief
         * Returns an output string stream displaying the layout of the board.
         * An ostringstream is used to automatically handle formatting of integers
         * and special characters into their string representations.
         * @return
         * An output stream containing the full board layout.
         */
        std::ostringstream displayBoard();
        bool isInCheckAfterMove(int fromRow, int fromCol, int toRow, int toColumn, Color playerColor);
        bool isKingInCheck(Color kingColor);
        bool isKingCaptured(Color kingColor);

       int getLastMoveFromRow() const { return lastMoveFromRow; }
    int getLastMoveFromColumn() const { return lastMoveFromColumn; }
    int getLastMoveToRow() const { return lastMoveToRow; }
    int getLastMoveToColumn() const { return lastMoveToColumn; }
    Color getLastMovePieceColor() const { return lastMovePieceColor; }
    bool wasLastMoveDoublePawnMove() const { return lastMoveWasDoublePawnMove; }
    void setHasMoved(bool moved) { hasMoved = moved; }
    bool getHasMoved() const { return hasMoved; }
    };
}

#endif
