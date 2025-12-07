/**
 * @file SudokuAdvancedChecks.cpp
 * @brief Implementation of advanced solving techniques
 *
 * This file implements sophisticated Sudoku solving techniques including
 * naked singles, hidden singles, naked pairs, hidden pairs, and locked
 * candidates for puzzle analysis and hint generation.
 *
 * @author Salah-Eldin Hassen
 * @date December 2025
 * @version 1.0
 * @project Sudoku Game - SW Diploma
 */

#include "SudokuAdvancedChecks.hpp"
#include <sstream>

// =================================================
// Constructor & Destructor
// =================================================

SudokuAdvancedChecks::SudokuAdvancedChecks()
{
}

SudokuAdvancedChecks::~SudokuAdvancedChecks()
{
}

// =================================================
// Hint Generation Methods
// =================================================

bool SudokuAdvancedChecks::findHint(const SudokuBoard& board, SudokuHint& hint)
{
    // ------------------------------------------------------
    // Calculate candidates for all empty cells
    // ------------------------------------------------------
    calculateCandidates(board);
    
    // ------------------------------------------------------
    // Try techniques in order of simplicity
    // ------------------------------------------------------
    
    // 1. Naked Singles (easiest)
    if (findNakedSingle(board, hint)) {
        return true;
    }
    
    // 2. Hidden Singles
    if (findHiddenSingle(board, hint)) {
        return true;
    }
    
    // 3. Naked Pairs
    if (findNakedPair(board, hint)) {
        return true;
    }
    
    // 4. Hidden Pairs
    if (findHiddenPair(board, hint)) {
        return true;
    }
    
    // 5. Locked Candidates
    if (findLockedCandidate(board, hint)) {
        return true;
    }
    
    return false;
}

std::vector<SudokuHint> SudokuAdvancedChecks::findAllHints(const SudokuBoard& board)
{
    std::vector<SudokuHint> hints;
    calculateCandidates(board);
    
    SudokuHint hint;
    
    // Find all naked singles
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        for (int col = 0; col < SUDOKU_SIZE; ++col) {
            if (board.isEmpty(row, col) && m_candidates[row][col].size() == 1) {
                hint.type = SudokuHint::NAKED_SINGLE;
                hint.row = row;
                hint.col = col;
                hint.value = *m_candidates[row][col].begin();
                
                std::ostringstream oss;
                oss << "Naked single: Cell (" << (row + 1) << "," << (col + 1) 
                    << ") can only be " << hint.value;
                hint.description = oss.str();
                
                hints.push_back(hint);
            }
        }
    }
    
    return hints;
}

// =================================================
// Candidate Management
// =================================================

void SudokuAdvancedChecks::calculateCandidates(const SudokuBoard& board)
{
    // ------------------------------------------------------
    // Clear all candidates
    // ------------------------------------------------------
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        for (int col = 0; col < SUDOKU_SIZE; ++col) {
            m_candidates[row][col].clear();
        }
    }
    
    // ------------------------------------------------------
    // Calculate candidates for each empty cell
    // ------------------------------------------------------
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        for (int col = 0; col < SUDOKU_SIZE; ++col) {
            if (board.isEmpty(row, col)) {
                updateCandidatesForCell(board, row, col);
            }
        }
    }
}

std::set<int> SudokuAdvancedChecks::getCandidates(int row, int col) const
{
    if (row >= 0 && row < SUDOKU_SIZE && col >= 0 && col < SUDOKU_SIZE) {
        return m_candidates[row][col];
    }
    return std::set<int>();
}

// =================================================
// Technique Detection Methods
// =================================================

