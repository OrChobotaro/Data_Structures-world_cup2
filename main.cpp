
#include "worldcup23a2.h"

int main(){


    world_cup_t wc;
    wc.add_team(1);
    wc.add_team(2);
    wc.add_team(3);
    wc.add_team(4);


    wc.add_player(11, 1, permutation_t::read("1,2,3,4,5"), 4, 5, 2, false);
    wc.add_player(12, 1, permutation_t::read("2,3,5,4,1"), 4, 5, 2, false);
    wc.add_player(13, 1, permutation_t::read("3,1,4,2,5"), 4, 5, 2, false);
    wc.add_player(14, 2, permutation_t::read("5,4,2,1,3"), 4, 5, 2, false);
    wc.add_player(15, 2, permutation_t::read("2,1,3,4,5"), 4, 5, 2, false);

    output_t<permutation_t> per1 = wc.get_partial_spirit(11);
    std::cout << "player1 permutation: ";
    std::cout << permutation_t::read("1,2,3,4,5") << std::endl;

    std::cout << per1.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per2 = wc.get_partial_spirit(12);
    permutation_t partial_2 = permutation_t::read("2,3,5,4,1") * per1.ans();
    std::cout << "player2 permutation: " << partial_2 << std::endl;
    std::cout << per2.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per3 = wc.get_partial_spirit(13);
    permutation_t partial_3 = permutation_t::read("3,1,4,2,5") * per1.ans();/// fix
    std::cout << "player3 permutation: " << partial_3 << std::endl;
    std::cout << per3.ans() << std::endl;

    std::cout << "---------------------" << std::endl;


    output_t<permutation_t> per4 = wc.get_partial_spirit(14);
    std::cout << "player4 permutation: ";
    std::cout << permutation_t::read("5,4,2,1,3") << std::endl;
    std::cout << per4.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per5 = wc.get_partial_spirit(15);
    permutation_t partial_5 = permutation_t::read("2,1,3,4,5") * per4.ans();
    std::cout << "player5 permutation: " << partial_5 << std::endl;
    std::cout << per5.ans() << std::endl;


    std::cout << "---------------------" << std::endl;


    wc.buy_team(1, 2);

    output_t<permutation_t> per1ABT = wc.get_partial_spirit(11);
    permutation_t partial_1ABT = permutation_t::read("1,2,3,4,5");
    std::cout << "player1 permutation: " << partial_1ABT << std::endl;
    std::cout << per1ABT.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per2ABT = wc.get_partial_spirit(12);
    permutation_t partial_2ABT = permutation_t::read("2,3,5,4,1") * partial_1ABT;
    std::cout << "player2 permutation: " << partial_2ABT << std::endl;
    std::cout << per2ABT.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per3ABT = wc.get_partial_spirit(13);
    permutation_t partial_3ABT = permutation_t::read("3,1,4,2,5") * partial_2ABT;
    std::cout << "player3 permutation: " << partial_3ABT << std::endl;
    std::cout << per3ABT.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per4ABT = wc.get_partial_spirit(14);
    permutation_t partial_4ABT = permutation_t::read("5,4,2,1,3") * partial_3ABT;
    std::cout << "player4 permutation: ";
    std::cout << permutation_t::read("5,4,2,1,3") << std::endl;
    std::cout << per4ABT.ans() << std::endl;


}



#include "worldcup23a2.h"
#include "stdio.h"

int main() {
    world_cup_t wc;
    wc.add_team(1);
    wc.add_team(2);
    wc.add_team(3);
    wc.add_team(4);


    wc.add_player(11, 1, permutation_t::read("1,2,3,4,5"), 4, 5, 2, false);
    wc.add_player(12, 1, permutation_t::read("2,3,5,4,1"), 4, 5, 2, false);
    wc.add_player(13, 1, permutation_t::read("3,1,4,2,5"), 4, 5, 2, false);
    wc.add_player(14, 2, permutation_t::read("5,4,2,1,3"), 4, 5, 2, false);
    wc.add_player(15, 2, permutation_t::read("2,1,3,4,5"), 4, 5, 2, false);

    output_t<permutation_t> per1 = wc.get_partial_spirit(11);
    std::cout << "player1 permutation: ";
    std::cout << permutation_t::read("1,2,3,4,5") << std::endl;

    std::cout << per1.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per2 = wc.get_partial_spirit(12);
    permutation_t partial_2 = permutation_t::read("2,3,5,4,1") * per1.ans();
    std::cout << "player2 permutation: " << partial_2 << std::endl;
    std::cout << per2.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per3 = wc.get_partial_spirit(13);
    permutation_t partial_3 = permutation_t::read("3,1,4,2,5") * partial_2;
    std::cout << "player3 permutation: " << partial_3 << std::endl;
    std::cout << per3.ans() << std::endl;

    std::cout << "---------------------" << std::endl;


    output_t<permutation_t> per4 = wc.get_partial_spirit(14);
    std::cout << "player4 permutation: ";
    std::cout << permutation_t::read("5,4,2,1,3") << std::endl;
    std::cout << per4.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per5 = wc.get_partial_spirit(15);
    permutation_t partial_5 = permutation_t::read("2,1,3,4,5") * per4.ans();
    std::cout << "player5 permutation: " << partial_5 << std::endl;
    std::cout << per5.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    wc.buy_team(1, 2);

    output_t<permutation_t> per1ABT = wc.get_partial_spirit(11);
    permutation_t partial_1ABT = permutation_t::read("1,2,3,4,5");
    std::cout << "player1 permutation: " << partial_1ABT << std::endl;
    std::cout << per1ABT.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per2ABT = wc.get_partial_spirit(12);
    permutation_t partial_2ABT = permutation_t::read("2,3,5,4,1") * partial_1ABT;
    std::cout << "player2 permutation: " << partial_2ABT << std::endl;
    std::cout << per2ABT.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per3ABT = wc.get_partial_spirit(13);
    permutation_t partial_3ABT = permutation_t::read("3,1,4,2,5") * partial_2ABT;
    std::cout << "player3 permutation: " << partial_3ABT << std::endl;
    std::cout << per3ABT.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per4ABT = wc.get_partial_spirit(14);
    permutation_t partial_4ABT = permutation_t::read("5,4,2,1,3") * partial_3ABT;
    std::cout << "player4 permutation: ";
    std::cout << permutation_t::read("5,4,2,1,3") << std::endl;
    std::cout << per4ABT.ans() << std::endl;

    std::cout << "---------------------" << std::endl;


    output_t<permutation_t> per5ABT = wc.get_partial_spirit(15);
    permutation_t partial_5ABT = permutation_t::read("2,1,3,4,5") * partial_4ABT;
    std::cout << "player5 permutation: " << partial_5 << std::endl;
    std::cout << per5ABT.ans() << std::endl;

    std::cout << "---------------------" << std::endl;



    return 0;

}
