#include "worldcup23a2.h"

world_cup_t::world_cup_t()
{

    // creating teams' tree
    std::shared_ptr<AvlTree<TeamData>> teamTree(new AvlTree<TeamData>);
    m_teamTree = teamTree;

    // creating hash table
    HashTable* hashTable = new HashTable(20);
    m_hashTable = hashTable;

    // creating rank tree
    std::shared_ptr<RankTree> rankTree(new RankTree);
    m_rankAbilityTree = rankTree;
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}

StatusType world_cup_t::add_team(int teamId)
{

    if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    } else if(m_teamTree->find(teamId)){
        return StatusType::FAILURE;
    }

    return m_teamTree->insert(teamId);

}

StatusType world_cup_t::remove_team(int teamId) // todo: test when adding players
{

    Node<TeamData>* team = m_teamTree->find(teamId);

    if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    } else if (!team){
        return StatusType::FAILURE;
    }

    if(team->getKey().getPtrPlayerReverseRoot()){
        team->getKey().getPtrPlayerReverseRoot()->setPtrTeam(nullptr);
        team->getKey().setPtrPlayerReverseRoot(nullptr);
    }

    m_teamTree->remove(teamId);

	return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)  //todo: test when union func is ready
{

    // find team in teams' tree
    Node<TeamData>* team = m_teamTree->find(teamId);

    if(playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || cards < 0 || !spirit.isvalid()){ // todo: check spirit invalid??
        return StatusType::INVALID_INPUT;
    } else if (!team || m_hashTable->find(playerId)){
        return StatusType::FAILURE;
    }

    PlayerData* newPlayer;
    try{
         newPlayer = new PlayerData(playerId, spirit, gamesPlayed, ability, cards, goalKeeper);
    } catch(std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    // adding player to hash
    m_hashTable->insert(newPlayer);

    // todo: add - union to team


	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{

    // check input:
    if(teamId1 <=0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }

    // find teams in tree:
    Node<TeamData>* team1 = m_teamTree->find(teamId1);
    Node<TeamData>* team2 = m_teamTree->find(teamId2);

    if(!team1 || !team2 || team1->getKey().getNumGoalKeepers() == 0 || team2->getKey().getNumGoalKeepers() == 0){
        return StatusType::FAILURE;
    }


    int totalTeam1 = team1->getKey().getTeamPoints() + team1->getKey().getTeamAbility();


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