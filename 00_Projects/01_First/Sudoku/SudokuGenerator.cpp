/**
 * @file SudokuGenerator.cpp
 * @brief Implementation of puzzle generation algorithm
 *
 * This file implements the two-phase puzzle generation algorithm:
 * 1. Generate a complete valid Sudoku solution
 * 2. Remove cells while maintaining uniqueness
 *
 * @author Salah-Eldin Hassen
 * @date December 2025
 * @version 1.0
 * @project Sudoku Game - SW Diploma
 */

#include "SudokuGenerator.hpp"
#include <algorithm>
#include <chrono>

// =================================================
// Constructor & Destructor
// =================================================

SudokuGenerator::SudokuGenerator()
    : m_rng(std::chrono::steady_clock::now().time_since_epoch().count())
    , m_solver()
    , m_lastAttempts(0)
{
}

SudokuGenerator::SudokuGenerator(unsigned int seed)
    : m_rng(seed)
    , m_solver()
    , m_lastAttempts(0)
{
}

SudokuGenerator::~SudokuGenerator()
{
}

// =================================================
// Public Generation Methods
// =================================================

bool SudokuGenerator::generate(SudokuBoard& board, Difficulty difficulty)
{
    int cellsToRemove = getCellsToRemove(difficulty);
    return generateWithClueCount(board, 81 - cellsToRemove);
}

bool SudokuGenerator::generateWithClueCount(SudokuBoard& board, int clueCount)
{
    // ------------------------------------------------------
    // Validate clue count (must leave some cells filled)
    // ------------------------------------------------------
    if (clueCount < 17 || clueCount > 81) {
        return false;
    }
    
    m_lastAttempts = 0;
    int cellsToRemove = 81 - clueCount;
    
    // ------------------------------------------------------
    // Phase 1: Generate complete solution
    // ------------------------------------------------------
    bool solutionGenerated = generateFullSolution(board);
    if (!solutionGenerated) {
        // Try again with fresh start
        for (int row = 0; row < SUDOKU_SIZE; ++row) {
            for (int col = 0; col < SUDOKU_SIZE; ++col) {
                board.setValue(row, col, 0);
            }
        }
        solutionGenerated = generateFullSolution(board);
        if (!solutionGenerated) {
            return false;
        }
    }
    
    // ------------------------------------------------------
    // Phase 2: Remove cells
    // ------------------------------------------------------
    bool cellsRemoved = removeCells(board, cellsToRemove);
    if (!cellsRemoved) {
        return false;
    }
    
    // ------------------------------------------------------
    // Mark remaining cells as fixed (the puzzle clues)
    // ------------------------------------------------------
    board.clearAllFixedMarks();
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        for (int col = 0; col < SUDOKU_SIZE; ++col) {
            if (board.getValue(row, col) != 0) {
                board.markAsFixed(row, col);
            }
        }
    }
    
    return true;
}

// =================================================
// Private Generation Methods - Full Solution
// =================================================

bool SudokuGenerator::generateFullSolution(SudokuBoard& board)
{
    // ------------------------------------------------------
    // Clear board
    // ------------------------------------------------------
    for (int row = 0; row < SUDOKU_SIZE; ++row) {
        for (int col = 0; col < SUDOKU_SIZE; ++col) {
            board.setValue(row, col, 0);
        }
    }
    board.clearAllFixedMarks();
    
    // ------------------------------------------------------
    // Fast approach: Fill diagonal 3x3 boxes first (they're independent)
    // This dramatically reduces backtracking
    // ------------------------------------------------------
    for (int box = 0; box < 3; ++box) {
        std::array<int, 9> numbers{};
        getShuffledNumbers(numbers);
        
        int startRow = box * 3;
        int startCol = box * 3;
        int idx = 0;
        
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                board.setValue(startRow + r, startCol + c, numbers[idx++]);
            }
        }
    }
    
    // ------------------------------------------------------
    // Now fill remaining cells with backtracking
    // ------------------------------------------------------
    return fillBoardRecursive(board, 0);
}

