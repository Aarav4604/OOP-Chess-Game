#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"
#include "KnightPiece.hh"
#include "QueenPiece.hh"
#include <limits>
#include <iostream>

using Student::ChessBoard;

ChessBoard::ChessBoard(int numRow, int numCol) : numRows(numRow), numCols(numCol), turn(White) 
{
    board.resize(numRows, std::vector<ChessPiece*>(numCols, nullptr));
    lastMoveWasDoublePawnMove = true;
    hasKingMoved = false;
    hasRookMoved[0] = false; 
    hasRookMoved[1] = false;
}

void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn) {
    if (startRow < 0 || startRow >= numRows || startColumn < 0 || startColumn >= numCols) {
        return;
    }

    if (board[startRow][startColumn] != nullptr) {
        delete board[startRow][startColumn];
        board[startRow][startColumn] = nullptr; 
    }

    switch (ty) {
        case Pawn:
            board[startRow][startColumn] = new PawnPiece(*this, col, startRow, startColumn);
            break;
        case Rook:
            board[startRow][startColumn] = new RookPiece(*this, col, startRow, startColumn);
            break;
        case Bishop:
            board[startRow][startColumn] = new BishopPiece(*this, col, startRow, startColumn);
            break;    
        case King:
            board[startRow][startColumn] = new KingPiece(*this, col, startRow, startColumn);
            break; 
        case Knight:
            board[startRow][startColumn] = new KnightPiece(*this, col, startRow, startColumn);
            break;  
        case Queen:
            board[startRow][startColumn] = new QueenPiece(*this, col, startRow, startColumn);
            break;           

        default:
  
            break;
    }
}
bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn) {
    if (!isWithinBoard(fromRow, fromColumn) || !isWithinBoard(toRow, toColumn)) {
        std::cout << "Move out of board bounds.\n";
        return false;
    }

    ChessPiece* origPiece = board[fromRow][fromColumn];
    if (origPiece == nullptr) {
        std::cout << "No piece at the original location.\n";
        return false;
    }

    if (origPiece->getColor() != turn) {
        std::cout << "It's not the turn of the piece.\n";
        return false;
    }
    if (origPiece->getType() == King && abs(fromColumn - toColumn) == 2 && fromRow == toRow) {
        // Detailed castling checks
        if (!executeCastling(fromRow, fromColumn, toRow, toColumn)) {
            std::cout << "Castling move failed.\n";
            return false;
        }
        updateTurn();
        return true;
    }

    if (!origPiece->canMoveToLocation(toRow, toColumn)) {
        std::cout << "Move not valid according to the piece's moving capabilities.\n";
        return false;
    }

    // Handle captures
    ChessPiece* destPiece = board[toRow][toColumn];
    if (destPiece && destPiece->getColor() == origPiece->getColor()) {
        std::cout << "Destination occupied by a friendly piece.\n";
        return false;
    }

    // Execute move
    board[fromRow][fromColumn] = nullptr;
    board[toRow][toColumn] = origPiece;
    origPiece->setPosition(toRow, toColumn);

    if (destPiece) {
        std::cout << "Capturing enemy piece.\n";
        delete destPiece;  // Capture the piece
    }

    // En Passant capture move
    if (origPiece->getType() == Pawn && static_cast<PawnPiece*>(origPiece)->isEnPassantAttack()) {
        int captureRow = (origPiece->getColor() == Color::White) ? toRow + 1 : toRow - 1;
        delete board[captureRow][toColumn];
        board[captureRow][toColumn] = nullptr;
    }


    // Pawn Promotion
    if (origPiece->getType() == Pawn && (toRow == 0 || toRow == numRows - 1)) {
        ChessPiece* newQueen = new QueenPiece(*this, origPiece->getColor(), toRow, toColumn);
        delete origPiece; // Delete the pawn
        board[toRow][toColumn] = newQueen;
        std::cout << "Pawn promoted to Queen.\n";
    }
    

    updateTurn();  // Move to next player's turn
    return true;
}



void ChessBoard::updateTurn() {
    
    turn = (turn == White) ? Black : White;
}


