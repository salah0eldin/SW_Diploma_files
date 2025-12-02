// =================================================
// SudokuWindow.cpp
// Implementation of the main Sudoku game window
// =================================================

#include "SudokuWindow.h"
#include "./ui_sudoku.h"

#include <QMessageBox>
#include <QFileDialog>

// =================================================
// Constructor & Destructor
// =================================================

SudokuWindow::SudokuWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sudoku)
    , m_selectedRow(-1)
    , m_selectedCol(-1)
{
    // ------------------------------------------------------
    // Initialize UI from form
    // ------------------------------------------------------
    ui->setupUi(this);

    // ------------------------------------------------------
    // Initialize 9x9 cell grid storage
    // ------------------------------------------------------
    m_cells.resize(9);
    for (int i = 0; i < 9; ++i) {
        m_cells[i].resize(9);
    }

    // ------------------------------------------------------
    // Setup UI components
    // ------------------------------------------------------
    setupGrid();
    setupNumberPad();
    connectSignals();

    // ------------------------------------------------------
    // Load initial puzzle and show welcome message
    // ------------------------------------------------------
    loadSamplePuzzle();
    updateStatus("Welcome to Sudoku! Select a cell to begin.");
}

SudokuWindow::~SudokuWindow()
{
    delete ui;
}

// =================================================
// UI Setup Methods
// =================================================

void SudokuWindow::setupGrid()
{
    // ------------------------------------------------------
    // Create grid layout for the Sudoku board
    // ------------------------------------------------------
    m_gridLayout = new QGridLayout(ui->gridContainer);
    m_gridLayout->setSpacing(0);
    m_gridLayout->setContentsMargins(0, 0, 0, 0);

    // ------------------------------------------------------
    // Create 81 cells (9x9 grid)
    // ------------------------------------------------------
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            SudokuCell *cell = new SudokuCell(row, col, ui->gridContainer);
            m_cells[row][col] = cell;
            m_gridLayout->addWidget(cell, row, col);

            // Connect cell signals
            connect(cell, &SudokuCell::cellSelected, 
                    this, &SudokuWindow::onCellSelected);
            connect(cell, &SudokuCell::cellValueChanged, 
                    this, &SudokuWindow::onCellValueChanged);
        }
    }
}

void SudokuWindow::setupNumberPad()
{
    // ------------------------------------------------------
    // Define style for number pad buttons
    // ------------------------------------------------------
    QString buttonStyle =
        "QPushButton {"
        "   background-color: #0f3460;"
        "   color: #eaf0f1;"
        "   border: none;"
        "   border-radius: 8px;"
        "   font-size: 18px;"
        "   font-weight: bold;"
        "   min-width: 50px;"
        "   min-height: 50px;"
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
        btn->setFixedSize(50, 50);

        // Connect with captured value
        connect(btn, &QPushButton::clicked, this, [this, i]() {
            onNumberPadClicked(i);
        });

        m_numberPadButtons.append(btn);
        ui->numberPadLayout->addWidget(btn);
    }

    // ------------------------------------------------------
    // Create erase/backspace button
    // ------------------------------------------------------
    QPushButton *eraseBtn = new QPushButton("⌫", ui->numberPadWidget);
    eraseBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #e17055;"
        "   color: #eaf0f1;"
        "   border: none;"
        "   border-radius: 8px;"
        "   font-size: 18px;"
        "   font-weight: bold;"
        "   min-width: 50px;"
        "   min-height: 50px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #fab1a0;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #d63031;"
        "}"
    );
    eraseBtn->setFixedSize(50, 50);
    connect(eraseBtn, &QPushButton::clicked, this, &SudokuWindow::onClearCell);
    ui->numberPadLayout->addWidget(eraseBtn);
}