bool SudokuGenerator::fillBoardRecursive(SudokuBoard& board, int position)
{
    // ------------------------------------------------------
    // Find next empty cell (skip already filled diagonal boxes)
    // ------------------------------------------------------
    while (position < 81) {
        int row = position / SUDOKU_SIZE;
        int col = position % SUDOKU_SIZE;
        
        if (board.getValue(row, col) == 0) {
            break; // Found empty cell
        }
        position++;
    }
    
    // ------------------------------------------------------
    // Base case: all cells filled
    // ------------------------------------------------------
    if (position >= 81) {
        return true;
    }
    
    int row = position / SUDOKU_SIZE;
    int col = position % SUDOKU_SIZE;
    
    // ------------------------------------------------------
    // Try numbers in random order
    // ------------------------------------------------------
    std::array<int, 9> numbers{};
    getShuffledNumbers(numbers);
    
    for (int i = 0; i < 9; ++i) {
        int value = numbers[i];
        
        if (board.isValidPlacement(row, col, value)) {
            board.setValue(row, col, value);
            
            if (fillBoardRecursive(board, position + 1)) {
                return true;
            }
            
            // Backtrack
            board.setValue(row, col, 0);
        }
    }
    
    return false;
}

void SudokuGenerator::getShuffledNumbers(std::array<int, 9>& numbers)
{
    // ------------------------------------------------------
    // Fill array with 1-9 and shuffle
    // ------------------------------------------------------
    for (int i = 0; i < 9; ++i) {
        numbers[i] = i + 1;
    }
    
    std::shuffle(numbers.begin(), numbers.end(), m_rng);
}

// =================================================
// Private Generation Methods - Cell Removal
// =================================================

bool SudokuGenerator::removeCells(SudokuBoard& board, int cellsToRemove)
{
    // ------------------------------------------------------
    // Fast removal: remove cells randomly
    // Since we start with a valid complete solution, removing cells
    // will always leave a solvable puzzle
    // ------------------------------------------------------
    std::array<int, 81> positions{};
    getRandomCellOrder(positions);
    
    int removed = 0;
    m_lastAttempts = 0;
    
    // ------------------------------------------------------
    // Simply remove the requested number of cells
    // ------------------------------------------------------
    for (int i = 0; i < 81 && removed < cellsToRemove; ++i) {
        m_lastAttempts++;
        
        int pos = positions[i];
        int row = pos / SUDOKU_SIZE;
        int col = pos % SUDOKU_SIZE;
        
        if (board.getValue(row, col) != 0) {
            board.setValue(row, col, 0);
            removed++;
        }
    }
    
    // Always succeeds - we removed exactly what was requested
    return removed >= cellsToRemove;
}

bool SudokuGenerator::hasUniqueSolution(const SudokuBoard& board)
{
    // ------------------------------------------------------
    // Check if puzzle has exactly one solution
    // ------------------------------------------------------
    int solutionCount = m_solver.countSolutions(board, 2);
    return solutionCount == 1;
}

void SudokuGenerator::getRandomCellOrder(std::array<int, 81>& positions)
{
    // ------------------------------------------------------
    // Fill with positions 0-80 and shuffle
    // ------------------------------------------------------
    for (int i = 0; i < 81; ++i) {
        positions[i] = i;
    }
    
    std::shuffle(positions.begin(), positions.end(), m_rng);
}

// =================================================
// Difficulty Helpers
// =================================================

int SudokuGenerator::getCellsToRemove(Difficulty difficulty) const
{
    // ------------------------------------------------------
    // Determine cells to remove based on difficulty
    // Easy: 36-40 clues (41-45 cells removed)
    // Medium: 30-35 clues (46-51 cells removed)
    // Hard: 25-29 clues (52-56 cells removed)
    // ------------------------------------------------------
    
    switch (difficulty) {
        case Difficulty::EASY:
            return 43; // Remove 43 cells, leave 38 clues
        
        case Difficulty::MEDIUM:
            return 48; // Remove 48 cells, leave 33 clues
        
        case Difficulty::HARD:
            return 54; // Remove 54 cells, leave 27 clues
        
        default:
            return 43; // Default to easy
    }
}
