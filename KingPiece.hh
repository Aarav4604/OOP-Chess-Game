#ifndef __KINGPIECE_H__
#define __KINGPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a King chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class KingPiece : public ChessPiece
    {
        public:

            KingPiece(ChessBoard& board, Color color, int row, int column);
            virtual ~KingPiece();
            virtual Type getType() const ;
            virtual bool canMoveToLocation(int toRow, int toColumn) const override;
            virtual const char* toString() override;

    };
}

#endif
