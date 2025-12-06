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
    : m_board{}
    , m_fixedCells{}
{
    // ------------------------------------------------------
    // Initialize all cells to empty and not fixed
    // ------------------------------------------------------
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        for (int col = 0; col < SUDOKU_SIZE; ++col) {
            m_board[row][col] = 0;
            m_fixedCells[row][col] = false;
        }
    }
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
    // Check row, column, and 3x3 box constraints
    // ------------------------------------------------------
    return isValidRow(row, value) && 
           isValidCol(col, value) && 
           isValidBox(row, col, value);
}

bool SudokuBoard::isValidRow(int row, int value) const
{
    if (row < 0 || row >= SUDOKU_SIZE || value < 1 || value > SUDOKU_SIZE) {
        return false;
    }
    
    for (int col = 0; col < SUDOKU_SIZE; ++col) {
        if (m_board[row][col] == value) {
            return false;
        }
    }
    return true;
}

bool SudokuBoard::isValidCol(int col, int value) const
{
    if (col < 0 || col >= SUDOKU_SIZE || value < 1 || value > SUDOKU_SIZE) {
        return false;
    }
    
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
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
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        for (int col = 0; col < SUDOKU_SIZE; ++col) {
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
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        for (int col = 0; col < SUDOKU_SIZE; ++col) {
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
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        for (int col = 0; col < SUDOKU_SIZE; ++col) {
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

SudokuGrid SudokuBoard::getBoard() const
{
    return m_board;
}

void SudokuBoard::setBoard(const SudokuGrid& board)
{
    m_board = board;
}

// ------------------------------------------------------
// Row / Column / Box Accessors
// ------------------------------------------------------

SudokuLine SudokuBoard::getRow(int row) const
{
    SudokuLine result{};

    if (!isValidIndex(row, 0)) {
        return result;
    }

    for (int col = 0; col < SUDOKU_SIZE; ++col) {
        result[col] = m_board[row][col];
    }

    return result;
}

SudokuLine SudokuBoard::getColumn(int col) const
{
    SudokuLine result{};

    if (!isValidIndex(0, col)) {
        return result;
    }

    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        result[row] = m_board[row][col];
    }

    return result;
}

SudokuBox SudokuBoard::getBox(int boxRow, int boxCol) const
{
    SudokuBox result{};

    // ------------------------------------------------------
    // boxRow and boxCol are box indices in [0..2]
    // ------------------------------------------------------
    int startRow = boxRow * 3;
    int startCol = boxCol * 3;

    if (!isValidIndex(startRow, startCol)) {
        return result;
    }

    int index = 0;
    for (int r = startRow; r < startRow + 3; ++r) {
        for (int c = startCol; c < startCol + 3; ++c) {
            if (index < SUDOKU_SIZE) {
                result[index++] = m_board[r][c];
            }
        }
    }

    return result;
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
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        for (int col = 0; col < SUDOKU_SIZE; ++col) {
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
    // Format: 0 = empty, 1-9 = user cell, -1 to -9 = fixed cell
    // ------------------------------------------------------
    clearAllFixedMarks();
    
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        for (int col = 0; col < SUDOKU_SIZE; ++col) {
            int value;
            if (!(file >> value)) {
                return false;
            }
            
            // Negative values indicate fixed cells
            if (value < 0) {
                m_board[row][col] = -value;
                m_fixedCells[row][col] = true;
            } else {
                m_board[row][col] = value;
                m_fixedCells[row][col] = false;
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
    // Format: 0 = empty, 1-9 = user cell, -1 to -9 = fixed cell
    // ------------------------------------------------------
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        for (int col = 0; col < SUDOKU_SIZE; ++col) {
            int value = m_board[row][col];
            
            // Write negative value if cell is fixed
            if (m_fixedCells[row][col] && value != 0) {
                file << -value;
            } else {
                file << value;
            }
            
            if (col < SUDOKU_SIZE - 1) {
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

    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        for (int col = 0; col < SUDOKU_SIZE; ++col) {
            if (m_board[row][col] == 0) {
                oss << ". ";
            } else {
                oss << m_board[row][col] << " ";
            }
            
            // Add vertical separators for 3x3 boxes
            if ((col + 1) % 3 == 0 && col < SUDOKU_SIZE - 1) {
                oss << "| ";
            }
        }
        oss << "\n";
        
        // Add horizontal separators for 3x3 boxes
        if ((row + 1) % 3 == 0 && row < SUDOKU_SIZE - 1) {
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
    return row >= 0 && row < SUDOKU_SIZE && col >= 0 && col < SUDOKU_SIZE;
}
