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



int main(){

    world_cup_t* obj = new world_cup_t();

    StatusType res = obj->add_team(1);
//    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_team(2);
//    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_team(3);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_team(4);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_team(5);
    //REQUIRE(res == StatusType::SUCCESS);

    res = obj->add_player(1001, 1, permutation_t::read("2,3,5,4,1"), 1, 1000, 0, true);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(1002, 1, permutation_t::neutral(), 1, 1, 0, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(2001, 2, permutation_t::read("4,2,1,5,3"), 1, 100, 0, true);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(2002, 2, permutation_t::neutral(), 1, 1, 0, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(3001, 3, permutation_t::read("5,4,3,2,1"), 1, 10000, 0, true);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(4001, 4, permutation_t::neutral(), 1, 1, 0, true);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(4002, 4, permutation_t::read("1,5,2,4,3"), 1, 10, 0, true);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(5001, 5, permutation_t::neutral(), 1, 0, 0, true);
    //REQUIRE(res == StatusType::SUCCESS);


    output_t<permutation_t> res14 = obj->get_partial_spirit(1001);
    //REQUIRE(res14.status() == StatusType::SUCCESS);
    //REQUIRE(res14.ans() == permutation_t::read("2,3,5,4,1"));
    output_t<permutation_t> res15 = obj->get_partial_spirit(2001);
    //REQUIRE(res15.status() == StatusType::SUCCESS);
    //REQUIRE(res15.ans() == permutation_t::read("4,2,1,5,3"));
    output_t<permutation_t> res16 = obj->get_partial_spirit(3001);
    //REQUIRE(res16.status() == StatusType::SUCCESS);
    //REQUIRE(res16.ans() == permutation_t::read("5,4,3,2,1"));
    output_t<permutation_t> res17 = obj->get_partial_spirit(4002);
    //REQUIRE(res17.status() == StatusType::SUCCESS);
    //REQUIRE(res17.ans() == permutation_t::read("1,5,2,4,3"));
    output_t<permutation_t> res18 = obj->get_partial_spirit(5001);
    //REQUIRE(res18.status() == StatusType::SUCCESS);
    //REQUIRE(res18.ans() == permutation_t::neutral());

    res = obj->buy_team(1, 2);
    //REQUIRE(res == StatusType::SUCCESS);

    output_t<permutation_t> res140 = obj->get_partial_spirit(1001);
    //REQUIRE(res140.status() == StatusType::SUCCESS);
    //REQUIRE(res140.ans() == permutation_t::read("2,3,5,4,1"));
    output_t<permutation_t> res150 = obj->get_partial_spirit(2001);
    //REQUIRE(res150.status() == StatusType::SUCCESS);
    //REQUIRE(res150.ans() == permutation_t::read("4,3,2,1,5"));


    res = obj->buy_team(3, 4);
    //REQUIRE(res == StatusType::SUCCESS);

    output_t<permutation_t> res161 = obj->get_partial_spirit(3001);
    //REQUIRE(res161.status() == StatusType::SUCCESS);
    //REQUIRE(res161.ans() == permutation_t::read("5,4,3,2,1"));
    output_t<permutation_t> res171 = obj->get_partial_spirit(4002);
    //REQUIRE(res171.status() == StatusType::SUCCESS);
    //REQUIRE(res171.ans() == permutation_t::read("5,1,4,2,3"));



    res = obj->buy_team(3, 5);
    //REQUIRE(res == StatusType::SUCCESS);

    output_t<permutation_t> res162 = obj->get_partial_spirit(3001);
    //REQUIRE(res162.status() == StatusType::SUCCESS);
    //REQUIRE(res162.ans() == permutation_t::read("5,4,3,2,1"));
    output_t<permutation_t> res172 = obj->get_partial_spirit(4002);
    //REQUIRE(res172.status() == StatusType::SUCCESS);
    //REQUIRE(res172.ans() == permutation_t::read("5,1,4,2,3"));
    output_t<permutation_t> res182 = obj->get_partial_spirit(5001);
    //REQUIRE(res182.status() == StatusType::SUCCESS);
    //REQUIRE(res182.ans() == permutation_t::read("5,1,4,2,3"));

    return 0;


}



