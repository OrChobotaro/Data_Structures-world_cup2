#include "worldcup23a2.h"

int main2(){

    world_cup_t wc;
    wc.add_team(1);
    wc.add_team(2);
    wc.add_team(3);
    wc.add_team(4);


    wc.add_player(11, 1, permutation_t::read("1,5,4,2,3"), 4, 5, 2, false);
    wc.add_player(12, 1, permutation_t::read("2,3,5,4,1"), 4, 5, 2, false);
    wc.add_player(13, 1, permutation_t::read("3,1,4,2,5"), 4, 5, 2, false);
    wc.add_player(14, 2, permutation_t::read("5,4,2,1,3"), 4, 5, 2, false);
    wc.add_player(15, 2, permutation_t::read("2,1,3,4,5"), 4, 5, 2, false);

    PlayerData* player1 = wc.m_hashTable->find(11);
    PlayerData* player2 = wc.m_hashTable->find(12);
    PlayerData* player3 = wc.m_hashTable->find(13);
    PlayerData* player4 = wc.m_hashTable->find(14);
    PlayerData* player5 = wc.m_hashTable->find(15);

    output_t<permutation_t> per1 = wc.get_partial_spirit(11);
    std::cout << "player1 permutation: ";
    std::cout << permutation_t::read("1,5,4,2,3") << std::endl;
    std::cout << per1.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per2 = wc.get_partial_spirit(12);
    permutation_t partial_2 = permutation_t::read("1,5,4,2,3") * permutation_t::read("2,3,5,4,1");
    std::cout << "player2 permutation: " << partial_2 << std::endl;
    std::cout << per2.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per3 = wc.get_partial_spirit(13);
    permutation_t partial_3 = partial_2 * permutation_t::read("3,1,4,2,5");
    std::cout << "player3 permutation: " << partial_3 << std::endl;
    std::cout << per3.ans() << std::endl;

    std::cout << "---------------------" << std::endl;


    output_t<permutation_t> per4 = wc.get_partial_spirit(14);
    std::cout << "player4 permutation: ";
    std::cout << permutation_t::read("5,4,2,1,3") << std::endl;
    std::cout << per4.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per5 = wc.get_partial_spirit(15);
    permutation_t partial_5 = permutation_t::read("5,4,2,1,3") * permutation_t::read("2,1,3,4,5");
    std::cout << "player5 permutation: " << partial_5 << std::endl;
    std::cout << per5.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    wc.buy_team(1, 2);

    output_t<permutation_t> per1ABT = wc.get_partial_spirit(11);
    permutation_t partial_1ABT = permutation_t::read("1,5,4,2,3");
    std::cout << "player1 permutation: " << partial_1ABT << std::endl;
    std::cout << per1ABT.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per2ABT = wc.get_partial_spirit(12);
    permutation_t partial_2ABT = partial_1ABT * permutation_t::read("2,3,5,4,1");
    std::cout << "player2 permutation: " << partial_2ABT << std::endl;
    std::cout << per2ABT.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per3ABT = wc.get_partial_spirit(13);
    permutation_t partial_3ABT = partial_2ABT * permutation_t::read("3,1,4,2,5");
    std::cout << "player3 permutation: " << partial_3ABT << std::endl;
    std::cout << per3ABT.ans() << std::endl;

    std::cout << "---------------------" << std::endl;

    output_t<permutation_t> per4ABT = wc.get_partial_spirit(14);
    permutation_t partial_4ABT = partial_3ABT * permutation_t::read("5,4,2,1,3");
    std::cout << "player4 permutation: ";
    std::cout << partial_4ABT << std::endl;
    std::cout << per4ABT.ans() << std::endl;

    std::cout << "---------------------" << std::endl;


    output_t<permutation_t> per5ABT = wc.get_partial_spirit(15);
    permutation_t partial_5ABT = partial_4ABT * permutation_t::read("2,1,3,4,5");
    std::cout << "player5 permutation: " << partial_5ABT << std::endl;
    std::cout << per5ABT.ans() << std::endl;

    std::cout << "---------------------" << std::endl;



    return 0;

}

int get_played_game_no_shrinking(PlayerData* player){
    int counter = player->getIndividualGamesPlayed();

    while(player){
        counter+=player->getCalcTotalGamesPlayed();
        player = player->getUp();
    }

    return counter;
}


