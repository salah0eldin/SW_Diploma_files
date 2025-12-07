/**
 * @file SudokuGenerator.hpp
 * @brief Automatic puzzle generation with difficulty levels
 *
 * This header defines the generator class that creates valid Sudoku puzzles
 * of varying difficulty by generating complete solutions and strategically
 * removing cells while maintaining uniqueness.
 *
 * @author Salah-Eldin Hassen
 * @date December 2025
 * @version 1.0
 * @project Sudoku Game - SW Diploma
 */

#pragma once

#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"
#include <random>

// =================================================
// Difficulty Level Enumeration
// =================================================

enum class Difficulty
{
    EASY,      // 36-40 clues (41-45 cells removed)
    MEDIUM,    // 30-35 clues (46-51 cells removed)
    HARD       // 25-29 clues (52-56 cells removed)
};

// =================================================
// SudokuGenerator Class
// =================================================

class SudokuGenerator
{
public:
    // ------------------------------------------------------
    // Constructor & Destructor
    // ------------------------------------------------------
    SudokuGenerator();
    explicit SudokuGenerator(unsigned int seed);
    ~SudokuGenerator();
    
    // ------------------------------------------------------
    // Puzzle Generation Methods
    // ------------------------------------------------------
    bool generate(SudokuBoard& board, Difficulty difficulty);
    bool generateWithClueCount(SudokuBoard& board, int clueCount);
    
    // ------------------------------------------------------
    // Statistics
    // ------------------------------------------------------
    int getLastGenerationAttempts() const { return m_lastAttempts; }
    void resetStatistics() { m_lastAttempts = 0; }

private:
    // ------------------------------------------------------
    // Private Data Members
    // ------------------------------------------------------
    std::mt19937 m_rng;                    // Random number generator
    SudokuSolver m_solver;                 // Solver for verification
    int m_lastAttempts;                    // Track generation attempts
    
    // ------------------------------------------------------
    // Private Generation Methods
    // ------------------------------------------------------
    bool generateFullSolution(SudokuBoard& board);
    bool fillBoardRecursive(SudokuBoard& board, int position);
    void getShuffledNumbers(std::array<int, 9>& numbers);
    
    bool removeCells(SudokuBoard& board, int cellsToRemove);
    bool hasUniqueSolution(const SudokuBoard& board);
    void getRandomCellOrder(std::array<int, 81>& positions);
    
    // ------------------------------------------------------
    // Difficulty Helpers
    // ------------------------------------------------------
    int getCellsToRemove(Difficulty difficulty) const;
};
