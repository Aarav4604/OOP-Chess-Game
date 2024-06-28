#include "KnightPiece.hh"
#include "ChessBoard.hh"

namespace Student {

    KnightPiece::KnightPiece(ChessBoard& board, Color color, int row, int column)
        : ChessPiece(board, color, row, column) {
            this->_type = Knight;
        }

    KnightPiece::~KnightPiece() {}

    Type KnightPiece::getType() const {
    return this->_type;
    }

    bool KnightPiece::canMoveToLocation(int toRow, int toColumn) const {
        int dx = abs(getColumn() - toColumn);
        int dy = abs(getRow() - toRow);
        return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
    }

    const char* KnightPiece::toString() {
        return (_color == White) ? "N" : "n";
    }

}