#include "RookPiece.hh"
#include "ChessBoard.hh"


namespace Student {

    RookPiece::RookPiece(ChessBoard& board, Color color, int row, int column)
        : ChessPiece(board, color, row, column) {
            this->_type = Rook;
        }

    RookPiece::~RookPiece() {}

    Type RookPiece::getType() const {
    return this->_type;
}


    bool RookPiece::canMoveToLocation(int toRow, int toColumn) const {
    if (toRow == getRow()) {
        int colOffset = (toColumn > getColumn()) ? 1 : -1;
        for (int checkCol = getColumn() + colOffset; checkCol != toColumn; checkCol += colOffset) {
            if (_board.getPiece(toRow, checkCol) != nullptr) {
                return false; 
            }
        }
    } else if (toColumn == getColumn()) {
        int rowOffset = (toRow > getRow()) ? 1 : -1;
        for (int checkRow = getRow() + rowOffset; checkRow != toRow; checkRow += rowOffset) {
            if (_board.getPiece(checkRow, toColumn) != nullptr) {
                return false;
            }
        }
    } else {
        return false; 
    }

    return true;
}

    const char* RookPiece::toString() {
        return (_color == White) ? "R" : "r";
    }

}
