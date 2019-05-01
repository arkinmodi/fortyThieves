#include "GameBoard.h"
#include "Stack.h"
#include "CardStack.h"
#include "CardTypes.h"

#include <functional>
#include <stdexcept>

using namespace std;

/********************************** PUBLIC ***********************************/

BoardT::BoardT(vector<CardT> deck)
{
    if (not(two_decks(init_seq(10), init_seq(8), CardStackT(deck), CardStackT())))
    {
        throw invalid_argument("BoardT: invalid_argument");
    }

    vector<CardT> T(deck.begin(), deck.begin() + 40);
    vector<CardT> D(deck.begin() + 40, deck.end());
    this->T = tab_deck(T);
    this->F = init_seq(8);
    this->D = CardStackT(D);
    this->W = CardStackT();
};

bool BoardT::is_valid_tab_mv(CategoryT c, unsigned int n0, unsigned int n1)
{
    if (c == Tableau)
    {
        if (not(is_valid_pos(Tableau, n0) && is_valid_pos(Tableau, n1)))
        {
            throw out_of_range("is_valid_tab_mv: out_of_range");
        }
        return valid_tab_tab(n0, n1);
    }
    else if (c == Foundation)
    {
        if (not(is_valid_pos(Tableau, n0) && is_valid_pos(Foundation, n1)))
        {
            throw out_of_range("is_valid_tab_mv: out_of_range");
        }
        return valid_tab_foundation(n0, n1);
    }
    return false;
};

bool BoardT::is_valid_waste_mv(CategoryT c, unsigned int n)
{
    if (this->W.size() == 0)
    {
        throw invalid_argument("is_valid_waste_mv: invalid_argument");
    }
    else if (c == Tableau)
    {
        if (not(is_valid_pos(Tableau, n)))
        {
            throw out_of_range("is_valid_waste_mv: out_of_range");
        }
        return valid_waste_tab(n);
    }
    else if (c == Foundation)
    {
        if (not(is_valid_pos(Foundation, n)))
        {
            throw out_of_range("is_valid_waste_mv: out_of_range");
        }
        return valid_waste_foundation(n);
    }
    return false;
};

bool BoardT::is_valid_deck_mv()
{
    return this->D.size() > 0;
};

void BoardT::tab_mv(CategoryT c, unsigned int n0, unsigned int n1)
{
    if (not(is_valid_tab_mv(c, n0, n1)))
    {
        throw invalid_argument("tab_mv: invalid_argument");
    }
    else if (c == Tableau)
    {
        this->T[n1] = this->T[n1].push(this->T[n0].top());
        this->T[n0] = this->T[n0].pop();
    }
    else if (c == Foundation)
    {
        this->F[n1] = this->F[n1].push(this->T[n0].top());
        this->T[n0] = this->T[n0].pop();
    }
};

void BoardT::waste_mv(CategoryT c, unsigned int n)
{
    if (not(is_valid_waste_mv(c, n)))
    {
        throw invalid_argument("waste_mv: invalid_argument");
    }
    else if (c == Tableau)
    {
        this->T[n] = this->T[n].push(this->W.top());
        this->W = this->W.pop();
    }
    else if (c == Foundation)
    {
        this->F[n] = this->F[n].push(this->W.top());
        this->W = this->W.pop();
    }
};

void BoardT::deck_mv()
{
    if (not(is_valid_deck_mv()))
    {
        throw invalid_argument("deck_mv: invalid_argument");
    }
    this->W = this->W.push(this->D.top());
    this->D = this->D.pop();
};

CardStackT BoardT::get_tab(unsigned int i)
{
    if (not(is_valid_pos(Tableau, i)))
    {
        throw out_of_range("get_tab: out_of_range");
    }
    return this->T[i];
};

CardStackT BoardT::get_foundation(unsigned int i)
{
    if (not(is_valid_pos(Foundation, i)))
    {
        throw out_of_range("get_foundation: out_of_range");
    }
    return this->F[i];
};

CardStackT BoardT::get_deck()
{
    return this->D;
};

CardStackT BoardT::get_waste()
{
    return this->W;
};

bool BoardT::valid_mv_exists()
{
    if (is_valid_deck_mv())
    {
        return true;
    }

    bool valid_tab_mv = false;
    bool valid_waste_mv = false;

    for (int c = 0; c < 2; c++)
    {
        for (int n0 = 0; n0 < 104; n0++)
        {
            if (not(is_valid_pos(Tableau, n0)))
            {
                continue;
            }
            for (int n1 = 0; n1 < 104; n1++)
            {
                if (not(is_valid_pos(static_cast<CategoryT>(c), n1)))
                {
                    continue;
                }
                valid_tab_mv = is_valid_tab_mv(static_cast<CategoryT>(c), n0, n1);
                if (valid_tab_mv)
                {
                    return true;
                }
            }
        }
    }

    for (int c = 0; c < 2; c++)
    {
        for (int n = 0; n < 104; n++)
        {
            if (not(is_valid_pos(static_cast<CategoryT>(c), n)))
            {
                continue;
            }
            valid_waste_mv = is_valid_waste_mv(static_cast<CategoryT>(c), n);
            if (valid_waste_mv)
            {
                return true;
            }
        }
    }
    return false;
};

