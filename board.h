#pragma once
#ifndef DELTAS_CHESS_BOARD_H
#define DELTAS_CHESS_BOARD_H

#include <tuple>
#include <array>
#include <vector>
#include <cstdint>
#include <memory>
#include <ranges>
#include <algorithm>

#include "code_utils.h"
#include "pieces.h"
#include "moves.h"

NAMESPACE_DDDELTA_START
using MovementMap_t = std::array<std::array<std::unique_ptr<PossibleMovement>, 8>, 8>;
using ChessBoard_t = std::array<std::array<Piece, 8>, 8>;


class Board {
public:
    Board();

    [[nodiscard]] inline
    Piece& get_piece(BoardCoor co)
        { return this->_board[co.x - 1][co.y - 1]; }

    [[nodiscard]] inline
    Piece& get_piece(std::uint8_t x, std::uint8_t y)
        { return this->_board[x - 1][y - 1]; }

    [[nodiscard]] inline
    const Piece& get_piece(BoardCoor co) const
        { return this->_board[co.x - 1][co.y - 1]; }

    [[nodiscard]] inline
    const Piece& get_piece(std::uint8_t x, std::uint8_t y) const
        { return this->_board[x - 1][y - 1]; }

    [[nodiscard]] inline
    const PossibleMovement* get_move(BoardCoor co) const
        { return this->_movement_map[co.x - 1][co.y - 1].get(); }

    [[nodiscard]] inline
    const PossibleMovement* get_move(std::uint8_t x, std::uint8_t y) const
        { return this->_movement_map[x - 1][y - 1].get(); }

    [[nodiscard]] inline
    ChessBoard_t& get_board()
        { return this->_board; }

    [[nodiscard]] inline
    const ChessBoard_t& get_board() const
        { return this->_board; }

    void set_up();
    void reset();

private:
    PossibleMovement* _pawn_move(BoardCoor co) const;
    PossibleMovement* _knight_move(BoardCoor co) const;
    PossibleMovement* _bishop_move(BoardCoor co) const;
    PossibleMovement* _rook_move(BoardCoor co) const;
    PossibleMovement* _queen_move(BoardCoor co) const;
    PossibleMovement* _king_move(BoardCoor co) const;


    ChessBoard_t _board;
    MovementMap_t _movement_map;
    std::vector<Piece> _captured_white;
    std::vector<Piece> _captured_black;
    std::uint16_t _white_lost_val;
    std::uint16_t _black_lost_val;
};
NAMESPACE_DDDELTA_END
#endif //DELTAS_CHESS_BOARD_H
