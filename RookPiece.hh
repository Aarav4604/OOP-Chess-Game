#ifndef _ROOKPIECE_H__
#define _ROOKPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Rook chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class RookPiece : public ChessPiece
    {
        public:
        RookPiece(ChessBoard& board, Color color, int row, int column);
        virtual ~RookPiece();
        virtual Type getType() const;
        virtual bool canMoveToLocation(int toRow, int toColumn) const override;
        virtual const char* toString() override;
    };
}

#endif