bool SudokuAdvancedChecks::findNakedSingle(const SudokuBoard& board, SudokuHint& hint)
{
    // ------------------------------------------------------
    // Find a cell with only one possible candidate
    // ------------------------------------------------------
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        for (int col = 0; col < SUDOKU_SIZE; ++col) {
            if (board.isEmpty(row, col) && m_candidates[row][col].size() == 1) {
                hint.type = SudokuHint::NAKED_SINGLE;
                hint.row = row;
                hint.col = col;
                hint.value = *m_candidates[row][col].begin();
                
                std::ostringstream oss;
                oss << "Naked single at (" << (row + 1) << "," << (col + 1) 
                    << "): Only " << hint.value << " is possible";
                hint.description = oss.str();
                
                return true;
            }
        }
    }
    
    return false;
}

bool SudokuAdvancedChecks::findHiddenSingle(const SudokuBoard& board, SudokuHint& hint)
{
    // ------------------------------------------------------
    // Check each row for hidden singles
    // ------------------------------------------------------
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        if (checkRowForHiddenSingle(board, row, hint)) {
            return true;
        }
    }
    
    // ------------------------------------------------------
    // Check each column for hidden singles
    // ------------------------------------------------------
    for (int col = 0; col < SUDOKU_SIZE; ++col) {
        if (checkColForHiddenSingle(board, col, hint)) {
            return true;
        }
    }
    
    // ------------------------------------------------------
    // Check each 3x3 box for hidden singles
    // ------------------------------------------------------
    for (int boxRow = 0; boxRow < 3; ++boxRow) {
        for (int boxCol = 0; boxCol < 3; ++boxCol) {
            if (checkBoxForHiddenSingle(board, boxRow, boxCol, hint)) {
                return true;
            }
        }
    }
    
    return false;
}

bool SudokuAdvancedChecks::findNakedPair(const SudokuBoard& board, SudokuHint& hint)
{
    // ------------------------------------------------------
    // Check rows for naked pairs
    // ------------------------------------------------------
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        if (checkRowForNakedPair(row, hint)) {
            return true;
        }
    }
    
    // ------------------------------------------------------
    // Check columns for naked pairs
    // ------------------------------------------------------
    for (int col = 0; col < SUDOKU_SIZE; ++col) {
        if (checkColForNakedPair(col, hint)) {
            return true;
        }
    }
    
    // ------------------------------------------------------
    // Check boxes for naked pairs
    // ------------------------------------------------------
    for (int boxRow = 0; boxRow < 3; ++boxRow) {
        for (int boxCol = 0; boxCol < 3; ++boxCol) {
            if (checkBoxForNakedPair(boxRow, boxCol, hint)) {
                return true;
            }
        }
    }
    
    return false;
}

bool SudokuAdvancedChecks::findHiddenPair(const SudokuBoard& board, SudokuHint& hint)
{
    // Simplified implementation - returns false for now
    // Full implementation would be similar to naked pairs but more complex
    return false;
}

bool SudokuAdvancedChecks::findLockedCandidate(const SudokuBoard& board, SudokuHint& hint)
{
    // Simplified implementation - returns false for now
    // Full implementation would check for pointing pairs and box-line reduction
    return false;
}

// =================================================
// Analysis Methods
// =================================================

int SudokuAdvancedChecks::estimateDifficulty(const SudokuBoard& board)
{
    calculateCandidates(board);
    
    int difficulty = 0;
    
    // Count cells with different candidate counts
    int singleCandidates = 0;
    int twoCandidates = 0;
    int manyCandidates = 0;
    
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        for (int col = 0; col < SUDOKU_SIZE; ++col) {
            if (board.isEmpty(row, col)) {
                int count = m_candidates[row][col].size();
                if (count == 1) singleCandidates++;
                else if (count == 2) twoCandidates++;
                else if (count > 2) manyCandidates++;
            }
        }
    }
    
    // Calculate difficulty based on distribution
    difficulty = manyCandidates * 3 + twoCandidates * 2 + singleCandidates;
    
    return difficulty;
}

bool SudokuAdvancedChecks::canSolveWithBasicTechniques(const SudokuBoard& board)
{
    SudokuHint hint;
    return findNakedSingle(board, hint) || findHiddenSingle(board, hint);
}

