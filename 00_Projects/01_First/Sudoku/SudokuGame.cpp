/**
 * @file SudokuGame.cpp
 * @brief Implementation of Qt GUI and game logic
 *
 * This file implements the Qt-based graphical interface including the
 * custom cell widgets, number pad, menu handlers, and game state management.
 *
 * @author Salah-Eldin Hassen
 * @date December 2025
 * @version 1.0
 * @project Sudoku Game - SW Diploma
 */

#include "SudokuGame.hpp"
#include "./ui_sudoku.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QKeyEvent>
#include <QFocusEvent>
#include <QFont>

// =================================================
// SudokuCell Implementation
// =================================================

SudokuCell::SudokuCell(int row, int col, QWidget *parent)
    : QLineEdit(parent)
    , m_row(row)
    , m_col(col)
    , m_initial(false)
    , m_highlighted(false)
    , m_matchingNumber(false)
    , m_error(false)
    , m_selected(false)
    , m_showPencilMarks(false)
{
    setMaxLength(1);
    setAlignment(Qt::AlignCenter);
    setFixedSize(60, 60);
    
    QFont font = this->font();
    font.setPointSize(20);
    font.setBold(true);
    setFont(font);
    
    // Create label overlay for grid display
    m_gridLabel = new QLabel(this);
    m_gridLabel->setAlignment(Qt::AlignCenter);
    m_gridLabel->setGeometry(0, 0, 60, 60);
    m_gridLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    QFont gridFont("Courier", 9);
    m_gridLabel->setFont(gridFont);
    m_gridLabel->setStyleSheet("QLabel { color: #7f8c8d; background: transparent; }");
    
    updateStyle();
    updateDisplay();
    
    // ------------------------------------------------------
    // Connect text change to value change signal
    // ------------------------------------------------------
    connect(this, &QLineEdit::textChanged, this, [this](const QString &text) {
        if (!text.isEmpty()) {
            bool ok;
            int val = text.toInt(&ok);
            if (ok && val >= 1 && val <= 9) {
                emit cellValueChanged(m_row, m_col, val);
            }
        } else {
            emit cellValueChanged(m_row, m_col, 0);
        }
        updateDisplay();
    });
}

void SudokuCell::setInitial(bool initial)
{
    m_initial = initial;
    setReadOnly(initial);
    updateStyle();
}

void SudokuCell::setHighlighted(bool highlighted)
{
    m_highlighted = highlighted;
    updateStyle();
}

void SudokuCell::setMatchingNumber(bool matching)
{
    m_matchingNumber = matching;
    updateStyle();
}

void SudokuCell::setError(bool error)
{
    m_error = error;
    updateStyle();
}

void SudokuCell::setSelected(bool selected)
{
    m_selected = selected;
    updateStyle();
}

int SudokuCell::value() const
{
    bool ok;
    int val = text().toInt(&ok);
    return ok ? val : 0;
}

void SudokuCell::setValue(int val)
{
    if (val >= 1 && val <= 9) {
        setText(QString::number(val));
    } else {
        clear();
    }
    updateDisplay();
}

void SudokuCell::clearValue()
{
    if (!m_initial) {
        clear();
    }
}

void SudokuCell::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    emit cellSelected(m_row, m_col);
}

void SudokuCell::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    
    // ------------------------------------------------------
    // Handle number keys (1-9)
    // ------------------------------------------------------
    if (key >= Qt::Key_1 && key <= Qt::Key_9) {
        if (!m_initial) {
            setText(QString::number(key - Qt::Key_0));
        }
        return;
    }
    
    // ------------------------------------------------------
    // Handle delete keys
    // ------------------------------------------------------
    if (key == Qt::Key_Backspace || key == Qt::Key_Delete) {
        if (!m_initial) {
            clear();
        }
        return;
    }
    
    // ------------------------------------------------------
    // Handle arrow key navigation
    // ------------------------------------------------------
    if (key == Qt::Key_Up || key == Qt::Key_Down || 
        key == Qt::Key_Left || key == Qt::Key_Right) {
        QLineEdit::keyPressEvent(event);
        return;
    }
    
    // ------------------------------------------------------
    // Block all other input
    // ------------------------------------------------------
    event->ignore();
}

