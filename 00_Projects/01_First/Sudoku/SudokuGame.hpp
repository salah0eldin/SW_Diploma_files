// =================================================
// SudokuGame.hpp
// Game logic and Qt GUI integration
// =================================================

#pragma once

#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"
#include <QMainWindow>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVector>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class SudokuGame;
}
QT_END_NAMESPACE

// =================================================
// SudokuCell Class - Custom cell widget
// =================================================

class SudokuCell : public QLineEdit
{
    Q_OBJECT

public:
    explicit SudokuCell(int row, int col, QWidget *parent = nullptr);
    
    // ------------------------------------------------------
    // Accessors
    // ------------------------------------------------------
    int row() const { return m_row; }
    int col() const { return m_col; }
    int value() const;
    
    // ------------------------------------------------------
    // State Management
    // ------------------------------------------------------
    void setInitial(bool initial);
    bool isInitial() const { return m_initial; }
    
    void setValue(int val);
    void clearValue();
    
    // ------------------------------------------------------
    // Visual State
    // ------------------------------------------------------
    void setHighlighted(bool highlighted);
    void setError(bool error);
    void setSelected(bool selected);

signals:
    void cellSelected(int row, int col);
    void cellValueChanged(int row, int col, int value);

protected:
    void focusInEvent(QFocusEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    // ------------------------------------------------------
    // Private Data Members
    // ------------------------------------------------------
    int m_row;
    int m_col;
    bool m_initial;
    bool m_highlighted;
    bool m_error;
    bool m_selected;
    
    // ------------------------------------------------------
    // Private Methods
    // ------------------------------------------------------
    void updateStyle();
};

// =================================================
// SudokuGame Class - Main game window
// =================================================

class SudokuGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit SudokuGame(QWidget *parent = nullptr);
    ~SudokuGame();

private slots:
    // ------------------------------------------------------
    // Cell Interaction Slots
    // ------------------------------------------------------
    void onCellSelected(int row, int col);
    void onCellValueChanged(int row, int col, int value);
    void onNumberPadClicked(int number);
    
    // ------------------------------------------------------
    // Game Action Slots
    // ------------------------------------------------------
    void onNewGame();
    void onLoadPuzzle();
    void onSavePuzzle();
    void onSolve();
    void onCheck();
    void onClearCell();
    void onAbout();

private:
    // ------------------------------------------------------
    // Private Data Members
    // ------------------------------------------------------
    Ui::SudokuGame *ui;
    
    SudokuBoard m_board;                              // Core board logic
    SudokuSolver m_solver;                            // Solver logic
    
    QVector<QVector<SudokuCell*>> m_cells;            // GUI cells
    QVector<QPushButton*> m_numberPadButtons;         // Number pad buttons
    QGridLayout *m_gridLayout;                        // Grid layout
    
    int m_selectedRow;                                // Currently selected cell
    int m_selectedCol;
    
    // ------------------------------------------------------
    // Private Setup Methods
    // ------------------------------------------------------
    void setupGrid();
    void setupNumberPad();
    void connectSignals();
    
    // ------------------------------------------------------
    // Private Game Logic Methods
    // ------------------------------------------------------
    void loadSamplePuzzle();
    void syncBoardToGUI();
    void syncGUIToBoard();
    
    // ------------------------------------------------------
    // Private UI Helper Methods
    // ------------------------------------------------------
    void updateStatus(const QString &message);
    void highlightRelatedCells(int row, int col);
    void clearHighlights();
    void showErrors();
    void clearErrors();
};
