// =================================================
// SudokuCell.h
// Custom QLineEdit widget representing a single Sudoku cell
// Handles cell-specific styling, input validation, and events
// =================================================

#ifndef SUDOKUCELL_H
#define SUDOKUCELL_H

#include <QLineEdit>

// =================================================
// SudokuCell Class Declaration
// A specialized QLineEdit for Sudoku grid cells
// =================================================

class SudokuCell : public QLineEdit
{
    Q_OBJECT

public:
    // =================================================
    // Constructor & Destructor
    // =================================================
    
    /**
     * @brief Constructs a SudokuCell at the specified grid position
     * @param row Row index (0-8)
     * @param col Column index (0-8)
     * @param parent Parent widget
     */
    explicit SudokuCell(int row, int col, QWidget *parent = nullptr);
    ~SudokuCell() = default;

    // =================================================
    // Getters - Cell Position
    // =================================================
    
    int row() const { return m_row; }
    int col() const { return m_col; }

    // =================================================
    // Cell State Management
    // =================================================
    
    /**
     * @brief Marks cell as an initial puzzle value (read-only)
     * @param initial True if cell is part of original puzzle
     */
    void setInitial(bool initial);
    bool isInitial() const { return m_initial; }

    /**
     * @brief Highlights cell (for row/column/box indication)
     * @param highlighted True to highlight
     */
    void setHighlighted(bool highlighted);

    /**
     * @brief Marks cell as having an error (invalid value)
     * @param error True if cell has error
     */
    void setError(bool error);

    /**
     * @brief Marks cell as currently selected
     * @param selected True if cell is selected
     */
    void setSelected(bool selected);

    // =================================================
    // Value Management
    // =================================================
    
    /**
     * @brief Gets the numeric value of the cell
     * @return Value 1-9, or 0 if empty
     */
    int value() const;

    /**
     * @brief Sets the cell value
     * @param val Value to set (1-9), 0 or invalid clears cell
     */
    void setValue(int val);

    /**
     * @brief Clears the cell value (if not initial)
     */
    void clearValue();

signals:
    // =================================================
    // Signals
    // =================================================
    
    /**
     * @brief Emitted when cell receives focus
     */
    void cellSelected(int row, int col);

    /**
     * @brief Emitted when cell value changes
     */
    void cellValueChanged(int row, int col, int value);

protected:
    // =================================================
    // Event Handlers
    // =================================================
    
    void focusInEvent(QFocusEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    // =================================================
    // Private Members
    // =================================================
    
    int m_row;          // Row position (0-8)
    int m_col;          // Column position (0-8)
    bool m_initial;     // Is this an initial puzzle value?
    bool m_highlighted; // Is this cell highlighted?
    bool m_error;       // Does this cell have an error?
    bool m_selected;    // Is this cell currently selected?

    // =================================================
    // Private Methods
    // =================================================
    
    /**
     * @brief Updates cell stylesheet based on current state
     */
    void updateStyle();
};

#endif // SUDOKUCELL_H