void SudokuCell::updateDisplay()
{
    // Show available moves only if cell is empty and pencil marks are enabled
    if (text().isEmpty() && m_showPencilMarks) {
        QString grid;
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                int num = row * 3 + col + 1;
                if (m_availableMoves.count(num)) {
                    grid += QString::number(num);
                } else {
                    grid += "·";  // Use middle dot for unavailable positions 
                }
                if (col < 2) grid += " ";
            }
            if (row < 2) grid += "\n";
        }
        m_gridLabel->setText(grid);
        m_gridLabel->show();
    } else {
        m_gridLabel->hide();
    }
}

void SudokuCell::setPencilMarksVisible(bool visible)
{
    m_showPencilMarks = visible;
    updateDisplay();
}

void SudokuCell::updateAvailableMoves(const std::set<int>& availableMoves)
{
    m_availableMoves = availableMoves;
    updateDisplay();
}

void SudokuCell::updateStyle()
{
    // ------------------------------------------------------
    // Set base colors
    // ------------------------------------------------------
    QString bgColor = "#2d3436";
    QString textColor = "#dfe6e9";
    QString borderColor = "#636e72";
    
    if (m_initial) {
        textColor = "#74b9ff";
        bgColor = "#2d3436";
    }
    
    if (m_highlighted) {
        bgColor = "#3d4448";
    }
    
    if (m_matchingNumber) {
        bgColor = "#6c5ce7";
        textColor = "#ffffff";
    }
    
    if (m_selected) {
        bgColor = "#0984e3";
        borderColor = "#74b9ff";
    }
    
    if (m_error) {
        bgColor = "#d63031";
        textColor = "#ffffff";
    }
    
    // ------------------------------------------------------
    // Calculate borders for 3x3 box separation
    // ------------------------------------------------------
    int topBorder = 1;
    int leftBorder = 1;
    int rightBorder = 1;
    int bottomBorder = 1;
    
    if (m_row % 3 == 0) topBorder = 3;
    if (m_col % 3 == 0) leftBorder = 3;
    if (m_row == 8) bottomBorder = 3;
    if (m_col == 8) rightBorder = 3;
    if ((m_col + 1) % 3 == 0) rightBorder = 2;
    if ((m_row + 1) % 3 == 0) bottomBorder = 2;
    
    // ------------------------------------------------------
    // Apply stylesheet
    // ------------------------------------------------------
    QString style = QString(
        "SudokuCell {"
        "   background-color: %1;"
        "   color: %2;"
        "   border: none;"
        "   border-top: %3px solid %6;"
        "   border-left: %4px solid %6;"
        "   border-right: %5px solid %6;"
        "   border-bottom: %7px solid %6;"
        "   padding: 5px;"
        "}"
        "SudokuCell:focus {"
        "   background-color: %8;"
        "}"
    ).arg(bgColor)
     .arg(textColor)
     .arg(topBorder)
     .arg(leftBorder)
     .arg(rightBorder)
     .arg(borderColor)
     .arg(bottomBorder)
     .arg(m_selected ? bgColor : "#3d4448");
    
    setStyleSheet(style);
}

// =================================================
// SudokuGame Main Window Implementation
// =================================================

SudokuGame::SudokuGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SudokuGame)
    , m_selectedRow(-1)
    , m_selectedCol(-1)
    , m_pencilMarksVisible(false)
{
    ui->setupUi(this);
    
    // ------------------------------------------------------
    // Initialize cell grid
    // ------------------------------------------------------
    m_cells.resize(9);
    for (int i = 0; i < 9; ++i) {
        m_cells[i].resize(9);
    }
    
    // ------------------------------------------------------
    // Setup GUI components
    // ------------------------------------------------------
    setupGrid();
    setupNumberPad();
    connectSignals();
    
    // ------------------------------------------------------
    // Load initial puzzle
    // ------------------------------------------------------
    loadSamplePuzzle();
    updateStatus("Welcome to Sudoku! Select a cell to begin.");
}

