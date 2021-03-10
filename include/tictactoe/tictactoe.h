#pragma once

#include <string>
#include <vector>

namespace tictactoe {

using std::string;
using std::vector;

/**
 * This enumeration specifies the possible results of the evaluation of a
 * Tic-Tac-Toe board.
 */
enum class BoardState {
  NoWinner,
  Xwins,
  Owins,
  UnreachableState,
};

/**
 * This class can store a Tic-Tac-Toe board and evaluate its state.
 */
class Board {
 public:
  /**
   * Constructs a Board from a string consisting of 9 characters in row-major
   * order (i.e. the first three characters specify the first row).
   *
   * An 'X' or 'x' represents that the corresponding square is filled with an X,
   * an 'O' or 'o' represents that the corresponding square is filled with an O,
   * and any other character represents that the corresponding square is empty.
   *
   * This method throws a std::invalid_argument exception if the string provided
   * is not a valid board.
   */
  Board(const std::string& board);

  /**
   * Evaluates the state of the board.
   */
  BoardState EvaluateBoard() const;

 private:
  /**
   * Represents TicTacToe Board as a String.
   */
  string specific_board_;

  /**
   * Length of a TicTacToe Board (should always be 3).
   */
  int board_side_length_;

  /**
   * Using specific_board_, this method converts/fills a 2D vector with board
   * values.
   * @return 2D char vector
   */
  vector<vector<char>> FillGameBoard() const;

  /**
   * Checks if there is a winner horizontally.
   * @param vector
   * @return corresponding BoardState
   */
  BoardState CheckHorizontal(vector<vector<char>> game_board) const;

  /**
   * Checks if there is a winner vertically.
   * @param vector
   * @return corresponding BoardState
   */
  BoardState CheckVertical(vector<vector<char>> game_board) const;

  /**
   * Checks if there is a winner diagonally from top left to bottom right.
   * @param vector
   * @return corresponding BoardState
   */
  BoardState CheckDiagonalTopLeftToBottomRight(vector<vector<char>> game_board) const;

  /**
   * Checks if there is a winner diagonally from top right to bottom left.
   * @param vector
   * @return corresponding BoardState
   */
  BoardState CheckDiagonalTopRightToBottomLeft(vector<vector<char>> game_board) const;
};

}
