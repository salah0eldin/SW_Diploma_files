// =================================================
// SudokuSolver.hpp
// Backtracking solver for Sudoku puzzles
// =================================================

#ifndef SUDOKUSOLVER_HPP
#define SUDOKUSOLVER_HPP

#include "SudokuBoard.hpp"

class SudokuSolver
{
public:
    // =================================================
    // Constructor & Destructor
    // =================================================
    SudokuSolver();
    ~SudokuSolver();
    
    // =================================================
    // Solving Methods
    // =================================================
    bool solve(SudokuBoard& board);
    bool hasSolution(const SudokuBoard& board);
    int countSolutions(const SudokuBoard& board, int maxCount = 2);
    
    // =================================================
    // Statistics
    // =================================================
    int getStepCount() const { return m_stepCount; }
    void resetStepCount() { m_stepCount = 0; }

private:
    // =================================================
    // Private Data Members
    // =================================================
    int m_stepCount;
    
    // =================================================
    // Private Helper Methods
    // =================================================
    bool solveRecursive(SudokuBoard& board);
    bool findEmptyCell(const SudokuBoard& board, int& row, int& col);
    int countSolutionsRecursive(SudokuBoard& board, int maxCount);
};

#endif // SUDOKUSOLVER_HPP
