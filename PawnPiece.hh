#ifndef __PAWNPIECE_H__
#define __PAWNPIECE_H__

#include "ChessPiece.hh"
#include "ChessBoard.hh"

/**
 * Student implementation of a Pawn chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class PawnPiece : public ChessPiece
    
    {
    private:
        mutable bool is_first_move; 
        mutable bool is_first_move_second; 
        mutable bool is_en_passant_attack;
    public:

        PawnPiece(ChessBoard& board, Color color, int row, int column);
        virtual Type getType() const;
        virtual ~PawnPiece();
        virtual bool canMoveToLocation(int toRow, int toColumn) const override;
        virtual const char* toString() override;
        void setFirstMoveFalse();
        bool isEnPassantAttack() const;

        // Sets the en passant attack capability
        void setIsEnPassantAttack(bool value);

        // Check if this pawn can execute an en passant
        bool canExecuteEnPassant(int toRow, int toColumn) const;

        // Getters for pawn status
        bool getIsFirstMove() const;
        bool getIsEnPassantAttack() const;
    };
}

#endif