// =================================================
// Helper Methods
// =================================================

void SudokuAdvancedChecks::updateCandidatesForCell(const SudokuBoard& board, int row, int col)
{
    // ------------------------------------------------------
    // Try each value 1-9 and see if it's valid
    // ------------------------------------------------------
    for (int value = 1; value <= 9; ++value) {
        if (board.isValidPlacement(row, col, value)) {
            m_candidates[row][col].insert(value);
        }
    }
}

bool SudokuAdvancedChecks::checkRowForHiddenSingle(const SudokuBoard& board, int row, SudokuHint& hint)
{
    // ------------------------------------------------------
    // For each value, count how many cells in row can have it
    // ------------------------------------------------------
    for (int value = 1; value <= 9; ++value) {
        int count = 0;
        int lastCol = -1;
        
        for (int col = 0; col < SUDOKU_SIZE; ++col) {
            if (board.isEmpty(row, col) && m_candidates[row][col].count(value) > 0) {
                count++;
                lastCol = col;
            }
        }
        
        if (count == 1) {
            hint.type = SudokuHint::HIDDEN_SINGLE;
            hint.row = row;
            hint.col = lastCol;
            hint.value = value;
            
            std::ostringstream oss;
            oss << "Hidden single in row " << (row + 1) << ": " 
                << value << " can only go in column " << (lastCol + 1);
            hint.description = oss.str();
            
            return true;
        }
    }
    
    return false;
}

bool SudokuAdvancedChecks::checkColForHiddenSingle(const SudokuBoard& board, int col, SudokuHint& hint)
{
    // ------------------------------------------------------
    // For each value, count how many cells in column can have it
    // ------------------------------------------------------
    for (int value = 1; value <= 9; ++value) {
        int count = 0;
        int lastRow = -1;
        
        for (int row = 0; row < SUDOKU_SIZE; ++row) {
            if (board.isEmpty(row, col) && m_candidates[row][col].count(value) > 0) {
                count++;
                lastRow = row;
            }
        }
        
        if (count == 1) {
            hint.type = SudokuHint::HIDDEN_SINGLE;
            hint.row = lastRow;
            hint.col = col;
            hint.value = value;
            
            std::ostringstream oss;
            oss << "Hidden single in column " << (col + 1) << ": " 
                << value << " can only go in row " << (lastRow + 1);
            hint.description = oss.str();
            
            return true;
        }
    }
    
    return false;
}

bool SudokuAdvancedChecks::checkBoxForHiddenSingle(const SudokuBoard& board, int boxRow, int boxCol, SudokuHint& hint)
{
    int startRow = boxRow * 3;
    int startCol = boxCol * 3;
    
    // ------------------------------------------------------
    // For each value, count how many cells in box can have it
    // ------------------------------------------------------
    for (int value = 1; value <= 9; ++value) {
        int count = 0;
        int lastRow = -1, lastCol = -1;
        
        for (int r = startRow; r < startRow + 3; ++r) {
            for (int c = startCol; c < startCol + 3; ++c) {
                if (board.isEmpty(r, c) && m_candidates[r][c].count(value) > 0) {
                    count++;
                    lastRow = r;
                    lastCol = c;
                }
            }
        }
        
        if (count == 1) {
            hint.type = SudokuHint::HIDDEN_SINGLE;
            hint.row = lastRow;
            hint.col = lastCol;
            hint.value = value;
            
            std::ostringstream oss;
            oss << "Hidden single in box (" << (boxRow + 1) << "," << (boxCol + 1) 
                << "): " << value << " can only go at (" << (lastRow + 1) << "," << (lastCol + 1) << ")";
            hint.description = oss.str();
            
            return true;
        }
    }
    
    return false;
}

