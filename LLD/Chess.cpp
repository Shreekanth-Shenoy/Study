#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

using namespace std;

enum class Color { WHITE, BLACK };


class Position {
public:
    int x;
    int y;
    Position(int x = 0, int y = 0): x(x), y(y) {}
    bool isValid() const {
        return x >= 0 && y >= 0 && x < 8 && y < 8;
    }
    bool operator==(const Position & other) const {
        return x == other.x && y == other.y;
    }
};

class Piece {
public:
    Color color;
    Piece(Color color): color(color) {}
    virtual ~Piece() = default;
    virtual bool isMoveValid(const Position& start, const Position& end, const std::vector<std::vector<std::unique_ptr<Piece>>>& board)const = 0;
    virtual char getSymbol() const = 0;
};

class Knight: public Piece {
public:
    Knight(Color color): Piece(color) {}

    bool isMoveValid(const Position& start, const Position& end, const std::vector<std::vector<std::unique_ptr<Piece>>>& board) const override {
        int dx = std::abs(start.x - end.x);
        int dy = std::abs(start.y - end.y);
        return (dx == 1 && dy == 2) || (dx == 2 && dy == 1);
    }

    char getSymbol() const override {
        return color == Color::WHITE ? 'N' : 'n';
    }
};

class Rook: public Piece {
public:
    Rook(Color color): Piece(color) {}

    bool isMoveValid(const Position& start, const Position& end, const std::vector<std::vector<std::unique_ptr<Piece>>>& board) const override {
        // Check if the move is a straight line (either horizontal or vertical)
        bool isHorizontalMove = (start.x == end.x);
        bool isVerticalMove = (start.y == end.y);

        if (!isHorizontalMove && !isVerticalMove) {
            return false; // Rook can only move in a straight line
        }

        // Determine step direction for movement
        int stepX = (end.x > start.x) ? 1 : -1;
        int stepY = (end.y > start.y) ? 1 : -1;

        // Check if the path is clear (for horizontal movement)
        if (isHorizontalMove) {
            for (int y = start.y + stepY; y != end.y; y += stepY) {
                if (board[start.x][y] != nullptr) {
                    return false; // Path is blocked by another piece
                }
            }
        }
        else {
            for (int x = start.x + stepX; x != end.x; x += stepX) {
                if (board[x][start.y] != nullptr) {
                    return false;
                }
            }
        }
        return true;
    }
    char getSymbol() const override {
        return color == Color::WHITE ? 'R' : 'r';
    }
};

class Bishop: public Piece {
public:
    Bishop(Color color): Piece(color) {}

    bool isMoveValid(const Position& start, const Position& end, const std::vector<std::vector<std::unique_ptr<Piece>>>& board)const override {
        int dx = std::abs(start.x - end.x);
        int dy = std::abs(start.y - end.y);

        if (dx != dy) {
            return false;
        }

        // Determine the step direction for movement
        int stepX = (end.x > start.x) ? 1 : -1;
        int stepY = (end.y > start.y) ? 1 : -1;

        // Check if the path is clear
        int currentX = start.x + stepX;
        int currentY = start.y + stepY;

        while (currentX != end.x && currentY != end.y) {
            if (board[currentX][currentY] != nullptr) {
                return false; // Path is blocked by another piece
            }
            currentX += stepX;
            currentY += stepY;
        }
        return true;
    }

    char getSymbol() const override {
        return color == Color::WHITE ? 'B' : 'b';
    }

};

class Queen: public Piece {
public:
    Queen(Color color): Piece(color) {}

