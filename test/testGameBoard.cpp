#include "catch.h"
#include "GameBoard.h"

TEST_CASE("tests for GameBoard", "[GameBoard]") {
    std::vector<CardT> d;
    for (RankT rank = ACE; rank <= KING; rank++) {
        for (unsigned int suit = 0; suit < 4; suit++) {
        CardT n = { static_cast<SuitT>(suit), rank };
        d.push_back(n);
        d.push_back(n);
        }
    }
    BoardT board(d);

    SECTION("exception test for BoardT") {
        std::vector<CardT> deck = {};
        REQUIRE_THROWS_AS(BoardT(deck), std::invalid_argument);
    }

    SECTION("general test for is_valid_tab_mv") {
        REQUIRE(board.is_valid_tab_mv(Foundation, 0, 0));
        REQUIRE_FALSE(board.is_valid_tab_mv(Waste, 0, 0));
    }

    SECTION("exception test for is_valid_tab_mv") {
        REQUIRE_THROWS_AS(board.is_valid_tab_mv(Foundation, 104, 0), std::out_of_range);
    }

    SECTION("general tests for is_valid_waste_mv") {
        board.deck_mv();    // Spade KING now in waste
        REQUIRE_FALSE(board.is_valid_waste_mv(Tableau, 0));
        REQUIRE_FALSE(board.is_valid_waste_mv(Foundation, 0));
        REQUIRE_FALSE(board.is_valid_waste_mv(Deck, 0));
    }

    SECTION("exception tests for is_valid_waste_mv") {
        REQUIRE_THROWS_AS(board.is_valid_waste_mv(Tableau, 0), std::invalid_argument);
        board.deck_mv();    // Spade KING now in waste
        REQUIRE_THROWS_AS(board.is_valid_waste_mv(Tableau, 104), std::out_of_range);
    }

    SECTION("general test for is_valid_deck_mv") {
        REQUIRE(board.is_valid_deck_mv());
        for(int i = 0; i < 104-40; i++) {board.deck_mv();};
        REQUIRE_FALSE(board.is_valid_deck_mv());
    }

    SECTION("general test for tab_mv") {
        unsigned int initSize = board.get_tab(0).size();
        board.tab_mv(Foundation, 0, 0);
        REQUIRE(board.get_foundation(0).top().r == ACE);
        REQUIRE(board.get_tab(0).size() == initSize-1);
    }
    
    SECTION("exception test for tab_mv") {
        // Try to move a 2 to Foundation
        REQUIRE_THROWS_AS(board.tab_mv(Foundation, 9, 0), std::invalid_argument);
    }

    SECTION("general test for waste_mv") {
        for(int i = 0; i < 4; i++) {board.tab_mv(Foundation, 0, i);}
        board.deck_mv();
        unsigned int initSize = board.get_waste().size();
        board.waste_mv(Tableau, 0);
        REQUIRE((
                board.get_tab(0).top().r == KING
            &&  board.get_tab(0).top().s == Spade
            ));
        REQUIRE(board.get_waste().size() == initSize-1);
    }

    SECTION("exception tests for waste_mv") {
        REQUIRE_THROWS_AS(board.waste_mv(Tableau, 0), std::invalid_argument);
        board.deck_mv();
        REQUIRE_THROWS_AS(board.waste_mv(Tableau, 0), std::invalid_argument);
    }

    SECTION("general test for deck_mv") {
        unsigned int initSizeDeck = board.get_deck().size();
        unsigned int initSizeWaste = board.get_waste().size();
        REQUIRE((
                board.get_deck().top().r == KING
            &&  board.get_deck().top().s == Spade
            ));
        board.deck_mv();
        REQUIRE((
                board.get_waste().top().r == KING
            &&  board.get_waste().top().s == Spade
            ));
        REQUIRE(board.get_deck().size() == initSizeDeck-1);
        REQUIRE(board.get_waste().size() == initSizeWaste+1);
    }

    SECTION("exception test for deck_mv") {
        for(int i = 0; i < 104-40; i++) {board.deck_mv();}
        REQUIRE_THROWS_AS(board.deck_mv(), std::invalid_argument);
    }

    SECTION("general test for get_tab") {
        REQUIRE((
                board.get_tab(0).top().r == ACE
            &&  board.get_tab(0).top().s == Diamond
        ));
    }

    SECTION("exception test for get_tab") {
        REQUIRE_THROWS_AS(board.get_tab(10), std::out_of_range);
    }

    SECTION("general tests for get_foundation") {
        REQUIRE(board.get_foundation(0).size() == 0);
        board.tab_mv(Foundation, 0, 0);
        REQUIRE((
                board.get_foundation(0).top().r == ACE
            &&  board.get_foundation(0).top().s == Diamond
            &&  board.get_foundation(0).size() == 1
        ));
    }

    SECTION("exception test for get_foundation") {
        REQUIRE_THROWS_AS(board.get_foundation(8), std::out_of_range);
    }

    SECTION("general test for get_deck") {
        REQUIRE((
                board.get_deck().top().r == KING
            &&  board.get_deck().top().s == Spade
        ));
    }

    SECTION("general tests for get_waste") {
        REQUIRE(board.get_waste().size() == 0);
        board.deck_mv();
        REQUIRE((
                board.get_waste().top().r == KING
            &&  board.get_waste().top().s == Spade
            &&  board.get_waste().size() == 1
        ));
    }

    SECTION("general tests for valid_mv_exists") {
        REQUIRE(board.valid_mv_exists());

        std::vector<CardT> deck;
        for (RankT rank = KING; rank >= ACE; rank--) {
            for (unsigned int suit = 0; suit < 4; suit++) {
                CardT n = { static_cast<SuitT>(suit), rank };
                deck.push_back(n);
                deck.push_back(n);
            }
        }
        BoardT board2(deck); // same as board but deck is reversed

        REQUIRE(board2.valid_mv_exists());
    }

    SECTION("general tests for is_win_state") {
        
        REQUIRE_FALSE(board.is_win_state());

        // Moves cards from Tableau to Foundation
        for(int j = 0; j < 10; j+=2) {
            for(int i = 0; i < 4; i++) {board.tab_mv(Foundation, j, i);}
            for(int i = 4; i < 8; i++) {board.tab_mv(Foundation, j+1, i);}
        }

        // Moves cards from Deck to Waste
        for(int i = 0; i < 104-40; i++) {board.deck_mv();}

        // Moves cards from Waste to Foundation
        for(int j = 0; j < board.get_waste().size(); j++) {
            for(int i = 3; i >= 0; i--) {board.waste_mv(Foundation, i);}
            for(int i = 7; i >= 4; i--) {board.waste_mv(Foundation, i);}
        }

        REQUIRE(board.is_win_state());
    }
}