bool SudokuAdvancedChecks::checkRowForNakedPair(int row, SudokuHint& hint)
{
    // ------------------------------------------------------
    // Find two cells with exactly the same two candidates
    // ------------------------------------------------------
    for (int col1 = 0; col1 < SUDOKU_SIZE; ++col1) {
        if (m_candidates[row][col1].size() == 2) {
            for (int col2 = col1 + 1; col2 < SUDOKU_SIZE; ++col2) {
                if (m_candidates[row][col2] == m_candidates[row][col1]) {
                    hint.type = SudokuHint::NAKED_PAIR;
                    hint.row = row;
                    hint.col = col1;
                    
                    auto it = m_candidates[row][col1].begin();
                    int val1 = *it++;
                    int val2 = *it;
                    
                    std::ostringstream oss;
                    oss << "Naked pair in row " << (row + 1) << ": Cells (" 
                        << (row + 1) << "," << (col1 + 1) << ") and (" 
                        << (row + 1) << "," << (col2 + 1) << ") both contain {" 
                        << val1 << "," << val2 << "}";
                    hint.description = oss.str();
                    
                    return true;
                }
            }
        }
    }
    
    return false;
}

bool SudokuAdvancedChecks::checkColForNakedPair(int col, SudokuHint& hint)
{
    // ------------------------------------------------------
    // Find two cells with exactly the same two candidates
    // ------------------------------------------------------
    for (int row1 = 0; row1 < SUDOKU_SIZE; ++row1) {
        if (m_candidates[row1][col].size() == 2) {
            for (int row2 = row1 + 1; row2 < SUDOKU_SIZE; ++row2) {
                if (m_candidates[row2][col] == m_candidates[row1][col]) {
                    hint.type = SudokuHint::NAKED_PAIR;
                    hint.row = row1;
                    hint.col = col;
                    
                    auto it = m_candidates[row1][col].begin();
                    int val1 = *it++;
                    int val2 = *it;
                    
                    std::ostringstream oss;
                    oss << "Naked pair in column " << (col + 1) << ": Cells (" 
                        << (row1 + 1) << "," << (col + 1) << ") and (" 
                        << (row2 + 1) << "," << (col + 1) << ") both contain {" 
                        << val1 << "," << val2 << "}";
                    hint.description = oss.str();
                    
                    return true;
                }
            }
        }
    }
    
    return false;
}

bool SudokuAdvancedChecks::checkBoxForNakedPair(int boxRow, int boxCol, SudokuHint& hint)
{
    int startRow = boxRow * 3;
    int startCol = boxCol * 3;
    
    // ------------------------------------------------------
    // Collect all cells in box with exactly 2 candidates
    // ------------------------------------------------------
    std::vector<std::pair<int, int>> pairCells;
    
    for (int r = startRow; r < startRow + 3; ++r) {
        for (int c = startCol; c < startCol + 3; ++c) {
            if (m_candidates[r][c].size() == 2) {
                pairCells.push_back({r, c});
            }
        }
    }
    
    // Check for matching pairs
    for (size_t i = 0; i < pairCells.size(); ++i) {
        for (size_t j = i + 1; j < pairCells.size(); ++j) {
            int r1 = pairCells[i].first, c1 = pairCells[i].second;
            int r2 = pairCells[j].first, c2 = pairCells[j].second;
            
            if (m_candidates[r1][c1] == m_candidates[r2][c2]) {
                hint.type = SudokuHint::NAKED_PAIR;
                hint.row = r1;
                hint.col = c1;
                
                auto it = m_candidates[r1][c1].begin();
                int val1 = *it++;
                int val2 = *it;
                
                std::ostringstream oss;
                oss << "Naked pair in box (" << (boxRow + 1) << "," << (boxCol + 1) 
                    << "): Cells (" << (r1 + 1) << "," << (c1 + 1) << ") and (" 
                    << (r2 + 1) << "," << (c2 + 1) << ") both contain {" 
                    << val1 << "," << val2 << "}";
                hint.description = oss.str();
                
                return true;
            }
        }
    }
    
    return false;
}
