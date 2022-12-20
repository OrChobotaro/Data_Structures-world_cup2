#include "worldcup23a2.h"

world_cup_t::world_cup_t()
{
	// TODO: Your code goes here
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}

StatusType world_cup_t::add_team(int teamId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	// TODO: Your code goes here
	return StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}







////// To check in the fatherFunc that player != nullptr
Node<TeamData>* world_cup_t::findTeamAux(PlayerData *player) {
    PlayerData* temp = player;
    int sumTotalGamesPlayed = 0;
    permutation_t multiplePartialSpirit = permutation_t::neutral();

    PlayerData* reversedRoot = nullptr;
    while (temp->getUp()) {
        reversedRoot = temp;
        sumTotalGamesPlayed += temp->getCalcTotalGamesPlayed();
        multiplePartialSpirit = multiplePartialSpirit * temp->getCalcPartialSpirit();
        temp = temp->getUp();
    }

    sumTotalGamesPlayed -= reversedRoot->getCalcTotalGamesPlayed();
    multiplePartialSpirit = multiplePartialSpirit * (reversedRoot->getCalcPartialSpirit()).inv();

    int toSubtract = 0;
    permutation_t toDivide = permutation_t::neutral();

    temp = player;
    while (temp->getUp() != reversedRoot) {
        int tempTotalGamesPlayed = temp->getCalcTotalGamesPlayed();
        temp->setCalcTotalGamesPlayed(sumTotalGamesPlayed - toSubtract);

        permutation_t tempPartialSpirit = temp->getCalcPartialSpirit();
        temp->setCalcPartialSpirit(multiplePartialSpirit * toDivide.inv());

        toSubtract += tempTotalGamesPlayed;
        toDivide = toDivide * tempPartialSpirit;

        temp->setUp(reversedRoot);
        temp = temp->getUp();
    }
    return reversedRoot->getPtrTeam();
}