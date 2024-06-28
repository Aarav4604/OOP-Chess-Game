#include "QueenPiece.hh"
#include "ChessBoard.hh"

namespace Student {

    QueenPiece::QueenPiece(ChessBoard& board, Color color, int row, int column)
        : ChessPiece(board, color, row, column) {
            this->_type = Queen;
        }

    QueenPiece::~QueenPiece() {}

    Type QueenPiece::getType() const {
    return this->_type;
    }

    bool QueenPiece::canMoveToLocation(int toRow, int toColumn) const {
    if (getRow() == toRow) {
        // Check if path is clear horizontally
        int minCol = std::min(getColumn(), toColumn) + 1;
        int maxCol = std::max(getColumn(), toColumn);
        for (int col = minCol; col < maxCol; col++) {
            if (!_board.isEmpty(getRow(), col)) return false;
        }
        return true;
    } else if (getColumn() == toColumn) {
        // Check if path is clear vertically
        int minRow = std::min(getRow(), toRow) + 1;
        int maxRow = std::max(getRow(), toRow);
        for (int row = minRow; row < maxRow; row++) {
            if (!_board.isEmpty(row, getColumn())) return false;
        }
        return true;
    } else if (abs(getRow() - toRow) == abs(getColumn() - toColumn)) {
        // Check if path is clear diagonally
        int rowStep = (toRow - getRow()) / abs(toRow - getRow());
        int colStep = (toColumn - getColumn()) / abs(toColumn - getColumn());
        int steps = abs(toRow - getRow());
        for (int i = 1; i < steps; i++) {
            if (!_board.isEmpty(getRow() + i * rowStep, getColumn() + i * colStep)) return false;
        }
        return true;
    }
    return false;
}


    const char* QueenPiece::toString() {
        return (_color == White) ? "Q" : "q";
    }

} 
