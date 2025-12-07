/**
 * @file main.cpp
 * @brief Entry point for Sudoku Qt application
 *
 * This file initializes the Qt application framework and launches the
 * main Sudoku game window.
 *
 * @author Salah-Eldin Hassen
 * @date December 2025
 * @version 1.0
 * @project Sudoku Game - SW Diploma
 */

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