    bool isMoveValid(const Position& start, const Position& end, const std::vector<std::vector<std::unique_ptr<Piece>>>& board) const override {
        int dx = std::abs(start.x - end.x);
        int dy = std::abs(start.y - end.y);

        // Check if the move is valid like a rook (horizontal/vertical) or bishop (diagonal)
        bool isHorizontalMove = (start.x == end.x);
        bool isVerticalMove = (start.y == end.y);
        bool isDiagonalMove = (dx == dy);

        if (!isHorizontalMove && !isVerticalMove && !isDiagonalMove) {
            return false; // Queen can only move like a rook or bishop
        }

        // Check for path clearance
        if (isHorizontalMove) {
            int stepY = (end.y > start.y) ? 1 : -1;
            for (int y = start.y + stepY; y != end.y; y += stepY) {
                if (board[start.x][y] != nullptr) {
                    return false; // Path is blocked by another piece
                }
            }
        } else if (isVerticalMove) {
            int stepX = (end.x > start.x) ? 1 : -1;
            for (int x = start.x + stepX; x != end.x; x += stepX) {
                if (board[x][start.y] != nullptr) {
                    return false; // Path is blocked by another piece
                }
            }
        } else if (isDiagonalMove) {
            int stepX = (end.x > start.x) ? 1 : -1;
            int stepY = (end.y > start.y) ? 1 : -1;
            int currentX = start.x + stepX;
            int currentY = start.y + stepY;

            while (currentX != end.x && currentY != end.y) {
                if (board[currentX][currentY] != nullptr) {
                    return false; // Path is blocked by another piece
                }
                currentX += stepX;
                currentY += stepY;
            }
        }

        // The move is valid if all checks pass
        return true;
    }

    char getSymbol() const override {
        return color == Color::WHITE ? 'Q' : 'q';
    }
};

class Pawn : public Piece {
public:
    Pawn(Color color) : Piece(color) {}

    bool isMoveValid(const Position& start, const Position& end, const std::vector<std::vector<std::unique_ptr<Piece>>>& board) const override {
        int direction = (color == Color::WHITE) ? 1 : -1; // White moves up, Black moves down
        int dx = end.x - start.x;
        int dy = std::abs(end.y - start.y);

        // Standard one-square move forward
        if (dy == 0 && dx == direction && board[end.x][end.y] == nullptr) {
            return true;
        }

        // First move can be two squares forward
        if (dy == 0 && dx == 2 * direction && board[start.x + direction][start.y] == nullptr && board[end.x][end.y] == nullptr) {
            if ((color == Color::WHITE && start.x == 1) || (color == Color::BLACK && start.x == 6)) {
                return true;
            }
        }

        // Capture move (diagonal)
        if (dy == 1 && dx == direction && board[end.x][end.y] != nullptr && board[end.x][end.y]->color != color) {
            return true;
        }

        return false;
    }

    char getSymbol() const override {
        return color == Color::WHITE ? 'P' : 'p';
    }
};

class King : public Piece {
public:
    King(Color color) : Piece(color) {}

    bool isMoveValid(const Position& start, const Position& end, const std::vector<std::vector<std::unique_ptr<Piece>>>& board) const override {
        int dx = std::abs(start.x - end.x);
        int dy = std::abs(start.y - end.y);
        // King can move one square in any direction
        return (dx <= 1 && dy <= 1);
    }

    char getSymbol() const override {
        return color == Color::WHITE ? 'K' : 'k';
    }
};


class Board {
public:
    std::vector<std::vector<std::unique_ptr<Piece>>> grid;

    Board() {
        // Resize the outer vector to 8 rows
        grid.resize(8);

        // Resize each row to 8 columns initialized with `nullptr`
        for (auto& row : grid) {
            row.resize(8);
        }

        // Initialize pieces or leave as `nullptr` for empty squares
        initialize();
    }

    void initialize() {

        grid[0][0] = std::make_unique<Rook>(Color::WHITE);
        grid[0][1] = std::make_unique<Knight>(Color::WHITE);
        grid[0][2] = std::make_unique<Bishop>(Color::WHITE);
        grid[0][3] = std::make_unique<Queen>(Color::WHITE);
        grid[0][4] = std::make_unique<King>(Color::WHITE);
        grid[0][5] = std::make_unique<Bishop>(Color::WHITE);
        grid[0][6] = std::make_unique<Knight>(Color::WHITE);
        grid[0][7] = std::make_unique<Rook>(Color::WHITE);

        grid[7][0] = std::make_unique<Rook>(Color::BLACK);
        grid[7][1] = std::make_unique<Knight>(Color::BLACK);
        grid[7][2] = std::make_unique<Bishop>(Color::BLACK);
        grid[7][3] = std::make_unique<Queen>(Color::BLACK);
        grid[7][4] = std::make_unique<King>(Color::BLACK);
        grid[7][5] = std::make_unique<Bishop>(Color::BLACK);
        grid[7][6] = std::make_unique<Knight>(Color::BLACK);
        grid[7][7] = std::make_unique<Rook>(Color::BLACK);

        for (int i = 0; i < 8; ++i) {
            grid[1][i] = std::make_unique<Pawn>(Color::WHITE);
            grid[6][i] = std::make_unique<Pawn>(Color::BLACK);
        }
    }

