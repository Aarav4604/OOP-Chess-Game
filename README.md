# OOP-Chess-Game

Welcome to my OOP Chess Game repository! This project is a simplified version of chess implemented in C++. The goal is to practice object-oriented programming concepts such as inheritance, polymorphism, and abstract classes.

Project Overview

In this project, I developed a comprehensive chess game that includes all standard chess pieces and moves. The game supports a flexible board size and incorporates advanced features such as castling, en passant, and pawn promotion.

Key Features:
- All standard chess pieces: Pawn ♟, Rook ♜, Bishop ♝, Knight ♞, Queen ♛, and King ♚.
- Flexible board size: Not limited to the traditional 8x8 grid.
- Advanced chess rules: Includes castling, en passant, and pawn promotion.
- Scoring system: Evaluates board states and computes scores based on the pieces and possible moves.

**Classes and Methods**

**ChessBoard**
- Description: Defines the chessboard, handles piece positions and move execution, and implements scoring functions to evaluate board states.
- Key Methods:
  - movePiece(int fromRow, int fromCol, int toRow, int toCol): Moves a piece from one position to another if the move is valid.
isPieceUnderThreat(int row, int col): Checks if a piece at the given position is under threat from any opponent piece.
  - scoreBoard(): Computes the score from the perspective of the current player.
  - getHighestNextScore(): Evaluates all possible moves and returns the highest score achievable after a single move.

**ChessPiece (Abstract Class)**
- Description: Base class for all chess pieces, defining common methods and variables.
- Key Methods:
  - isValidMove(int fromRow, int fromCol, int toRow, int toCol): Checks if a proposed move is valid for the piece.

**PawnPiece ♟**
- Description: Moves forward and captures diagonally, can move two spaces from its starting position.
- Key Methods:
  - isValidMove(int fromRow, int fromCol, int toRow, int toCol): Specific validation for pawn moves, including diagonal captures.
    
**RookPiece ♜**
- Description: Moves horizontally or vertically any number of squares.
- Key Methods:
  - isValidMove(int fromRow, int fromCol, int toRow, int toCol): Specific validation for rook moves.
    
**BishopPiece ♝**
- Description: Moves diagonally any number of squares.
- Key Methods:
  - isValidMove(int fromRow, int fromCol, int toRow, int toCol): Specific validation for bishop moves.

**KnightPiece ♞**
- Description: Moves in an L-shape: two squares in one direction and then one square perpendicular.
- Key Methods:
  - isValidMove(int fromRow, int fromCol, int toRow, int toCol): Specific validation for knight moves.

**QueenPiece ♛**
- Description: Moves horizontally, vertically, or diagonally any number of squares.
- Key Methods:
  - isValidMove(int fromRow, int fromCol, int toRow, int toCol): Specific validation for queen moves.

**KingPiece ♚**
- Description: Moves one square in any direction, ensures the King is not left in a state of check.
- Key Methods:
  - isValidMove(int fromRow, int fromCol, int toRow, int toCol): Specific validation for king moves, including castling.

**Additional Features**

En Passant
- Allows a pawn to capture an opponent's pawn that has moved two squares from its starting position and bypassed the capturing pawn's adjacent square.

Pawn Promotion
- Promotes a pawn to a queen when it reaches the opponent's back rank.

Castling
- Allows the king to move two squares towards a rook, and the rook moves to the space the king skipped over, provided certain conditions are met.

Scoring System
- Adds points for each piece on the board and evaluates the total score considering possible legal moves for both players.


Build and Run
- Use the provided Makefile.
make custom_tests to compile using main.cc and run custom tests.
