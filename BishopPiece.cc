#include "BishopPiece.hh"
#include "ChessBoard.hh"

namespace Student {
    BishopPiece::BishopPiece(ChessBoard& board, Color color, int row, int column)
        : ChessPiece(board, color, row, column) {
            this->_type = Bishop;
        }

     BishopPiece::~BishopPiece() {}

     Type BishopPiece::getType() const {
        return this->_type;
        }

 bool BishopPiece::canMoveToLocation(int toRow, int toColumn) const {
    if (abs(toRow - getRow()) == abs(toColumn - getColumn())) {
        int rowOffset = (toRow > getRow()) ? 1 : -1;
        int colOffset = (toColumn > getColumn()) ? 1 : -1;
        
        int checkRow = getRow() + rowOffset, checkCol = getColumn() + colOffset;
        while (checkRow != toRow && checkCol != toColumn) {
            if (_board.getPiece(checkRow, checkCol) != nullptr) {
                return false; // Path is blocked
            }
            checkRow += rowOffset;
            checkCol += colOffset;
        }
        return true; 
    }
    return false; 
}


    const char* BishopPiece::toString() {
        return getColor() == Color::White ? "B" : "b";
    }
}
