/**
 * @file SudokuBoard.hpp
 * @brief Board representation, validation, and basic I/O
 *
 * This header defines the core Sudoku board class that manages the 9x9 grid,
 * validates moves according to Sudoku rules, and handles file I/O operations
 * for saving and loading puzzle states.
 *
 * @author Salah-Eldin Hassen
 * @date December 2025
 * @version 1.0
 * @project Sudoku Game - SW Diploma
 */

#pragma once

#include <array>
#include <string>

// =================================================
// Board configuration
// =================================================

inline constexpr int SUDOKU_SIZE = 9;

using SudokuGrid = std::array<std::array<int, SUDOKU_SIZE>, SUDOKU_SIZE>;
using FixedGrid  = std::array<std::array<bool, SUDOKU_SIZE>, SUDOKU_SIZE>;
using SudokuLine = std::array<int, SUDOKU_SIZE>;
using SudokuBox  = std::array<int, SUDOKU_SIZE>;

class SudokuBoard
{
public:
    // ------------------------------------------------------
    // Constructor & Destructor
    // ------------------------------------------------------
    SudokuBoard();
    ~SudokuBoard();
    
    // ------------------------------------------------------
    // Board Access Methods
    // ------------------------------------------------------
    int getValue(int row, int col) const;
    void setValue(int row, int col, int value);
    void clearValue(int row, int col);
    bool isEmpty(int row, int col) const;
    
    // ------------------------------------------------------
    // Validation Methods
    // ------------------------------------------------------
    bool isValidPlacement(int row, int col, int value) const;
    bool isValidRow(int row, int value) const;
    bool isValidCol(int col, int value) const;
    bool isValidBox(int row, int col, int value) const;
    bool isBoardValid() const;
    bool isSolved() const;
    
    // ------------------------------------------------------
    // Board State Management
    // ------------------------------------------------------
    void clearBoard();
    void copyBoard(const SudokuBoard& other);
    SudokuGrid getBoard() const;
    void setBoard(const SudokuGrid& board);

    // ------------------------------------------------------
    // Row / Column / Box Accessors
    // ------------------------------------------------------
    SudokuLine getRow(int row) const;
    SudokuLine getColumn(int col) const;
    SudokuBox  getBox(int boxRow, int boxCol) const;
    
    // ------------------------------------------------------
    // Fixed Cells Management
    // ------------------------------------------------------
    void markAsFixed(int row, int col);
    bool isFixed(int row, int col) const;
    void clearAllFixedMarks();
    
    // ------------------------------------------------------
    // File I/O Methods
    // ------------------------------------------------------
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    
    // ------------------------------------------------------
    // Display Methods
    // ------------------------------------------------------
    std::string toString() const;
    void print() const;

private:
    // ------------------------------------------------------
    // Private Data Members
    // ------------------------------------------------------
    SudokuGrid m_board;   // 9x9 grid (0 = empty, 1-9 = filled)
    FixedGrid  m_fixedCells;  // Track which cells are fixed
    
    // ------------------------------------------------------
    // Private Helper Methods
    // ------------------------------------------------------
    bool isValidIndex(int row, int col) const;
};