bool BoardT::is_win_state()
{
    for (int i = 0; i < 8; i++)
    {
        if (not(this->F[i].size() > 0 && this->F[i].top().r == KING))
        {
            return false;
        }
    }
    return true;
};

/********************************** PRIVATE **********************************/

bool BoardT::two_decks(vector<CardStackT> T, vector<CardStackT> F, CardStackT D, CardStackT W)
{
    for (RankT rk = ACE; rk <= KING; rk++)
    {
        for (unsigned int st = 0; st < 4; st++)
        {
            function<bool(CardT)> f = [&](CardT c) -> bool { return c.r == rk && c.s == st; };
            if (cnt_cards(T, F, D, W, f) != 2)
            {
                return false;
            };
        }
    }
    return true;
};

int BoardT::cnt_cards_seq(vector<CardStackT> S, function<bool(CardT)> f)
{
    int counter = 0;
    for (auto cards : S)
    {
        counter += cnt_cards_stack(cards, f);
    }
    return counter;
};

int BoardT::cnt_cards_stack(CardStackT s, function<bool(CardT)> f)
{
    int counter = 0;
    for (auto card : s.toSeq())
    {
        if (f(card))
        {
            counter++;
        };
    }
    return counter;
};

int BoardT::cnt_cards(vector<CardStackT> T, vector<CardStackT> F, CardStackT D, CardStackT W, function<bool(CardT)> f)
{
    return cnt_cards_seq(T, f) + cnt_cards_seq(F, f) + cnt_cards_stack(D, f) + cnt_cards_stack(W, f);
};

vector<CardStackT> BoardT::init_seq(unsigned int n)
{
    vector<CardStackT> s;
    for (unsigned int i = 0; i < n; i++)
    {
        CardStackT temp = CardStackT();
        s.push_back(temp);
    }
    return s;
};

vector<CardStackT> BoardT::tab_deck(vector<CardT> deck)
{
    vector<CardStackT> T;
    for (int i = 0; i <= 10; i++)
    {
        vector<CardT> temp;
        for (int j = 4 * i; j < 4 * (i + 1); j++)
        {
            temp.push_back(deck[j]);
        }
        T.push_back(temp);
    }
    return T;
};

bool BoardT::is_valid_pos(CategoryT c, unsigned int n)
{
    if (c == Tableau)
    {
        return n >= 0 && n <= 9;
    }
    else if (c == Foundation)
    {
        return n >= 0 && n <= 7;
    }
    return true;
};

bool BoardT::valid_tab_tab(unsigned int n0, unsigned int n1)
{
    if (this->T[n0].size() == 0)
    {
        return false;
    }
    else if (this->T[n0].size() > 0)
    {
        if (this->T[n1].size() == 0)
        {
            return true;
        }
        else if (this->T[n1].size() > 0)
        {
            return tab_placeable(this->T[n0].top(), this->T[n1].top());
        }
    }
    return false;
};

bool BoardT::valid_tab_foundation(unsigned int n0, unsigned int n1)
{
    if (this->T[n0].size() == 0)
    {
        return false;
    }
    else if (this->T[n0].size() > 0)
    {
        if (this->F[n1].size() == 0)
        {
            return this->T[n0].top().r == ACE;
        }
        else if (this->F[n1].size() > 0)
        {
            return foundation_placeable(this->T[n0].top(), this->F[n1].top());
        }
    }
    return false;
};

bool BoardT::valid_waste_tab(unsigned int n)
{
    if (this->T[n].size() == 0)
    {
        return true;
    }
    else if (this->T[n].size() > 0)
    {
        return tab_placeable(this->W.top(), this->T[n].top());
    }
    return false;
};

bool BoardT::valid_waste_foundation(unsigned int n)
{
    if (this->F[n].size() == 0)
    {
        return this->W.top().r == ACE;
    }
    else if (this->F[n].size() > 0)
    {
        return foundation_placeable(this->W.top(), this->F[n].top());
    }
    return false;
};

bool BoardT::tab_placeable(CardT c, CardT d)
{
    return c.s == d.s && c.r == (d.r - 1);
};

bool BoardT::foundation_placeable(CardT c, CardT d)
{
    return c.s == d.s && c.r == (d.r + 1);
};