int main(){

    world_cup_t wc;
    wc.add_team(1);
    wc.add_team(2);
    wc.add_team(3);
    wc.add_team(4);
    wc.add_team(5);
    wc.add_team(6);
    wc.add_team(7);
    wc.add_team(8);
    wc.add_player(1,4,permutation_t::read("4,2,1,3,5"),5,203,67,true);
    wc.add_player(2,1,permutation_t::read("4,2,5,1,3"),273,97,67,false);
    wc.add_player(3,1,permutation_t::read("1,3,5,2,4"),9,75,218,true);
    wc.add_player(4,7,permutation_t::read("2,3,4,1,5"),50,54,52,true);
    wc.add_player(5,6,permutation_t::read("3,4,1,5,2"),109,76,94,false);
    wc.add_player(6,1,permutation_t::read("5,2,1,3,4"),43,223,115,false);
    wc.add_player(7,8,permutation_t::read("5,3,2,1,4"),276,174,282,false);
    wc.add_player(8,4,permutation_t::read("1,3,5,2,4"),24,73,243,true);
    wc.add_player(9,4,permutation_t::read("4,2,5,1,3"),205,189,1,false);
    wc.add_player(10,2,permutation_t::read("3,2,5,1,4"),13,234,100,false);
    wc.add_player(11,1,permutation_t::read("3,4,2,5,1"),154,123,275,false);
    wc.add_player(12,3,permutation_t::read("5,1,3,2,4"),192,236,167,false);
    wc.add_player(13,4,permutation_t::read("3,1,2,4,5"),116,50,39,true);
    wc.add_player(14,3,permutation_t::read("4,1,3,5,2"),47,275,246,true);
    wc.add_player(15,2,permutation_t::read("4,2,1,5,3"),254,174,9,true);
    wc.add_player(16,2,permutation_t::read("4,5,2,3,1"),110,42,100,false);
    wc.add_player(17,5,permutation_t::read("4,2,3,1,5"),92,20,68,true);
    wc.add_player(18,3,permutation_t::read("1,3,2,4,5"),164,47,34,true);
    wc.add_player(19,6,permutation_t::read("1,2,3,4,5"),207,142,4,false);
    wc.add_player(20,5,permutation_t::read("5,2,1,4,3"),215,239,295,true);
    wc.play_match(3,4);
    wc.add_player_cards(9,90);
    wc.get_team_points(1);
    wc.get_ith_pointless_ability(1);
    wc.add_player(21,7,permutation_t::read("4,1,2,3,5"),15,74,184,true);
    wc.remove_team(4);
    wc.play_match(3,8);
    wc.get_team_points(5);
    wc.get_player_cards(8);
    wc.get_player_cards(6);
    wc.add_player(22,7,permutation_t::read("5,4,2,3,1"),296,206,35,false);
    PlayerData* player = wc.m_hashTable->find(22);
    wc.add_player_cards(20,221);
    wc.get_team_points(7);
    wc.add_player(23,5,permutation_t::read("4,5,3,1,2"),113,96,133,false);
    wc.add_player(24,5,permutation_t::read("1,4,3,5,2"),258,187,214,false);
    wc.add_player(25,5,permutation_t::read("4,1,2,3,5"),286,119,130,false);
    wc.add_player(26,3,permutation_t::read("5,4,2,1,3"),5,170,288,true);
    wc.get_ith_pointless_ability(0);
    wc.remove_team(8);
    wc.get_ith_pointless_ability(1);
    wc.play_match(7,2);
    wc.get_ith_pointless_ability(4);
    wc.get_player_cards(18);
    wc.get_player_cards(19);
    wc.get_team_points(5);
    wc.remove_team(1);
    wc.get_ith_pointless_ability(4);
    wc.buy_team(7,3);
    wc.get_player_cards(7);
    wc.get_ith_pointless_ability(0);
    wc.num_played_games_for_player(1);
    wc.num_played_games_for_player(2);
    wc.num_played_games_for_player(6);
    wc.play_match(2,7);
    wc.add_team(8);
    wc.add_team(8);
    wc.add_player(27,6,permutation_t::read("3,1,2,4,5"),22,165,286,false);
    wc.get_player_cards(18);
    wc.buy_team(5,2);
    wc.remove_team(5);
    wc.add_player_cards(10,151);
    wc.buy_team(6,2);
    wc.remove_team(6);
    wc.get_team_points(3);
    wc.play_match(7,2);
    wc.add_player_cards(4,133);
    wc.remove_team(7);
    wc.num_played_games_for_player(2);
    wc.add_team(4);
    wc.get_ith_pointless_ability(0);
    wc.play_match(2,3);
    wc.add_player(27,2,permutation_t::read("1,4,5,2,3"),128,10,281,true);
    wc.get_partial_spirit(12);
    wc.get_ith_pointless_ability(1);
    wc.add_player(27,2,permutation_t::read("3,2,4,1,5"),228,191,282,true);
    wc.get_partial_spirit(26);
    wc.num_played_games_for_player(22);
    std::cout << wc.num_played_games_for_player(22).ans() << std::endl;
    std::cout << get_played_game_no_shrinking(player);

    return 0;

}