SudokuGame::~SudokuGame()
{
    delete ui;
}

// =================================================
// Private Setup Methods
// =================================================

void SudokuGame::setupGrid()
{
    m_gridLayout = new QGridLayout(ui->gridContainer);
    m_gridLayout->setSpacing(0);
    m_gridLayout->setContentsMargins(0, 0, 0, 0);
    
    // ------------------------------------------------------
    // Create 9x9 grid of SudokuCell widgets
    // ------------------------------------------------------
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            SudokuCell *cell = new SudokuCell(row, col, ui->gridContainer);
            m_cells[row][col] = cell;
            m_gridLayout->addWidget(cell, row, col);
            
            connect(cell, &SudokuCell::cellSelected, this, &SudokuGame::onCellSelected);
            connect(cell, &SudokuCell::cellValueChanged, this, &SudokuGame::onCellValueChanged);
        }
    }
}

void SudokuGame::setupNumberPad()
{
    QString buttonStyle = 
        "QPushButton {"
        "   background-color: #0f3460;"
        "   color: #eaf0f1;"
        "   border: none;"
        "   border-radius: 8px;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   min-width: 20px;"
        "   min-height: 20px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #16537e;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #0a2647;"
        "}";
    
    // ------------------------------------------------------
    // Create number buttons 1-9
    // ------------------------------------------------------
    for (int i = 1; i <= 9; ++i) {
        QPushButton *btn = new QPushButton(QString::number(i), ui->numberPadWidget);
        btn->setStyleSheet(buttonStyle);
        btn->setFixedSize(20, 20);
        
        connect(btn, &QPushButton::clicked, this, [this, i]() {
            onNumberPadClicked(i);
        });
        
        m_numberPadButtons.append(btn);
        ui->numberPadLayout->addWidget(btn);
    }
    
    // ------------------------------------------------------
    // Add erase button
    // ------------------------------------------------------
    QPushButton *eraseBtn = new QPushButton("⌫", ui->numberPadWidget);
    eraseBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #e17055;"
        "   color: #eaf0f1;"
        "   border: none;"
        "   border-radius: 8px;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   min-width: 20px;"
        "   min-height: 20px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #fab1a0;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #d63031;"
        "}"
    );
    eraseBtn->setFixedSize(20, 20);
    connect(eraseBtn, &QPushButton::clicked, this, &SudokuGame::onClearCell);
    ui->numberPadLayout->addWidget(eraseBtn);
}

void SudokuGame::connectSignals()
{
    // ------------------------------------------------------
    // Connect button signals
    // ------------------------------------------------------
    connect(ui->newGameButton, &QPushButton::clicked, this, &SudokuGame::onNewGame);
    connect(ui->loadButton, &QPushButton::clicked, this, &SudokuGame::onLoadPuzzle);
    connect(ui->saveButton, &QPushButton::clicked, this, &SudokuGame::onSavePuzzle);
    connect(ui->solveButton, &QPushButton::clicked, this, &SudokuGame::onSolve);
    connect(ui->checkButton, &QPushButton::clicked, this, &SudokuGame::onCheck);
    connect(ui->hintButton, &QPushButton::clicked, this, &SudokuGame::onHint);
    connect(ui->clearCellButton, &QPushButton::clicked, this, &SudokuGame::onClearCell);
    connect(ui->clearBoardButton, &QPushButton::clicked, this, &SudokuGame::onClearBoard);
    connect(ui->toggleNotesButton, &QPushButton::clicked, this, &SudokuGame::onToggleNotes);
    
    // ------------------------------------------------------
    // Connect menu action signals
    // ------------------------------------------------------
    connect(ui->actionNew, &QAction::triggered, this, &SudokuGame::onNewGame);
    connect(ui->actionLoad, &QAction::triggered, this, &SudokuGame::onLoadPuzzle);
    connect(ui->actionSave, &QAction::triggered, this, &SudokuGame::onSavePuzzle);
    connect(ui->actionSolve, &QAction::triggered, this, &SudokuGame::onSolve);
    connect(ui->actionCheck, &QAction::triggered, this, &SudokuGame::onCheck);
    connect(ui->actionClear, &QAction::triggered, this, &SudokuGame::onClearBoard);
    connect(ui->actionAbout, &QAction::triggered, this, &SudokuGame::onAbout);
    connect(ui->actionExit, &QAction::triggered, this, &QMainWindow::close);
}

