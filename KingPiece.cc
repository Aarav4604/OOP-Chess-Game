#include "KingPiece.hh"
#include "ChessBoard.hh"
#include <cmath>

namespace Student
{
    KingPiece::KingPiece(ChessBoard& board, Color color, int row, int column)
        : ChessPiece(board, color, row, column)
    {
        this->_type = King;
    }

    Type KingPiece::getType() const {
    return this->_type; 
    }

    KingPiece::~KingPiece()
    {
        
    }

    bool KingPiece::canMoveToLocation(int toRow, int toColumn) const {
    int rowDiff = std::abs(toRow - this->_row);
    int colDiff = std::abs(toColumn - this->_column);
    bool isSingleSquareMove = rowDiff <= 1 && colDiff <= 1;

    // Check for regular king moves
    if (isSingleSquareMove && _board.isWithinBoard(toRow, toColumn)) {
        ChessPiece* destinationPiece = _board.getPiece(toRow, toColumn);
        if (destinationPiece != nullptr && destinationPiece->getColor() == this->_color) {
            return false;
        }
        return true;
    }

    // Preliminary check for castling move
    if (rowDiff == 0 && colDiff == 2) {
        // This is a placeholder for castling; actual validation should be done in the ChessBoard class
        return true;  // Return true here but ensure detailed check in movePiece
    }

    return false;
}

    const char* KingPiece::toString()
    {
         return getColor() == Color::White ? "K" : "k";
    }
}
