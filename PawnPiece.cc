#include "PawnPiece.hh"
#include "ChessBoard.hh"
#include "iostream"

namespace Student {

    PawnPiece::PawnPiece(ChessBoard& board, Color color, int row, int column)
        : ChessPiece(board, color, row, column), is_first_move(true), is_first_move_second(true), is_en_passant_attack(false) {
        this->_type = Pawn;
    }

PawnPiece::~PawnPiece() {}

Type PawnPiece::getType() const {
    return this->_type;
}

bool PawnPiece::canMoveToLocation(int toRow, int toColumn) const {
    int direction = (getColor() == Color::White) ? -1 : 1; 
    int startRow = getRow();
    int startColumn = getColumn();
    int numRows = _board.getNumRows();

    // Check bounds for toRow and toColumn
    // if (toRow < 0 || toRow >= numRows || toColumn < 0 || toColumn >= _board.getNumCols()) {
    //     return false;
    // }

    // Normal forward move
    if (toColumn == startColumn && toRow == startRow + direction && _board.isEmpty(toRow, toColumn)) {
        return true;
    }

    // Initial two-square forward move
    if (is_first_move && toColumn == startColumn && toRow == startRow + 2 * direction &&
        (startRow == (getColor() == Color::White ? numRows - 2 : 1)) &&
        _board.isEmpty(startRow + direction, startColumn) && _board.isEmpty(toRow, toColumn)) {
        _board.lastMoveWasDoublePawnMove = false;  // Set flag for potential en passant
        return true;
    }

    // Diagonal capture
    if (abs(toColumn - startColumn) == 1 && toRow == startRow + direction) {
        if (_board.isEnemyPiece(toRow, toColumn, getColor())) {
            return true;
        }
    }

    // En passant capture
    if (!_board.lastMoveWasDoublePawnMove &&
        abs(toColumn - startColumn) == 1 && toRow == startRow + direction &&
        _board.isEnemyPiece(startRow, toColumn, getColor())) { 
        is_en_passant_attack = true;
        return true;
    }

    return false;
}


// bool PawnPiece::canExecuteEnPassant(int toRow, int toColumn) const {
//         if (!is_en_passant_attack) {
//             return false;
//         }

//         int direction = (getColor() == Color::White) ? -1 : 1;
//         if(is_first_move && _board.isEmpty(toRow,toColumn) && abs(toColumn - ))

//         return (abs(toColumn - getColumn()) == 1 && toRow == getRow() + direction && _board.isEmpty(toRow, toColumn));
//     }

bool PawnPiece::isEnPassantAttack() const {
        return is_en_passant_attack;
    }

void PawnPiece::setIsEnPassantAttack(bool value) {
    is_en_passant_attack = value;
}

void PawnPiece::setFirstMoveFalse() {
    is_first_move = false;
}

const char* PawnPiece::toString() {
    return getColor() == Color::White ? "♙" : "♟︎";
}

}