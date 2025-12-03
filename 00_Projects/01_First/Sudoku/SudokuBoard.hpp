// =================================================
// SudokuBoard.hpp
// Board representation, validation, and basic I/O
// =================================================

#ifndef SUDOKUBOARD_HPP
#define SUDOKUBOARD_HPP

#include <vector>
#include <string>

class SudokuBoard
{
public:
    // =================================================
    // Constructor & Destructor
    // =================================================
    SudokuBoard();
    ~SudokuBoard();
    
    // =================================================
    // Board Access Methods
    // =================================================
    int getValue(int row, int col) const;
    void setValue(int row, int col, int value);
    void clearValue(int row, int col);
    bool isEmpty(int row, int col) const;
    
    // =================================================
    // Validation Methods
    // =================================================
    bool isValidPlacement(int row, int col, int value) const;
    bool isValidRow(int row, int value) const;
    bool isValidCol(int col, int value) const;
    bool isValidBox(int row, int col, int value) const;
    bool isBoardValid() const;
    bool isSolved() const;
    
    // =================================================
    // Board State Management
    // =================================================
    void clearBoard();
    void copyBoard(const SudokuBoard& other);
    std::vector<std::vector<int>> getBoard() const;
    void setBoard(const std::vector<std::vector<int>>& board);
    
    // =================================================
    // Fixed Cells Management
    // =================================================
    void markAsFixed(int row, int col);
    bool isFixed(int row, int col) const;
    void clearAllFixedMarks();
    
    // =================================================
    // File I/O Methods
    // =================================================
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    
    // =================================================
    // Display Methods
    // =================================================
    std::string toString() const;
    void print() const;

private:
    // =================================================
    // Private Data Members
    // =================================================
    std::vector<std::vector<int>> m_board;        // 9x9 grid (0 = empty, 1-9 = filled)
    std::vector<std::vector<bool>> m_fixedCells;  // Track which cells are fixed
    
    // =================================================
    // Private Helper Methods
    // =================================================
    bool isValidIndex(int row, int col) const;
};

#endif // SUDOKUBOARD_HPP
