#ifndef __KNIGHTPIECE_H__
#define __KNIGHTPIECE_H__

#include "ChessPiece.hh"
#include "ChessBoard.hh"

/**
 * Student implementation of a Pawn chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class KnightPiece : public ChessPiece
    {
    public:

        KnightPiece(ChessBoard& board, Color color, int row, int column);
        virtual Type getType() const;
        virtual ~KnightPiece();
        virtual bool canMoveToLocation(int toRow, int toColumn) const override;


        virtual const char* toString() override;
    };
}

#endif
