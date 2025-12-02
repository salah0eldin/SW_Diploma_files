// =================================================
// SudokuWindow.h
// Main window class for the Sudoku game
// Handles UI setup, user interactions, and game coordination
// =================================================

#ifndef SUDOKUWINDOW_H
#define SUDOKUWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>

#include "SudokuCell.h"

// =================================================
// Forward Declarations
// =================================================

QT_BEGIN_NAMESPACE
namespace Ui {
class sudoku;
}
QT_END_NAMESPACE

// =================================================
// SudokuWindow Class Declaration
// Main application window for the Sudoku game
// =================================================

class SudokuWindow : public QMainWindow
{
    Q_OBJECT

public:
    // =================================================
    // Constructor & Destructor
    // =================================================
    
    explicit SudokuWindow(QWidget *parent = nullptr);
    ~SudokuWindow();

private slots:
    // =================================================
    // Cell Interaction Slots
    // =================================================
    
    /**
     * @brief Handles cell selection
     * @param row Selected row (0-8)
     * @param col Selected column (0-8)
     */
    void onCellSelected(int row, int col);

    /**
     * @brief Handles cell value changes
     * @param row Cell row (0-8)
     * @param col Cell column (0-8)
     * @param value New value (0-9, 0 = empty)
     */
    void onCellValueChanged(int row, int col, int value);

    /**
     * @brief Handles number pad button clicks
     * @param number Number clicked (1-9)
     */
    void onNumberPadClicked(int number);

    // =================================================
    // Game Action Slots
    // =================================================
    
    void onNewGame();       // Start a new game
    void onLoadPuzzle();    // Load puzzle from file
    void onSavePuzzle();    // Save puzzle to file
    void onSolve();         // Auto-solve the puzzle
    void onCheck();         // Check current solution
    void onClearCell();     // Clear selected cell
    void onAbout();         // Show about dialog

private:
    // =================================================
    // Private Members
    // =================================================
    
    Ui::sudoku *ui;                              // UI form pointer
    QVector<QVector<SudokuCell*>> m_cells;       // 9x9 grid of cells
    QVector<QPushButton*> m_numberPadButtons;    // Number pad buttons (1-9)
    QGridLayout *m_gridLayout;                   // Grid layout for cells

    int m_selectedRow;    // Currently selected row (-1 if none)
    int m_selectedCol;    // Currently selected column (-1 if none)

    // =================================================
    // UI Setup Methods
    // =================================================
    
    /**
     * @brief Creates the 9x9 Sudoku grid
     */
    void setupGrid();

    /**
     * @brief Creates the number pad buttons
     */
    void setupNumberPad();

    /**
     * @brief Connects all signals and slots
     */
    void connectSignals();

    // =================================================
    // Game Logic Methods
    // =================================================
    
    /**
     * @brief Loads a sample puzzle for demonstration
     */
    void loadSamplePuzzle();

    /**
     * @brief Updates the status bar message
     * @param message Message to display
     */
    void updateStatus(const QString &message);

    /**
     * @brief Highlights cells in same row, column, and 3x3 box
     * @param row Center row
     * @param col Center column
     */
    void highlightRelatedCells(int row, int col);

    /**
     * @brief Clears all cell highlights
     */
    void clearHighlights();
};

#endif // SUDOKUWINDOW_H