// =================================================
// Private Game Logic Methods
// =================================================

void SudokuGame::loadSamplePuzzle()
{
    // ------------------------------------------------------
    // Load the sample puzzle from specification
    // ------------------------------------------------------
    int puzzle[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    
    // ------------------------------------------------------
    // Set board values and mark fixed cells
    // ------------------------------------------------------
    m_board.clearAllFixedMarks();
    
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            m_board.setValue(row, col, puzzle[row][col]);
            
            if (puzzle[row][col] != 0) {
                m_board.markAsFixed(row, col);
            }
        }
    }
    
    syncBoardToGUI();
}

void SudokuGame::syncBoardToGUI()
{
    // ------------------------------------------------------
    // Sync core board state to GUI cells
    // ------------------------------------------------------
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            SudokuCell *cell = m_cells[row][col];
            int value = m_board.getValue(row, col);
            
            cell->setError(false);
            cell->setValue(value);
            cell->setInitial(m_board.isFixed(row, col));
        }
    }
}

void SudokuGame::syncGUIToBoard()
{
    // ------------------------------------------------------
    // Sync GUI cell values to core board
    // ------------------------------------------------------
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (!m_board.isFixed(row, col)) {
                int value = m_cells[row][col]->value();
                m_board.setValue(row, col, value);
            }
        }
    }
}

// =================================================
// Cell Interaction Slots
// =================================================

void SudokuGame::onCellSelected(int row, int col)
{
    // ------------------------------------------------------
    // Clear previous selection
    // ------------------------------------------------------
    if (m_selectedRow >= 0 && m_selectedCol >= 0) {
        m_cells[m_selectedRow][m_selectedCol]->setSelected(false);
    }
    
    clearHighlights();
    
    // ------------------------------------------------------
    // Set new selection
    // ------------------------------------------------------
    m_selectedRow = row;
    m_selectedCol = col;
    
    m_cells[row][col]->setSelected(true);
    highlightRelatedCells(row, col);
    
    // ------------------------------------------------------
    // Highlight all cells with the same number (purple glow)
    // ------------------------------------------------------
    int selectedValue = m_cells[row][col]->value();
    if (selectedValue >= 1 && selectedValue <= 9) {
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if ((r != row || c != col) && m_cells[r][c]->value() == selectedValue) {
                    m_cells[r][c]->setMatchingNumber(true);
                }
            }
        }
    }
    
    // ------------------------------------------------------
    // Update status
    // ------------------------------------------------------
    QString status = QString("Selected cell: Row %1, Column %2").arg(row + 1).arg(col + 1);
    if (m_cells[row][col]->isInitial()) {
        status += " (fixed)";
    }
    updateStatus(status);
}

void SudokuGame::onCellValueChanged(int row, int col, int value)
{
    // ------------------------------------------------------
    // Update board when cell value changes
    // ------------------------------------------------------
    if (!m_board.isFixed(row, col)) {
        m_board.setValue(row, col, value);
    }
    
    // ------------------------------------------------------
    // Update matching number highlights if this is the selected cell
    // ------------------------------------------------------
    if (row == m_selectedRow && col == m_selectedCol) {
        // Clear previous matching highlights
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                m_cells[r][c]->setMatchingNumber(false);
            }
        }
        
        // Highlight cells with the new matching number
        if (value >= 1 && value <= 9) {
            for (int r = 0; r < 9; ++r) {
                for (int c = 0; c < 9; ++c) {
                    if ((r != row || c != col) && m_cells[r][c]->value() == value) {
                        m_cells[r][c]->setMatchingNumber(true);
                    }
                }
            }
        }
    }
}

