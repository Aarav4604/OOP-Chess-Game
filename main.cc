#include <cassert>
#include "ChessBoard.hh"
#include "ChessPiece.hh"
#include <iostream>

using namespace Student;


int main() {
    ChessBoard board(8, 8);  // Create an 8x8 chess board
    //board.displayBoard(); // Assuming you have a method to print board state
    //ChessBoard board(8, 8);

    // Clear the board first to remove any existing pieces

    // Placing the pieces according to the test input
    board.createChessPiece(White, King, 0, 4);  // Black Queen at 0,0
    //board.createChessPiece(Black, Queen, 1, 0);   // White King at 1,1
    board.createChessPiece(White, Rook, 0,7);   // White Pawn at 2,1 (corrected from Knight)
    //board.createChessPiece(White, Pawn, 3, 2);   // White Pawn at 2,1 (corrected from Knight)
    //board.createChessPiece(Black, Pawn, 4, 4);
    board.createChessPiece(Black, Rook, 0, 2);   // Black Rook at 6,1
    //board.createChessPiece(Black, King, 1, 6);   // Black King at 7,0
    //board.createChessPiece(White,King, 6,4);

    // Printing the board to verify placement
    std::cout << board.displayBoard().str() << std::endl;
    if (board.movePiece(0, 4, 0,6)) { // Attempting to move the white pawn from (1,1) to (0,1)
        std::cout << "Pawn moved successfully. Checking for promotion..." << std::endl;
        // Implement the promotion logic here
    } else {
        std::cout << "Move failed or was invalid." << std::endl;
    }

    //board.isValidScan(8,8);
    std::cout << board.displayBoard().str() << std::endl;
    if (board.movePiece(4, 4, 5, 5)) { // Attempting to move the white pawn from (1,1) to (0,1)
        std::cout << "Pawn moved successfully. Checking for promotion..." << std::endl;
        // Implement the promotion logic here
    } else {
        std::cout << "Move failed or was invalid." << std::endl;
    }
    // std::cout << board.displayBoard().str() << std::endl;
    // if (board.movePiece(4, 5, 5, 6)) { // Attempting to move the white pawn from (1,1) to (0,1)
    //     std::cout << "Pawn moved successfully. Checking for promotion..." << std::endl;
    //     // Implement the promotion logic here
    // } else {
    //     std::cout << "Move failed or was invalid." << std::endl;
    // }

    // std::cout << board.displayBoard().str() << std::endl;
    // if (board.movePiece(4, 3, 2, 3)) { // Attempting to move the white pawn from (1,1) to (0,1)
    //     std::cout << "Pawn moved successfully. Checking for promotion..." << std::endl;
    //     // Implement the promotion logic here
    // } else {
    //     std::cout << "Move failed or was invalid." << std::endl;
    // }

    //  if (board.movePiece(1, 6, 2,6)) { // Attempting to move the white pawn from (1,1) to (0,1)
    //     std::cout << "Pawn moved successfully. Checking for promotion..." << std::endl;
    //     // Implement the promotion logic here
    // } else {
    //     std::cout << "Move failed or was invalid." << std::endl;
    // }
    
    // if (board.movePiece(4, 2, 3, 2)) { // Attempting to move the white pawn from (1,1) to (0,1)
    //     std::cout << "Pawn moved successfully. Checking for promotion..." << std::endl;
    //     // Implement the promotion logic here
    // } else {
    //     std::cout << "Move failed or was invalid." << std::endl;
    // }
    // if (board.movePiece(2, 6, 2, 7)) { // Attempting to move the white pawn from (1,1) to (0,1)
    //     std::cout << "Pawn moved successfully. Checking for promotion..." << std::endl;
    //     // Implement the promotion logic here
    // } else {
    //     std::cout << "Move failed or was invalid." << std::endl;
    // }

    // if (board.movePiece(3, 2, 2, 3)) { // Attempting to move the white pawn from (1,1) to (0,1)
    //     std::cout << "Pawn moved successfully. Checking for promotion..." << std::endl;
    //     // Implement the promotion logic here
    // } else {
    //     std::cout << "Move failed or was invalid." << std::endl;
    // }



    // Print the board after the move
    std::cout << "Board State After Move:" << std::endl;
    std::cout << board.displayBoard().str() << std::endl;

    return 0;
}