void SudokuWindow::connectSignals()
{
    // ------------------------------------------------------
    // Connect toolbar buttons
    // ------------------------------------------------------
    connect(ui->newGameButton, &QPushButton::clicked, 
            this, &SudokuWindow::onNewGame);
    connect(ui->loadButton, &QPushButton::clicked, 
            this, &SudokuWindow::onLoadPuzzle);
    connect(ui->saveButton, &QPushButton::clicked, 
            this, &SudokuWindow::onSavePuzzle);
    connect(ui->solveButton, &QPushButton::clicked, 
            this, &SudokuWindow::onSolve);
    connect(ui->checkButton, &QPushButton::clicked, 
            this, &SudokuWindow::onCheck);
    connect(ui->clearButton, &QPushButton::clicked, 
            this, &SudokuWindow::onClearCell);

    // ------------------------------------------------------
    // Connect menu actions
    // ------------------------------------------------------
    connect(ui->actionNew, &QAction::triggered, 
            this, &SudokuWindow::onNewGame);
    connect(ui->actionLoad, &QAction::triggered, 
            this, &SudokuWindow::onLoadPuzzle);
    connect(ui->actionSave, &QAction::triggered, 
            this, &SudokuWindow::onSavePuzzle);
    connect(ui->actionSolve, &QAction::triggered, 
            this, &SudokuWindow::onSolve);
    connect(ui->actionCheck, &QAction::triggered, 
            this, &SudokuWindow::onCheck);
    connect(ui->actionAbout, &QAction::triggered, 
            this, &SudokuWindow::onAbout);
    connect(ui->actionExit, &QAction::triggered, 
            this, &QMainWindow::close);
}

// =================================================
// Game Logic Methods
// =================================================

void SudokuWindow::loadSamplePuzzle()
{
    // ------------------------------------------------------
    // Sample puzzle from the project specification
    // 0 represents empty cells
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
    // Load puzzle into grid cells
    // ------------------------------------------------------
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            SudokuCell *cell = m_cells[row][col];
            cell->setError(false);

            if (puzzle[row][col] != 0) {
                // Set initial puzzle values (read-only)
                cell->setValue(puzzle[row][col]);
                cell->setInitial(true);
            } else {
                // Clear user-editable cells
                cell->clearValue();
                cell->setInitial(false);
            }
        }
    }
}

void SudokuWindow::updateStatus(const QString &message)
{
    // ------------------------------------------------------
    // Update both status label and status bar
    // ------------------------------------------------------
    ui->statusLabel->setText(message);
    ui->statusbar->showMessage(message, 3000);
}

void SudokuWindow::highlightRelatedCells(int row, int col)
{
    // ------------------------------------------------------
    // Highlight cells in the same row and column
    // ------------------------------------------------------
    for (int i = 0; i < 9; ++i) {
        if (i != col) m_cells[row][i]->setHighlighted(true);
        if (i != row) m_cells[i][col]->setHighlighted(true);
    }

    // ------------------------------------------------------
    // Highlight cells in the same 3x3 box
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

void SudokuWindow::clearHighlights()
{
    // ------------------------------------------------------
    // Clear highlight and selection from all cells
    // ------------------------------------------------------
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            m_cells[row][col]->setHighlighted(false);
            m_cells[row][col]->setSelected(false);
        }
    }
}

// =================================================
// Cell Interaction Slot Implementations
// =================================================

void SudokuWindow::onCellSelected(int row, int col)
{
    // ------------------------------------------------------
    // Deselect previous cell if any
    // ------------------------------------------------------
    if (m_selectedRow >= 0 && m_selectedCol >= 0) {
        m_cells[m_selectedRow][m_selectedCol]->setSelected(false);
    }

    // ------------------------------------------------------
    // Clear all highlights and set new selection
    // ------------------------------------------------------
    clearHighlights();

    m_selectedRow = row;
    m_selectedCol = col;

    m_cells[row][col]->setSelected(true);
    highlightRelatedCells(row, col);

    // ------------------------------------------------------
    // Update status message
    // ------------------------------------------------------
    QString status = QString("Selected cell: Row %1, Column %2")
                         .arg(row + 1).arg(col + 1);
    if (m_cells[row][col]->isInitial()) {
        status += " (fixed)";
    }
    updateStatus(status);
}

void SudokuWindow::onCellValueChanged(int row, int col, int value)
{
    // ------------------------------------------------------
    // Placeholder for validation logic
    // Will be implemented with the solver module
    // ------------------------------------------------------
    Q_UNUSED(row)
    Q_UNUSED(col)
    Q_UNUSED(value)
}