void SudokuGame::onNumberPadClicked(int number)
{
    if (m_selectedRow >= 0 && m_selectedCol >= 0) {
        SudokuCell *cell = m_cells[m_selectedRow][m_selectedCol];
        
        if (!cell->isInitial()) {
            cell->setValue(number);
            m_board.setValue(m_selectedRow, m_selectedCol, number);
            updateStatus(QString("Placed %1 at Row %2, Column %3")
                        .arg(number).arg(m_selectedRow + 1).arg(m_selectedCol + 1));
        } else {
            updateStatus("Cannot modify initial puzzle cells!");
        }
    } else {
        updateStatus("Please select a cell first!");
    }
}

// =================================================
// Game Action Slots
// =================================================

void SudokuGame::onNewGame()
{
    // ------------------------------------------------------
    // Get selected difficulty from combo box
    // ------------------------------------------------------
    int difficultyIndex = ui->difficultyCombo->currentIndex();
    Difficulty difficulty;
    
    switch (difficultyIndex) {
        case 0: difficulty = Difficulty::EASY; break;
        case 1: difficulty = Difficulty::MEDIUM; break;
        case 2: difficulty = Difficulty::HARD; break;
        default: difficulty = Difficulty::EASY; break;
    }
    
    // ------------------------------------------------------
    // Generate new puzzle
    // ------------------------------------------------------
    updateStatus("Generating puzzle...");
    
    if (m_generator.generate(m_board, difficulty)) {
        syncBoardToGUI();
        m_selectedRow = -1;
        m_selectedCol = -1;
        clearHighlights();
        clearErrors();
        
        // Update pencil marks if they're visible
        if (m_pencilMarksVisible) {
            m_advancedChecks.calculateCandidates(m_board);
            for (int row = 0; row < 9; ++row) {
                for (int col = 0; col < 9; ++col) {
                    if (m_cells[row][col]->value() == 0) {
                        std::set<int> availableMoves = m_advancedChecks.getCandidates(row, col);
                        m_cells[row][col]->updateAvailableMoves(availableMoves);
                    }
                }
            }
        }
        
        QString difficultyName = ui->difficultyCombo->currentText();
        updateStatus(QString("New %1 puzzle generated! Select a cell to begin.").arg(difficultyName));
    } else {
        loadSamplePuzzle();
        updateStatus("Failed to generate puzzle. Loaded sample puzzle instead.");
    }
}

void SudokuGame::onLoadPuzzle()
{
    QString filename = QFileDialog::getOpenFileName(this, 
        "Load Puzzle", "", "Sudoku Files (*.txt *.sudoku);;All Files (*)");
    
    if (!filename.isEmpty()) {
        if (m_board.loadFromFile(filename.toStdString())) {
            syncBoardToGUI();
            clearErrors();
            updateStatus("Puzzle loaded successfully!");
        } else {
            QMessageBox::warning(this, "Load Failed", "Could not load puzzle from file.");
            updateStatus("Failed to load puzzle.");
        }
    }
}

void SudokuGame::onSavePuzzle()
{
    QString filename = QFileDialog::getSaveFileName(this,
        "Save Puzzle", "", "Sudoku Files (*.txt *.sudoku);;All Files (*)");
    
    if (!filename.isEmpty()) {
        syncGUIToBoard();
        
        if (m_board.saveToFile(filename.toStdString())) {
            updateStatus("Puzzle saved successfully!");
        } else {
            QMessageBox::warning(this, "Save Failed", "Could not save puzzle to file.");
            updateStatus("Failed to save puzzle.");
        }
    }
}