    void display() const {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (grid[i][j] == nullptr) {
                    std::cout << ". ";
                } else {
                    std::cout << grid[i][j]->getSymbol() << ' ';
                }
            }
            std::cout << std::endl;
        }
    }

    bool isOccupied(const Position& pos) const {
        return grid[pos.x][pos.y] != nullptr;
    }

    Piece* getPiece(const Position& pos) const {
        return grid[pos.x][pos.y].get();
    }

    void movePiece(const Position& start, const Position& end) {
        grid[end.x][end.y] = std::move(grid[start.x][start.y]);
        grid[start.x][start.y] = nullptr;
    }
};



class Game {
    Board board;
    Color currentTurn;
    bool gameEnded;
    int illegalMoveCount; // Counter for consecutive illegal moves


public:
    Game(): currentTurn(Color::WHITE), gameEnded(false), illegalMoveCount(0) {}

    void switchTurn() {
        currentTurn = (currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
        illegalMoveCount = 0; // Reset the counter when the turn switches
    }
    bool isKingInCheck(const Position& kingPos) {
        // Iterate over all opponent pieces and check if any can attack the king's position
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Piece* piece = board.getPiece(Position(i, j));
                if (piece != nullptr && piece->color != currentTurn) {
                    if (piece->isMoveValid(Position(i, j), kingPos, board.grid)) {
                        return true; // King is in check
                    }
                }
            }
        }
        return false; // King is not in check
    }

    bool checkForStalemate() {
        // Ensure the king is not in check first
        Position kingPos;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Piece* piece = board.getPiece(Position(i, j));
                if (piece != nullptr && piece->color == currentTurn && piece->getSymbol() == (currentTurn == Color::WHITE ? 'K' : 'k')) {
                    kingPos = Position(i, j);
                    break;
                }
            }
        }

        if (isKingInCheck(kingPos)) {
            return false; // If the king is in check, it's not a stalemate
        }

        // Check for any valid move for any piece of the current player
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Piece* piece = board.getPiece(Position(i, j));
                if (piece != nullptr && piece->color == currentTurn) {
                    for (int x = 0; x < 8; ++x) {
                        for (int y = 0; y < 8; ++y) {
                            Position newPos(x, y);
                            if (piece->isMoveValid(Position(i, j), newPos, board.grid)) {
                                // Simulate the move
                                Piece* capturedPiece = board.getPiece(newPos);
                                board.movePiece(Position(i, j), newPos);

                                bool moveValid = !isKingInCheck(kingPos);

                                // Undo the move
                                board.movePiece(newPos, Position(i, j));
                                if (capturedPiece) {
                                    board.grid[x][y] = std::unique_ptr<Piece>(capturedPiece);
                                }

                                if (moveValid) {
                                    return false; // Found a valid move, not stalemate
                                }
                            }
                        }
                    }
                }
            }
        }

        // No valid move found, and the king is not in check
        return true;
    }

    bool checkForCheckmate() {
        // Locate the king of the current player
        Position kingPos;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Piece* piece = board.getPiece(Position(i, j));
                if (piece != nullptr && piece->color == currentTurn && piece->getSymbol() == (currentTurn == Color::WHITE ? 'K' : 'k')) {
                    kingPos = Position(i, j);
                    break;
                }
            }
        }

        // Check if the king is currently in check
        if (!isKingInCheck(kingPos)) {
            return false; // The king is not in check, so it's not checkmate
        }

        // Iterate over all pieces of the current player and check if any valid move can get the king out of check
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Piece* piece = board.getPiece(Position(i, j));
                if (piece != nullptr && piece->color == currentTurn) {
                    for (int x = 0; x < 8; ++x) {
                        for (int y = 0; y < 8; ++y) {
                            Position newPos(x, y);
                            if (piece->isMoveValid(Position(i, j), newPos, board.grid)) {
                                // Simulate the move
                                Piece* capturedPiece = board.getPiece(newPos);
                                board.movePiece(Position(i, j), newPos);

                                bool stillInCheck = isKingInCheck(kingPos);

                                // Undo the move
                                board.movePiece(newPos, Position(i, j));
                                if (capturedPiece) {
                                    board.grid[x][y] = std::unique_ptr<Piece>(capturedPiece);
                                }

                                if (!stillInCheck) {
                                    return false; // Found a move that gets out of check, not checkmate
                                }
                            }
                        }
                    }
                }
            }
        }

        // No valid move found to get the king out of check
        return true;
    }


    bool wouldLeaveKingInCheck(const Position& start, const Position& end) {
        // Save the piece that may be captured
        Piece* capturedPiece = board.getPiece(end);

        // Simulate the move
        board.movePiece(start, end);

        // Find the king's position after the move
        Position kingPos;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Piece* piece = board.getPiece(Position(i, j));
                if (piece != nullptr && piece->color == currentTurn && piece->getSymbol() == (currentTurn == Color::WHITE ? 'K' : 'k')) {
                    kingPos = Position(i, j);
                    break;
                }
            }
        }

        // Check if the king is in check
        bool kingInCheck = isKingInCheck(kingPos);

        // Revert the move
        board.movePiece(end, start);
        if (capturedPiece) {
            board.grid[end.x][end.y] = std::unique_ptr<Piece>(capturedPiece);
        } else {
            board.grid[end.x][end.y] = nullptr;
        }

        return kingInCheck;
    }



    void checkIllegalMoves() {
        if (illegalMoveCount >= 5) {
            std::cout << (currentTurn == Color::WHITE ? "Black" : "White") << " wins due to 5 consecutive illegal moves!\n";
            gameEnded = true;
        }
    }

    void start() {
        while (!gameEnded) {
            board.display();
            Position start, end;
            std::cout << "Enter move (start x y end x y): ";
            std::cin >> start.x >> start.y >> end.x >> end.y;

            if (!start.isValid() || !end.isValid()) {
                std::cout << "Invalid position. Try again.\n";
                illegalMoveCount++;
                checkIllegalMoves();
                continue;
            }

            Piece* piece = board.getPiece(start);
            if (piece == nullptr || piece->color != currentTurn) {
                std::cout << "Invalid move. No piece at start or wrong turn.\n";
                illegalMoveCount++;
                checkIllegalMoves();
                continue;
            }

            if (piece->isMoveValid(start, end, board.grid)) {
                if (board.isOccupied(end) && board.getPiece(end)->color == currentTurn) {
                    std::cout << "Cannot capture your own piece. Try again.\n";
                    illegalMoveCount++;
                    checkIllegalMoves();
                    continue;
                }

                if (wouldLeaveKingInCheck(start, end)) {
                    std::cout << "This move would leave your king in check. Try again.\n";
                    illegalMoveCount++;
                    checkIllegalMoves();
                    continue;
                }

                board.movePiece(start, end);
                if (checkForCheckmate()) {
                    std::cout << (currentTurn == Color::WHITE ? "White" : "Black") << " wins by checkmate!\n";
                    gameEnded = true;
                } else if (checkForStalemate()) {
                    std::cout << "The game is a draw by stalemate!\n";
                    gameEnded = true;
                } else {
                    switchTurn();
                }
            } else {
                std::cout << "Invalid move for this piece. Try again.\n";
                illegalMoveCount++;
                checkIllegalMoves();
            }
        }
    }

};

int main()
{
    Game game;
    game.start();
    return 0;
}

//sample input
0 1 2 2  
6 3 4 3  
0 6 2 5  
7 1 5 2  
1 4 3 4  
