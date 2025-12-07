/**
 * @file SudokuSolver.cpp
 * @brief Implementation of backtracking solver
 *
 * This file implements the recursive backtracking algorithm for solving
 * Sudoku puzzles, including helper methods for cell searching and
 * solution counting.
 *
 * @author Salah-Eldin Hassen
 * @date December 2025
 * @version 1.0
 * @project Sudoku Game - SW Diploma
 */

#include "SudokuSolver.hpp"

// =================================================
// Constructor & Destructor
// =================================================

SudokuSolver::SudokuSolver()
    : m_stepCount(0)
{
}

SudokuSolver::~SudokuSolver()
{
}

// =================================================
// Solving Methods
// =================================================

bool SudokuSolver::solve(SudokuBoard& board)
{
    m_stepCount = 0;
    return solveRecursive(board);
}

bool SudokuSolver::hasSolution(const SudokuBoard& board)
{
    // ------------------------------------------------------
    // Create a copy to avoid modifying original board
    // ------------------------------------------------------
    SudokuBoard tempBoard;
    tempBoard.copyBoard(board);
    
    return solve(tempBoard);
}

int SudokuSolver::countSolutions(const SudokuBoard& board, int maxCount)
{
    // ------------------------------------------------------
    // Count number of solutions (useful for puzzle generation)
    // ------------------------------------------------------
    SudokuBoard tempBoard;
    tempBoard.copyBoard(board);
    
    m_stepCount = 0;
    return countSolutionsRecursive(tempBoard, maxCount);
}

// =================================================
// Private Helper Methods
// =================================================

bool SudokuSolver::solveRecursive(SudokuBoard& board)
{
    m_stepCount++;
    
    // ------------------------------------------------------
    // Find next empty cell
    // ------------------------------------------------------
    int row, col;
    if (!findEmptyCell(board, row, col)) {
        // No empty cells means puzzle is solved
        return true;
    }
    
    // ------------------------------------------------------
    // Try values 1-9
    // ------------------------------------------------------
    for (int value = 1; value <= 9; ++value) {
        if (board.isValidPlacement(row, col, value)) {
            // Place value
            board.setValue(row, col, value);
            
            // Recursively solve
            if (solveRecursive(board)) {
                return true;
            }
            
            // Backtrack if solution not found
            board.clearValue(row, col);
        }
    }
    
    // ------------------------------------------------------
    // No solution found with current configuration
    // ------------------------------------------------------
    return false;
}

bool SudokuSolver::findEmptyCell(const SudokuBoard& board, int& row, int& col)
{
    // ------------------------------------------------------
    // Find first empty cell (value = 0)
    // ------------------------------------------------------
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (board.isEmpty(r, c)) {
                row = r;
                col = c;
                return true;
            }
        }
    }
    return false;
}

int SudokuSolver::countSolutionsRecursive(SudokuBoard& board, int maxCount)
{
    m_stepCount++;
    
    // ------------------------------------------------------
    // Find next empty cell
    // ------------------------------------------------------
    int row, col;
    if (!findEmptyCell(board, row, col)) {
        // Found a complete solution
        return 1;
    }
    
    // ------------------------------------------------------
    // Try all possible values and count solutions
    // ------------------------------------------------------
    int solutionCount = 0;
    
    for (int value = 1; value <= 9; ++value) {
        if (board.isValidPlacement(row, col, value)) {
            board.setValue(row, col, value);
            
            solutionCount += countSolutionsRecursive(board, maxCount);
            
            // Early exit if we've found enough solutions
            if (solutionCount >= maxCount) {
                board.clearValue(row, col);
                return solutionCount;
            }
            
            board.clearValue(row, col);
        }
    }
    
    return solutionCount;
}