void SudokuGame::onSolve()
{
    // ------------------------------------------------------
    // Sync GUI to board before solving
    // ------------------------------------------------------
    syncGUIToBoard();
    
    // ------------------------------------------------------
    // Create a copy to solve
    // ------------------------------------------------------
    SudokuBoard solveBoard;
    solveBoard.copyBoard(m_board);
    
    // ------------------------------------------------------
    // Clear fixed marks for solving
    // ------------------------------------------------------
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (m_board.isFixed(row, col)) {
                solveBoard.markAsFixed(row, col);
            }
        }
    }
    
    // ------------------------------------------------------
    // Attempt to solve
    // ------------------------------------------------------
    if (m_solver.solve(solveBoard)) {
        m_board.copyBoard(solveBoard);
        syncBoardToGUI();
        updateStatus(QString("Puzzle solved in %1 steps!").arg(m_solver.getStepCount()));
        
        QMessageBox::information(this, "Success", 
            QString("Puzzle solved successfully!\nSteps taken: %1").arg(m_solver.getStepCount()));
    } else {
        updateStatus("No solution exists for this puzzle!");
        QMessageBox::warning(this, "No Solution", 
            "This puzzle has no valid solution.");
    }
}

void SudokuGame::onCheck()
{
    // ------------------------------------------------------
    // Sync GUI to board
    // ------------------------------------------------------
    syncGUIToBoard();
    
    clearErrors();
    
    // ------------------------------------------------------
    // Check for errors in current state
    // ------------------------------------------------------
    bool hasErrors = false;
    
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int value = m_board.getValue(row, col);
            
            if (value != 0 && !m_board.isFixed(row, col)) {
                // Temporarily clear to check validity
                m_board.setValue(row, col, 0);
                bool valid = m_board.isValidPlacement(row, col, value);
                m_board.setValue(row, col, value);
                
                if (!valid) {
                    m_cells[row][col]->setError(true);
                    hasErrors = true;
                }
            }
        }
    }
    
    // ------------------------------------------------------
    // Report results
    // ------------------------------------------------------
    if (hasErrors) {
        updateStatus("Found conflicts! Check cells marked in red.");
        QMessageBox::warning(this, "Validation Failed", 
            "The current board has conflicts!\nConflicting cells are highlighted in red.");
    } else if (m_board.isSolved()) {
        updateStatus("Congratulations! Puzzle solved correctly!");
        QMessageBox::information(this, "Success", 
            "Congratulations! You've solved the puzzle correctly!");
    } else {
        updateStatus("No conflicts found. Keep going!");
        QMessageBox::information(this, "Valid", 
            "The current board is valid, but not yet complete.");
    }
}

void SudokuGame::onClearCell()
{
    if (m_selectedRow >= 0 && m_selectedCol >= 0) {
        SudokuCell *cell = m_cells[m_selectedRow][m_selectedCol];
        
        if (!cell->isInitial()) {
            cell->clearValue();
            m_board.setValue(m_selectedRow, m_selectedCol, 0);
            updateStatus(QString("Cleared cell at Row %1, Column %2")
                        .arg(m_selectedRow + 1).arg(m_selectedCol + 1));
        } else {
            updateStatus("Cannot clear initial puzzle cells!");
        }
    } else {
        updateStatus("Please select a cell first!");
    }
}

void SudokuGame::onClearBoard()
{
    // ------------------------------------------------------
    // Ask for confirmation
    // ------------------------------------------------------
    QMessageBox::StandardButton reply = QMessageBox::question(this, 
        "Clear Board", 
        "Are you sure you want to clear all non-fixed cells?",
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // ------------------------------------------------------
        // Clear all non-fixed cells
        // ------------------------------------------------------
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (!m_board.isFixed(row, col)) {
                    m_board.setValue(row, col, 0);
                    m_cells[row][col]->clearValue();
                }
            }
        }
        
        clearErrors();
        updateStatus("Board cleared! All non-fixed cells have been erased.");
    }
}

