/**
 *  \file GameBoard.h
 *  \author Arkin Modi
 *  \brief The Forty Thieves GameBoard ADT
 *  \date March 20, 2019
 */

#ifndef A3_GAME_BOARD_H_
#define A3_GAME_BOARD_H_

#include "CardTypes.h"
#include "CardStack.h"
#include <vector>
#include <functional>

/**
 *  \brief Class representing a GameBoard
 */

class BoardT
{
private:
  std::vector<CardStackT> T; // Tableau
  std::vector<CardStackT> F; // Foundation
  CardStackT D;              // Deck
  CardStackT W;              // Waste

  bool two_decks(std::vector<CardStackT> T, std::vector<CardStackT> F, CardStackT D, CardStackT W);
  int cnt_cards_seq(std::vector<CardStackT> S, std::function<bool(CardT)> f);
  int cnt_cards_stack(CardStackT s, std::function<bool(CardT)> f);
  int cnt_cards(std::vector<CardStackT> T, std::vector<CardStackT> F, CardStackT D, CardStackT W, std::function<bool(CardT)> f);
  std::vector<CardStackT> init_seq(unsigned int n);
  std::vector<CardStackT> tab_deck(std::vector<CardT> deck);
  bool is_valid_pos(CategoryT c, unsigned int n);
  bool valid_tab_tab(unsigned int n0, unsigned int n1);
  bool valid_tab_foundation(unsigned int n0, unsigned int n1);
  bool valid_waste_tab(unsigned int n);
  bool valid_waste_foundation(unsigned int n);
  bool tab_placeable(CardT c, CardT d);
  bool foundation_placeable(CardT c, CardT d);

public:
  /**
     *  \brief Constructs a new GameBoard
     *  \param deck The deck of cards used in Forty Thieves (2 * 52 card decks)
     */
  BoardT(std::vector<CardT> deck);

  /**
     *  \brief Checks if the card move from the Tableau is valid
     *  \param c The category that the destination is in
     *  \param n0 The card in Tableau that is to be moved
     *  \param n1 The location in the destination that the card to be moved to
     *  \return Boolean representing is the move is valid
     */
  bool is_valid_tab_mv(CategoryT c, unsigned int n0, unsigned int n1);

  /**
     *  \brief Checks if the card move from the Waste is valid
     *  \param c The category that the destination is in
     *  \param n The location in the destination that the card to be moved to
     *  \return Boolean representing is the move is valid
     */
  bool is_valid_waste_mv(CategoryT c, unsigned int n);

  /**
     *  \brief Checks if the card move from the Deck to Waste is valid
     *  \return Boolean representing is the move is valid
     */
  bool is_valid_deck_mv();

  /**
     *  \brief Moves the card from the Tableau to the destination
     *  \param c The category that the destination is in
     *  \param n0 The card in Tableau that is to be moved
     *  \param n1 The location in the destination that the card to be moved to
     */
  void tab_mv(CategoryT c, unsigned int n0, unsigned int n1);

  /**
     *  \brief Moves the card from the Waste to the destination
     *  \param c The category that the destination is in
     *  \param n0 The card in Tableau that is to be moved
     *  \param n1 The location in the destination that the card to be moved to
     */
  void waste_mv(CategoryT c, unsigned int n);

  /**
     *  \brief Moves the card from the Deck to the Waste
     */
  void deck_mv();

  /**
     *  \brief Gets one of the card stack in the Tableau
     *  \param i The specific stack of cards in the sequence of stack in Tableau
     *  \return The card stack in the Tableau
     */
  CardStackT get_tab(unsigned int i);

  /**
     *  \brief Gets one of the card stack in the Foundation
     *  \param i The specific stack of cards in the sequence of stack in Foundation
     *  \return The card stack in the Foundation
     */
  CardStackT get_foundation(unsigned int i);

  /**
     *  \brief Gets the card stack in the Deck
     *  \return The card stack in the Deck
     */
  CardStackT get_deck();

  /**
     *  \brief Gets the card stack in the Waste
     *  \return The card stack in the Waste
     */
  CardStackT get_waste();

  /**
     *  \brief Checks if a valid move exists
     *  \return Boolean representing if a valid move exists
     */
  bool valid_mv_exists();

  /**
     *  \brief Checks if you have won the game
     *  \return Boolean representing if you have won the game
     */
  bool is_win_state();
};
#endif
