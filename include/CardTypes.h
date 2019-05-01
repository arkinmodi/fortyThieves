/**
 *  \file CardTypes.h
 *  \author Arkin Modi
 *  \brief The special types that will be used
 *  \date March 12, 2019
 */
#ifndef A3_CARD_TYPES_H_
#define A3_CARD_TYPES_H_

/**
 *  \brief Describes the rank of a card.
 */
typedef unsigned short int RankT;

/**
 *  \brief RankT for an Ace.
 */
#define ACE 1

/**
 *  \brief RankT for an Jack.
 */
#define JACK 11

/**
 *  \brief RankT for a Queen.
 */
#define QUEEN 12

/**
 *  \brief RankT for a King.
 */
#define KING 13

/**
 *  \brief Number of total cards.
 */
#define TOTAL_CARDS 104

/**
 *  \brief Describes the suit of a card.
 */
enum SuitT
{
    Heart,
    Diamond,
    Club,
    Spade
};

/**
 *  \brief Describes the category the card is in.
 */
enum CategoryT
{
    Tableau,
    Foundation,
    Deck,
    Waste
};

/**
 *  \brief Describes a card.
 */
struct CardT
{
    SuitT s;
    RankT r;
};

#endif