void SudokuGame::onHint()
{
    // ------------------------------------------------------
    // Sync GUI to board
    // ------------------------------------------------------
    syncGUIToBoard();
    
    // ------------------------------------------------------
    // Find a hint using advanced techniques
    // ------------------------------------------------------
    SudokuHint hint;
    if (m_advancedChecks.findHint(m_board, hint)) {
        // ------------------------------------------------------
        // Highlight the hint cell
        // ------------------------------------------------------
        clearHighlights();
        m_cells[hint.row][hint.col]->setSelected(true);
        m_cells[hint.row][hint.col]->setFocus();
        
        // ------------------------------------------------------
        // Show hint description
        // ------------------------------------------------------
        QString message = QString::fromStdString(hint.description);
        message += QString("\n\nCell: Row %1, Column %2\nValue: %3")
                   .arg(hint.row + 1).arg(hint.col + 1).arg(hint.value);
        
        QMessageBox::information(this, "Hint", message);
        
        updateStatus(QString::fromStdString(hint.description));
    } else {
        // ------------------------------------------------------
        // No hints found - either solved or needs backtracking
        // ------------------------------------------------------
        if (m_board.isSolved()) {
            QMessageBox::information(this, "Hint", "Puzzle is already solved!");
            updateStatus("Puzzle is already solved!");
        } else {
            QMessageBox::information(this, "Hint", 
                "No simple hints available. This puzzle requires advanced solving techniques or trial-and-error.");
            updateStatus("No hints available - try solving or using Check to verify.");
        }
    }
}

void SudokuGame::onToggleNotes()
{
    m_pencilMarksVisible = !m_pencilMarksVisible;
    
    // Calculate candidates once using advanced checks
    if (m_pencilMarksVisible) {
        // Sync GUI values to board first
        syncGUIToBoard();
        // Now calculate candidates
        m_advancedChecks.calculateCandidates(m_board);
    }
    
    // Update all cells to show/hide pencil marks
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            SudokuCell* cell = m_cells[row][col];
            cell->setPencilMarksVisible(m_pencilMarksVisible);
            
            // Get available moves from advanced checks for empty cells
            if (cell->value() == 0 && m_pencilMarksVisible) {
                std::set<int> availableMoves = m_advancedChecks.getCandidates(row, col);
                cell->updateAvailableMoves(availableMoves);
            }
        }
    }
    
    updateStatus(m_pencilMarksVisible ? "Pencil marks enabled" : "Pencil marks disabled");
}

void SudokuGame::onAbout()
{
    QMessageBox::about(this, "About Sudoku",
        "<h2>Sudoku Game</h2>"
        "<p>A modern Sudoku puzzle game built with Qt and C++.</p>"
        "<p><b>Features:</b></p>"
        "<ul>"
        "<li>Interactive 9×9 grid with visual feedback</li>"
        "<li>Number pad for easy input</li>"
        "<li>Keyboard support (1-9, arrows, delete)</li>"
        "<li>Cell highlighting for rows, columns, and boxes</li>"
        "<li>Save/Load puzzles from files</li>"
        "<li>Automatic solver with backtracking algorithm</li>"
        "<li>Puzzle validation and conflict detection</li>"
        "</ul>"
        "<p><b>Technologies:</b></p>"
        "<ul>"
        "<li>C++17 with STL</li>"
        "<li>Qt Framework for GUI</li>"
        "<li>Modular OOP design</li>"
        "</ul>"
        "<p>© 2025 Sudoku Project</p>");
}

// =================================================
// Private UI Helper Methods
// =================================================

void SudokuGame::updateStatus(const QString &message)
{
    ui->statusLabel->setText(message);
}

void SudokuGame::highlightRelatedCells(int row, int col)
{
    // ------------------------------------------------------
    // Highlight same row and column
    // ------------------------------------------------------
    for (int i = 0; i < 9; ++i) {
        if (i != col) m_cells[row][i]->setHighlighted(true);
        if (i != row) m_cells[i][col]->setHighlighted(true);
    }
    
    // ------------------------------------------------------
    // Highlight same 3x3 box
    // ------------------------------------------------------
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;
    
    for (int r = boxRow; r < boxRow + 3; ++r) {
        for (int c = boxCol; c < boxCol + 3; ++c) {
            if (r != row || c != col) {
                m_cells[r][c]->setHighlighted(true);
            }
        }
    }
}

void SudokuGame::clearHighlights()
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            m_cells[row][col]->setHighlighted(false);
            m_cells[row][col]->setMatchingNumber(false);
            m_cells[row][col]->setSelected(false);
        }
    }
}

void SudokuGame::showErrors()
{
    // Implementation moved to onCheck()
}

void SudokuGame::clearErrors()
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            m_cells[row][col]->setError(false);
        }
    }
}