bool ChessBoard::executeCastling(int fromRow, int fromColumn, int toRow, int toColumn) {
    if (fromRow != toRow || abs(fromColumn - toColumn) != 2) return false;

    int direction = (toColumn > fromColumn) ? 1 : -1;
    int rookFromCol = (direction == 1) ? 7 : 0;
    int rookToCol = (direction == 1) ? 5 : 3;

    if (hasKingMoved || hasRookMoved[rookFromCol == 7 ? 1 : 0]) return false;
    if (isPieceUnderThreat(fromRow, fromColumn)) return false;

    int startCol = std::min(fromColumn, toColumn) + 1;
    int endCol = std::max(fromColumn, toColumn) - 1;
    for (int col = startCol; col <= endCol; ++col) {
        if (getPiece(fromRow, col) != nullptr) return false;
    }

    int checkCol = fromColumn;
    while (checkCol != toColumn + direction) {
        if (isPieceUnderThreat(fromRow, checkCol)) return false;
        checkCol += direction;
    }

    ChessPiece* rook = getPiece(fromRow, rookFromCol);
    if (rook == nullptr || rook->getType() != Rook) return false;

    // Update board state after all checks are passed
    board[fromRow][rookToCol] = rook;
    board[fromRow][rookFromCol] = nullptr;
    rook->setPosition(fromRow, rookToCol);

    ChessPiece* king = board[fromRow][fromColumn];
    board[toRow][toColumn] = king;
    board[fromRow][fromColumn] = nullptr;
    king->setPosition(toRow, toColumn);

    hasKingMoved = true;
    hasRookMoved[rookFromCol == 7 ? 1 : 0] = true;

    return true;
}




bool ChessBoard::isKingCaptured(Color kingColor) {
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            ChessPiece* piece = getPiece(row, col);
            if (piece && piece->getColor() == kingColor && piece->getType() == King) {
                return false; 
            }
        }
    }
    return true; 
}

bool ChessBoard::isPathClear(int fromRow, int fromColumn, int toRow, int toColumn) const {
    if (fromRow == toRow && fromColumn == toColumn) {
        // No movement, path is trivially clear
        return true;
    }

    int rowDiff = toRow - fromRow;
    int colDiff = toColumn - fromColumn;

    int rowStep = (rowDiff == 0) ? 0 : rowDiff / std::abs(rowDiff);
    int colStep = (colDiff == 0) ? 0 : colDiff / std::abs(colDiff);

    int curRow = fromRow + rowStep;
    int curCol = fromColumn + colStep;

    while (curRow != toRow || curCol != toColumn) {
        if (board[curRow][curCol] != nullptr) {
            return false;
        }
        curRow += rowStep;
        curCol += colStep;
    }

    return true;
}



bool ChessBoard::isWithinBoard(int row, int column) {
    return row >= 0 && row < numRows && column >= 0 && column < numCols;
}

bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn) {
    if (fromRow < 0 || fromRow >= numRows || fromColumn < 0 || fromColumn >= numCols ||
        toRow < 0 || toRow >= numRows || toColumn < 0 || toColumn >= numCols) {
        return false;
    }

    if (fromRow == toRow && fromColumn == toColumn) {
        return false;
    }

    ChessPiece* movingPiece = getPiece(fromRow, fromColumn);

    if (movingPiece == nullptr) {
        return false; 
    }

    ChessPiece* destinationPiece = getPiece(toRow, toColumn);

    if (destinationPiece && destinationPiece->getColor() == movingPiece->getColor()) {
        return false;
    }

    if (!movingPiece->canMoveToLocation(toRow, toColumn)) {
        return false;
    }

    if (isInCheckAfterMove(fromRow, fromColumn, toRow, toColumn, movingPiece->getColor())) {
        return false; 
    }

    if (movingPiece->getType() == King && !hasKingMoved && 
        std::abs(fromColumn - toColumn) == 2 && fromRow == toRow) {
        int direction = (toColumn - fromColumn > 0) ? 1 : -1;
        int rookColumn = (direction == 1) ? numCols - 1 : 0;
        int pathClearUntil = (direction == 1) ? toColumn - 1 : toColumn + 1;
        bool isRookSide = (direction == 1);

        return !isKingInCheck(movingPiece->getColor()) && // King is not in check
               !hasRookMoved[isRookSide] && // The rook hasn't moved
               isPathClear(fromRow, fromColumn, fromRow, rookColumn) && // Path is clear
               !isPieceUnderThreat(fromRow, pathClearUntil); // The square king skips is not under threat
    }

    return true;
}


