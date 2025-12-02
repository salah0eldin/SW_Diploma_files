// =================================================
// SudokuCell.cpp
// Implementation of the SudokuCell widget
// =================================================

#include "SudokuCell.h"

#include <QKeyEvent>
#include <QFocusEvent>
#include <QFont>

// =================================================
// Constructor
// =================================================

SudokuCell::SudokuCell(int row, int col, QWidget *parent)
    : QLineEdit(parent)
    , m_row(row)
    , m_col(col)
    , m_initial(false)
    , m_highlighted(false)
    , m_error(false)
    , m_selected(false)
{
    // ------------------------------------------------------
    // Configure cell properties
    // ------------------------------------------------------
    setMaxLength(1);
    setAlignment(Qt::AlignCenter);
    setFixedSize(48, 48);

    // ------------------------------------------------------
    // Set up font styling
    // ------------------------------------------------------
    QFont cellFont = this->font();
    cellFont.setPointSize(18);
    cellFont.setBold(true);
    setFont(cellFont);

    // ------------------------------------------------------
    // Apply initial style
    // ------------------------------------------------------
    updateStyle();

    // ------------------------------------------------------
    // Connect text change signal to emit value changes
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
    });
}

// =================================================
// Cell State Management
// =================================================

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

// =================================================
// Value Management
// =================================================

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
}

void SudokuCell::clearValue()
{
    if (!m_initial) {
        clear();
    }
}

// =================================================
// Event Handlers
// =================================================

void SudokuCell::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    emit cellSelected(m_row, m_col);
}

void SudokuCell::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    // ------------------------------------------------------
    // Allow numbers 1-9
    // ------------------------------------------------------
    if (key >= Qt::Key_1 && key <= Qt::Key_9) {
        if (!m_initial) {
            setText(QString::number(key - Qt::Key_0));
        }
        return;
    }

    // ------------------------------------------------------
    // Allow backspace and delete to clear cell
    // ------------------------------------------------------
    if (key == Qt::Key_Backspace || key == Qt::Key_Delete) {
        if (!m_initial) {
            clear();
        }
        return;
    }

    // ------------------------------------------------------
    // Allow arrow key navigation
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

// =================================================
// Style Management
// =================================================

void SudokuCell::updateStyle()
{
    // ------------------------------------------------------
    // Define base colors
    // ------------------------------------------------------
    QString bgColor = "#2d3436";
    QString textColor = "#dfe6e9";
    QString borderColor = "#636e72";

    // ------------------------------------------------------
    // Adjust colors based on cell state
    // ------------------------------------------------------
    if (m_initial) {
        textColor = "#74b9ff";  // Blue for initial values
        bgColor = "#2d3436";
    }

    if (m_highlighted) {
        bgColor = "#3d4448";    // Slightly lighter for highlights
    }

    if (m_selected) {
        bgColor = "#0984e3";    // Blue for selection
        borderColor = "#74b9ff";
    }

    if (m_error) {
        bgColor = "#d63031";    // Red for errors
        textColor = "#ffffff";
    }

    // ------------------------------------------------------
    // Calculate border widths for 3x3 box separation
    // Thicker borders separate the 3x3 boxes
    // ------------------------------------------------------
    int topBorder = 1;
    int leftBorder = 1;
    int rightBorder = 1;
    int bottomBorder = 1;

    // Top edge of 3x3 box
    if (m_row % 3 == 0) topBorder = 3;
    
    // Left edge of 3x3 box
    if (m_col % 3 == 0) leftBorder = 3;
    
    // Bottom edge of grid
    if (m_row == 8) bottomBorder = 3;
    
    // Right edge of grid
    if (m_col == 8) rightBorder = 3;
    
    // Internal 3x3 box separators
    if ((m_col + 1) % 3 == 0) rightBorder = 2;
    if ((m_row + 1) % 3 == 0) bottomBorder = 2;

    // ------------------------------------------------------
    // Build and apply stylesheet
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
