/**
 * @file SudokuAdvancedChecks.hpp
 * @brief Advanced Sudoku solving techniques and analysis
 *
 * This header defines advanced solving techniques beyond basic backtracking,
 * including naked pairs, hidden pairs, locked candidates, and pointing pairs.
 * These techniques can be used for hints and puzzle analysis.
 *
 * @author Salah-Eldin Hassen
 * @date December 2025
 * @version 1.0
 * @project Sudoku Game - SW Diploma
 */

#pragma once

#include "SudokuBoard.hpp"
#include <vector>
#include <set>
#include <string>

// =================================================
// Hint Structure
// =================================================

struct SudokuHint
{
    enum Type {
        NAKED_SINGLE,      // Cell has only one possible value
        HIDDEN_SINGLE,     // Value can only go in one cell in a unit
        NAKED_PAIR,        // Two cells with same two candidates
        HIDDEN_PAIR,       // Two values locked to two cells
        LOCKED_CANDIDATE,  // Pointing/Claiming technique
        BASIC_ELIMINATION  // Simple elimination
    };
    
    Type type;
    int row;
    int col;
    int value;
    std::string description;
    std::vector<std::pair<int, int>> affectedCells;
};

// =================================================
// SudokuAdvancedChecks Class
// =================================================

class SudokuAdvancedChecks
{
public:
    // ------------------------------------------------------
    // Constructor & Destructor
    // ------------------------------------------------------
    SudokuAdvancedChecks();
    ~SudokuAdvancedChecks();
    
    // ------------------------------------------------------
    // Hint Generation Methods
    // ------------------------------------------------------
    bool findHint(const SudokuBoard& board, SudokuHint& hint);
    std::vector<SudokuHint> findAllHints(const SudokuBoard& board);
    
    // ------------------------------------------------------
    // Candidate Management
    // ------------------------------------------------------
    void calculateCandidates(const SudokuBoard& board);
    std::set<int> getCandidates(int row, int col) const;
    
    // ------------------------------------------------------
    // Analysis Methods
    // ------------------------------------------------------
    int estimateDifficulty(const SudokuBoard& board);
    bool canSolveWithBasicTechniques(const SudokuBoard& board);

private:
    // ------------------------------------------------------
    // Private Data Members
    // ------------------------------------------------------
    std::array<std::array<std::set<int>, SUDOKU_SIZE>, SUDOKU_SIZE> m_candidates;
    
    // ------------------------------------------------------
    // Technique Detection Methods
    // ------------------------------------------------------
    bool findNakedSingle(const SudokuBoard& board, SudokuHint& hint);
    bool findHiddenSingle(const SudokuBoard& board, SudokuHint& hint);
    bool findNakedPair(const SudokuBoard& board, SudokuHint& hint);
    bool findHiddenPair(const SudokuBoard& board, SudokuHint& hint);
    bool findLockedCandidate(const SudokuBoard& board, SudokuHint& hint);
    
    // ------------------------------------------------------
    // Helper Methods
    // ------------------------------------------------------
    void updateCandidatesForCell(const SudokuBoard& board, int row, int col);
    bool checkRowForHiddenSingle(const SudokuBoard& board, int row, SudokuHint& hint);
    bool checkColForHiddenSingle(const SudokuBoard& board, int col, SudokuHint& hint);
    bool checkBoxForHiddenSingle(const SudokuBoard& board, int boxRow, int boxCol, SudokuHint& hint);
    
    bool checkRowForNakedPair(int row, SudokuHint& hint);
    bool checkColForNakedPair(int col, SudokuHint& hint);
    bool checkBoxForNakedPair(int boxRow, int boxCol, SudokuHint& hint);
};