bool ChessBoard::isPieceUnderThreat(int row, int column) {
    if (!isWithinBoard(row, column)) return false;

    ChessPiece* targetPiece = board[row][column];
    if (!targetPiece) return false; 

    Color opponentColor = (targetPiece->getColor() == White) ? Black : White;

    // PAWN
    int pawnRowDirection = (opponentColor == White) ? 1 : -1;
    std::vector<std::pair<int, int>> pawnAttacks = {
        {row + pawnRowDirection, column - 1}, 
        {row + pawnRowDirection, column + 1}
    };
    for (const auto& pos : pawnAttacks) {
        if (isWithinBoard(pos.first, pos.second)) {
            ChessPiece* piece = board[pos.first][pos.second];
            if (piece && piece->getType() == Pawn && piece->getColor() == opponentColor) {
                return true;
            }
        }
    }

    // Direction vectors for rooks and bishops
    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}, // Rook 
        {1, 1}, {-1, -1}, {1, -1}, {-1, 1} // Bishop 
    };

    for (const auto& dir : directions) {
        for (int x = row + dir.first, y = column + dir.second; 
             isWithinBoard(x, y); 
             x += dir.first, y += dir.second) {
            ChessPiece* piece = board[x][y];
            if (piece) {
                if (piece->getColor() == opponentColor && 
                   ((abs(dir.first) != abs(dir.second) && piece->getType() == Rook) || 
                    (abs(dir.first) == abs(dir.second) && piece->getType() == Bishop))) {
                    return true;
                }
                break; 
            }
        }
    }

    // KING
    std::vector<std::pair<int, int>> kingMoves = {
        {-1, -1}, {-1, 0}, {-1, 1}, 
        {0, -1},           {0, 1}, 
        {1, -1},  {1, 0},  {1, 1}
    };
    for (const auto& move : kingMoves) {
        int kx = row + move.first, ky = column + move.second;
        if (isWithinBoard(kx, ky)) {
            ChessPiece* piece = board[kx][ky];
            if (piece && piece->getType() == King && piece->getColor() == opponentColor) {
                return true;
            }
        }
    }

    //QUEEN
    for (const auto& dir : directions) {
        for (int x = row + dir.first, y = column + dir.second; 
             isWithinBoard(x, y); 
             x += dir.first, y += dir.second) {
            ChessPiece* piece = board[x][y];
            if (piece) {
                if (piece->getColor() == opponentColor && piece->getType() == Queen) {
                    return true;
                }
                break; 
            }
        }
    }

    // KNIGHT
    std::vector<std::pair<int, int>> knightMoves = {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };
    for (const auto& move : knightMoves) {
        int nx = row + move.first, ny = column + move.second;
        if (isWithinBoard(nx, ny)) {
            ChessPiece* piece = board[nx][ny];
            if (piece && piece->getType() == Knight && piece->getColor() == opponentColor) {
                return true;
            }
        }
    }

    return false; 
}


bool ChessBoard::isInCheckAfterMove(int fromRow, int fromCol, int toRow, int toColumn, Color playerColor) {
    ChessPiece* movedPiece = getPiece(fromRow, fromCol); 
    ChessPiece* targetPiece = getPiece(toRow, toColumn); 

    board[toRow][toColumn] = movedPiece;
    board[fromRow][fromCol] = nullptr;
    if (movedPiece) movedPiece->setPosition(toRow, toColumn);

    bool kingInCheck = isKingInCheck(playerColor);


    board[fromRow][fromCol] = movedPiece;
    board[toRow][toColumn] = targetPiece;
    if (movedPiece) movedPiece->setPosition(fromRow, fromCol);

    return kingInCheck;
}
bool ChessBoard::isKingInCheck(Color kingColor) {
    int kingRow, kingCol;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            ChessPiece* piece = getPiece(row, col);
            if (piece && piece->getColor() == kingColor && piece->getType() == Type::King) {
                kingRow = row;
                kingCol = col;
                goto FOUND_KING; 
            }
        }
    }

