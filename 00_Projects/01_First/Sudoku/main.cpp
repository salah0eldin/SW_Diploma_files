// =================================================
// main.cpp
// Entry point for Sudoku Qt application
// =================================================

#include "SudokuGame.hpp"
#include <QApplication>

// =================================================
// Main Function
// =================================================

int main(int argc, char *argv[])
{
    // ------------------------------------------------------
    // Create Qt application instance
    // ------------------------------------------------------
    QApplication app(argc, argv);
    
    // ------------------------------------------------------
    // Set application metadata
    // ------------------------------------------------------
    QApplication::setApplicationName("Sudoku");
    QApplication::setApplicationVersion("1.0");
    QApplication::setOrganizationName("SW Diploma");

    // ------------------------------------------------------
    // Create and show main game window
    // ------------------------------------------------------
    SudokuGame gameWindow;
    gameWindow.show();

    // ------------------------------------------------------
    // Start event loop
    // ------------------------------------------------------
    return app.exec();
}
