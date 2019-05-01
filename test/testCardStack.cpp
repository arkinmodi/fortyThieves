#include "catch.h"
#include "CardStack.h"

TEST_CASE("tests for CardStackT", "[CardStackT]")
{
    std::vector<CardT> d;
    for (RankT rank = ACE; rank <= KING; rank++) {
        for (unsigned int suit = 0; suit < 4; suit++) {
            CardT n = {static_cast<SuitT>(suit), rank};
            d.push_back(n);
        }
    }
    CardStackT test = CardStackT(d);

    SECTION("general test for push") {
        test = test.push(CardT {Heart, ACE});
        REQUIRE((
                test.top().r == ACE
            &&  test.top().s == Heart
            ));
    }

    SECTION("general test for pop") {
        test = test.pop();
        REQUIRE((
                test.top().r == KING
            &&  test.top().s == Club
            ));
    }

    SECTION("exception test for pop") {
        std::vector<CardT> temp1 = {};
        CardStackT temp2 = CardStackT(temp1);
        REQUIRE_THROWS_AS(temp2.pop(), std::out_of_range);
    }

    SECTION("general test for top") {
        REQUIRE((
                test.top().r == KING
            &&  test.top().s == Spade
            ));
    }

    SECTION("exception test for top") {
        std::vector<CardT> temp1 = {};
        CardStackT temp2 = CardStackT(temp1);
        REQUIRE_THROWS_AS(temp2.top(), std::out_of_range);
    }

    SECTION("general test for size") {
        REQUIRE(test.size() == 52);
    }

    SECTION("general test for toSeq") {
        REQUIRE((
                test.toSeq().back().r == KING
            &&  test.toSeq().back().s == Spade
            ));
    }
}