FOUND_KING:

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            ChessPiece* piece = getPiece(row, col);
            if (piece && piece->getColor() != kingColor && piece->canMoveToLocation(kingRow, kingCol)) {
                return true; 
            }
        }
    }
    return false; 
}


std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    // top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << i;
    }
    outputString << std::endl
                 << "  ";
    // top border
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl;

    for (int row = 0; row < numRows; row++)
    {
        outputString << row << "|";
        for (int column = 0; column < numCols; column++)
        {
            ChessPiece *piece = board.at(row).at(column);
            outputString << (piece == nullptr ? " " : piece->toString());
        }
        outputString << "|" << std::endl;
    }

    // bottom border
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl
                 << std::endl;

    return outputString;
}

void ChessBoard::isValidScan(int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            for(int k = 0; k < n; k++){
                for(int x = 0; x < m; x++){
                    isValidMove(i,j,k,x);
                }
            }
        }
    }
}
ChessBoard::~ChessBoard() {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (board[i][j] != nullptr) {
                delete board[i][j]; 
                board[i][j] = nullptr; 
            }
        }
    }
}

float ChessBoard::scoreBoard() {
    float myScore = 0.0f;
    float opponentScore = 0.0f;

    // Iterate over the board to calculate the score based on piece values and legal moves
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            ChessPiece* piece = board[row][col];
            if (piece) {
                float pieceValue = 0.0f;
                int mobility = 0;

                // Assign piece values
                switch (piece->getType()) {
                    case King: pieceValue = 200.0f; break;
                    case Queen: pieceValue = 9.0f; break;
                    case Rook: pieceValue = 5.0f; break;
                    case Bishop:
                    case Knight: pieceValue = 3.0f; break;
                    case Pawn: pieceValue = 1.0f; break;
                }

                // Count mobility: total possible legal moves
                for (int toRow = 0; toRow < numRows; ++toRow) {
                    for (int toCol = 0; toCol < numCols; ++toCol) {
                        if (isValidMove(row, col, toRow, toCol)) mobility++;
                    }
                }

                // Adjust scores based on the current player's turn
                if (piece->getColor() == turn) {
                    myScore += pieceValue + 0.1f * mobility;
                } else {
                    opponentScore += pieceValue + 0.1f * mobility;
                }
            }
        }
    }

    // Net score from the perspective of the current player
    return myScore - opponentScore;
}


float ChessBoard::getHighestNextScore() {
    float highestScore = -std::numeric_limits<float>::max();

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            ChessPiece* piece = board[row][col];
            if (piece && piece->getColor() == turn) {
                // Consider all board locations for a potential move
                for (int toRow = 0; toRow < numRows; ++toRow) {
                    for (int toCol = 0; toCol < numCols; ++toCol) {
                        if (isValidMove(row, col, toRow, toCol)) {
                            // Save original state
                            ChessPiece* origDestPiece = board[toRow][toCol];

                            // Simulate the move
                            board[toRow][toCol] = piece;
                            board[row][col] = nullptr;
                            piece->setPosition(toRow, toCol);

                            // Calculate the new board score
                            float currentScore = scoreBoard();

                            // Undo the move
                            board[row][col] = piece;
                            board[toRow][toCol] = origDestPiece;
                            piece->setPosition(row, col);

                            // Update the highest score
                            if (currentScore > highestScore) {
                                highestScore = currentScore;
                            }
                        }
                    }
                }
            }
        }
    }
    return highestScore;
}


bool ChessBoard::isEmpty(int row, int col) const {
        return getPiece(row, col) == nullptr;
    }
bool ChessBoard::isEnemyPiece(int row, int col, Color color) const {
        ChessPiece* piece = getPiece(row, col);
        if (piece != nullptr && piece->getColor() != color) {
            return true;
        }
        return false;
    }