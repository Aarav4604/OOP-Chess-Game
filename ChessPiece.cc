#include "ChessPiece.hh"
#include "ChessBoard.hh" 

namespace Student {

    ChessPiece::ChessPiece(ChessBoard &board, Color color, int row, int column)
        : _board(board), _color(color), _row(row), _column(column) {}

    Color ChessPiece::getColor() const{
        return _color;
    }

    int ChessPiece::getRow()const {
        return _row;
    }

    int ChessPiece::getColumn()const {
        return _column;
    }

    void ChessPiece::setPosition(int row, int column) {
       _row = row;
       _column = column;
    }
    


}
