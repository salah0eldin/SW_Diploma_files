/**
 * @file SudokuSolver.hpp
 * @brief Backtracking solver for Sudoku puzzles
 *
 * This header defines the solver class that uses recursive backtracking
 * algorithm to find solutions for Sudoku puzzles. It can solve puzzles,
 * verify solvability, and count possible solutions.
 *
 * @author Salah-Eldin Hassen
 * @date December 2025
 * @version 1.0
 * @project Sudoku Game - SW Diploma
 */

#pragma once

#include "SudokuBoard.hpp"

class SudokuSolver
{
public:
    // ------------------------------------------------------
    // Constructor & Destructor
    // ------------------------------------------------------
    SudokuSolver();
    ~SudokuSolver();
    
    // ------------------------------------------------------
    // Solving Methods
    // ------------------------------------------------------
    bool solve(SudokuBoard& board);
    bool hasSolution(const SudokuBoard& board);
    int countSolutions(const SudokuBoard& board, int maxCount = 2);
    
    // ------------------------------------------------------
    // Statistics
    // ------------------------------------------------------
    int getStepCount() const { return m_stepCount; }
    void resetStepCount() { m_stepCount = 0; }

private:
    // ------------------------------------------------------
    // Private Data Members
    // ------------------------------------------------------
    int m_stepCount;
    
    // ------------------------------------------------------
    // Private Helper Methods
    // ------------------------------------------------------
    bool solveRecursive(SudokuBoard& board);
    bool findEmptyCell(const SudokuBoard& board, int& row, int& col);
    int countSolutionsRecursive(SudokuBoard& board, int maxCount);
};