void SudokuWindow::onNumberPadClicked(int number)
{
    // ------------------------------------------------------
    // Check if a cell is selected
    // ------------------------------------------------------
    if (m_selectedRow >= 0 && m_selectedCol >= 0) {
        SudokuCell *cell = m_cells[m_selectedRow][m_selectedCol];

        if (!cell->isInitial()) {
            cell->setValue(number);
            updateStatus(QString("Placed %1 at Row %2, Column %3")
                             .arg(number)
                             .arg(m_selectedRow + 1)
                             .arg(m_selectedCol + 1));
        } else {
            updateStatus("Cannot modify initial puzzle cells!");
        }
    } else {
        updateStatus("Please select a cell first!");
    }
}

// =================================================
// Game Action Slot Implementations
// =================================================

void SudokuWindow::onNewGame()
{
    // ------------------------------------------------------
    // Reset the game with sample puzzle
    // ------------------------------------------------------
    loadSamplePuzzle();
    m_selectedRow = -1;
    m_selectedCol = -1;
    clearHighlights();
    updateStatus("New game started! Select a cell to begin.");
}

void SudokuWindow::onLoadPuzzle()
{
    // ------------------------------------------------------
    // Open file dialog to load puzzle
    // ------------------------------------------------------
    QString filename = QFileDialog::getOpenFileName(this,
        "Load Puzzle", "", "Sudoku Files (*.txt *.sudoku);;All Files (*)");

    if (!filename.isEmpty()) {
        updateStatus("Load functionality will be implemented with the solver.");
    }
}

void SudokuWindow::onSavePuzzle()
{
    // ------------------------------------------------------
    // Open file dialog to save puzzle
    // ------------------------------------------------------
    QString filename = QFileDialog::getSaveFileName(this,
        "Save Puzzle", "", "Sudoku Files (*.txt *.sudoku);;All Files (*)");

    if (!filename.isEmpty()) {
        updateStatus("Save functionality will be implemented with the solver.");
    }
}

void SudokuWindow::onSolve()
{
    // ------------------------------------------------------
    // Placeholder for auto-solve functionality
    // ------------------------------------------------------
    updateStatus("Solve functionality will be implemented in the next step.");
    QMessageBox::information(this, "Solve",
        "The automatic solver will be implemented in the next step.\n"
        "It will use a backtracking algorithm to solve the puzzle.");
}

void SudokuWindow::onCheck()
{
    // ------------------------------------------------------
    // Placeholder for solution validation
    // ------------------------------------------------------
    updateStatus("Check functionality will be implemented with the solver.");
    QMessageBox::information(this, "Check",
        "The validation check will be implemented in the next step.\n"
        "It will verify if the current state is valid.");
}

void SudokuWindow::onClearCell()
{
    // ------------------------------------------------------
    // Clear the currently selected cell
    // ------------------------------------------------------
    if (m_selectedRow >= 0 && m_selectedCol >= 0) {
        SudokuCell *cell = m_cells[m_selectedRow][m_selectedCol];

        if (!cell->isInitial()) {
            cell->clearValue();
            updateStatus(QString("Cleared cell at Row %1, Column %2")
                             .arg(m_selectedRow + 1)
                             .arg(m_selectedCol + 1));
        } else {
            updateStatus("Cannot clear initial puzzle cells!");
        }
    } else {
        updateStatus("Please select a cell first!");
    }
}

void SudokuWindow::onAbout()
{
    // ------------------------------------------------------
    // Show about dialog
    // ------------------------------------------------------
    QMessageBox::about(this, "About Sudoku",
        "<h2>Sudoku Game</h2>"
        "<p>A modern Sudoku puzzle game built with Qt.</p>"
        "<p><b>Features:</b></p>"
        "<ul>"
        "<li>Interactive 9×9 grid</li>"
        "<li>Number pad for easy input</li>"
        "<li>Keyboard support</li>"
        "<li>Cell highlighting</li>"
        "<li>Save/Load puzzles</li>"
        "<li>Automatic solver</li>"
        "</ul>"
        "<p>© 2025 Sudoku Project</p>");
}
