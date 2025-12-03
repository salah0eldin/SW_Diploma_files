// =================================================
// SudokuBoard.cpp
// Implementation of Sudoku board operations
// =================================================

#include "SudokuBoard.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

// =================================================
// Constructor & Destructor
// =================================================

SudokuBoard::SudokuBoard()
    : m_board(9, std::vector<int>(9, 0))
    , m_fixedCells(9, std::vector<bool>(9, false))
{
}

SudokuBoard::~SudokuBoard()
{
}

// =================================================
// Board Access Methods
// =================================================

int SudokuBoard::getValue(int row, int col) const
{
    if (!isValidIndex(row, col)) {
        return -1;
    }
    return m_board[row][col];
}

void SudokuBoard::setValue(int row, int col, int value)
{
    // ------------------------------------------------------
    // Validate indices and value range
    // ------------------------------------------------------
    if (!isValidIndex(row, col)) {
        return;
    }
    
    if (value < 0 || value > 9) {
        return;
    }
    
    // ------------------------------------------------------
    // Don't allow modifying fixed cells
    // ------------------------------------------------------
    if (m_fixedCells[row][col]) {
        return;
    }
    
    m_board[row][col] = value;
}

void SudokuBoard::clearValue(int row, int col)
{
    if (!isValidIndex(row, col) || m_fixedCells[row][col]) {
        return;
    }
    m_board[row][col] = 0;
}

bool SudokuBoard::isEmpty(int row, int col) const
{
    if (!isValidIndex(row, col)) {
        return false;
    }
    return m_board[row][col] == 0;
}

// =================================================
// Validation Methods
// =================================================

bool SudokuBoard::isValidPlacement(int row, int col, int value) const
{
    // ------------------------------------------------------
    // Check if placing value at (row, col) violates rules
    // ------------------------------------------------------
    if (!isValidIndex(row, col) || value < 1 || value > 9) {
        return false;
    }
    
    // ------------------------------------------------------
    // Temporarily store current value
    // ------------------------------------------------------
    int currentValue = m_board[row][col];
    
    // ------------------------------------------------------
    // Check row, column, and 3x3 box constraints
    // ------------------------------------------------------
    for (int i = 0; i < 9; ++i) {
        // Check row
        if (i != col && m_board[row][i] == value) {
            return false;
        }
        
        // Check column
        if (i != row && m_board[i][col] == value) {
            return false;
        }
    }
    
    // ------------------------------------------------------
    // Check 3x3 box
    // ------------------------------------------------------
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;
    
    for (int r = boxRow; r < boxRow + 3; ++r) {
        for (int c = boxCol; c < boxCol + 3; ++c) {
            if ((r != row || c != col) && m_board[r][c] == value) {
                return false;
            }
        }
    }
    
    return true;
}

bool SudokuBoard::isValidRow(int row, int value) const
{
    if (row < 0 || row >= 9 || value < 1 || value > 9) {
        return false;
    }
    
    for (int col = 0; col < 9; ++col) {
        if (m_board[row][col] == value) {
            return false;
        }
    }
    return true;
}

bool SudokuBoard::isValidCol(int col, int value) const
{
    if (col < 0 || col >= 9 || value < 1 || value > 9) {
        return false;
    }
    
    for (int row = 0; row < 9; ++row) {
        if (m_board[row][col] == value) {
            return false;
        }
    }
    return true;
}

bool SudokuBoard::isValidBox(int row, int col, int value) const
{
    if (!isValidIndex(row, col) || value < 1 || value > 9) {
        return false;
    }
    
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;
    
    for (int r = boxRow; r < boxRow + 3; ++r) {
        for (int c = boxCol; c < boxCol + 3; ++c) {
            if (m_board[r][c] == value) {
                return false;
            }
        }
    }
    return true;
}

bool SudokuBoard::isBoardValid() const
{
    // ------------------------------------------------------
    // Check if current board state is valid (no conflicts)
    // ------------------------------------------------------
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int value = m_board[row][col];
            
            if (value != 0) {
                // Temporarily clear cell to check if value is valid
                const_cast<SudokuBoard*>(this)->m_board[row][col] = 0;
                bool valid = isValidPlacement(row, col, value);
                const_cast<SudokuBoard*>(this)->m_board[row][col] = value;
                
                if (!valid) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool SudokuBoard::isSolved() const
{
    // ------------------------------------------------------
    // Check if board is completely filled and valid
    // ------------------------------------------------------
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (m_board[row][col] == 0) {
                return false;
            }
        }
    }
    
    return isBoardValid();
}

// =================================================
// Board State Management
// =================================================

void SudokuBoard::clearBoard()
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (!m_fixedCells[row][col]) {
                m_board[row][col] = 0;
            }
        }
    }
}

void SudokuBoard::copyBoard(const SudokuBoard& other)
{
    m_board = other.m_board;
    m_fixedCells = other.m_fixedCells;
}

std::vector<std::vector<int>> SudokuBoard::getBoard() const
{
    return m_board;
}

void SudokuBoard::setBoard(const std::vector<std::vector<int>>& board)
{
    if (board.size() == 9 && board[0].size() == 9) {
        m_board = board;
    }
}

// =================================================
// Fixed Cells Management
// =================================================

void SudokuBoard::markAsFixed(int row, int col)
{
    if (isValidIndex(row, col)) {
        m_fixedCells[row][col] = true;
    }
}

bool SudokuBoard::isFixed(int row, int col) const
{
    if (!isValidIndex(row, col)) {
        return false;
    }
    return m_fixedCells[row][col];
}

void SudokuBoard::clearAllFixedMarks()
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            m_fixedCells[row][col] = false;
        }
    }
}

// =================================================
// File I/O Methods
// =================================================

bool SudokuBoard::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    // ------------------------------------------------------
    // Read 9x9 grid from file
    // ------------------------------------------------------
    clearAllFixedMarks();
    
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int value;
            if (!(file >> value)) {
                return false;
            }
            
            m_board[row][col] = value;
            
            // Mark non-zero cells as fixed
            if (value != 0) {
                m_fixedCells[row][col] = true;
            }
        }
    }
    
    file.close();
    return true;
}

bool SudokuBoard::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    // ------------------------------------------------------
    // Write 9x9 grid to file
    // ------------------------------------------------------
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            file << m_board[row][col];
            if (col < 8) {
                file << " ";
            }
        }
        file << "\n";
    }
    
    file.close();
    return true;
}

// =================================================
// Display Methods
// =================================================

std::string SudokuBoard::toString() const
{
    std::ostringstream oss;
    
    oss << "-------------------------------------\n";
    
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (m_board[row][col] == 0) {
                oss << ". ";
            } else {
                oss << m_board[row][col] << " ";
            }
            
            // Add vertical separators for 3x3 boxes
            if ((col + 1) % 3 == 0 && col < 8) {
                oss << "| ";
            }
        }
        oss << "\n";
        
        // Add horizontal separators for 3x3 boxes
        if ((row + 1) % 3 == 0 && row < 8) {
            oss << "-------------------------------------\n";
        }
    }
    
    oss << "-------------------------------------\n";
    
    return oss.str();
}

void SudokuBoard::print() const
{
    std::cout << toString();
}

// =================================================
// Private Helper Methods
// =================================================

bool SudokuBoard::isValidIndex(int row, int col) const
{
    return row >= 0 && row < 9 && col >= 0 && col < 9;
}
