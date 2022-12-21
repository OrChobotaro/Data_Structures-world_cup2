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

    if (!reversedRoot->getPtrTeam()) {
        return nullptr;
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




bool world_cup_t::unionPlayerToTeam(int playerID, int teamID) {
    PlayerData* playerNode = m_hashTable->find(playerID);
    Node<TeamData>* teamNode = findTeamInTeamTree(teamID, m_teamTree->getRoot());
    if (!playerNode || !teamNode) {
        return false;
    }
    if (playerNode->getPtrTeam() || playerNode->getUp()) {
        return false;
    }
    if (teamNode->getKey().getPtrPlayerReverseRoot()) {
        return unionPlayerToRegularTeam(playerNode, teamNode);
    }
    return unionPlayerToEmptyTeam(playerNode, teamNode);
}


bool world_cup_t::unionPlayerToEmptyTeam(PlayerData* playerNode, Node<TeamData>* teamNode) {
    playerNode->setPtrTeam(teamNode);
    teamNode->m_key.setPtrPlayerReverseRoot(playerNode);
    teamNode->m_key.increaseTeamFieldsAfterUnion(playerNode);
    return true;
}



bool world_cup_t::unionPlayerToRegularTeam(PlayerData* playerNode, Node<TeamData>* teamNode) {
    PlayerData* reversedRoot = teamNode->getKey().getPtrPlayerReverseRoot();

    playerNode->setCalcTotalGamesPlayed(-reversedRoot->getCalcTotalGamesPlayed());
    permutation_t newCalcPartialSpirit = (teamNode->getKey().getTeamSpirit() * playerNode->getCalcPartialSpirit()) *
            reversedRoot->getCalcPartialSpirit().inv();
    playerNode->setCalcPartialSpirit(newCalcPartialSpirit);

    playerNode->setUp(reversedRoot);
    teamNode->m_key.increaseTeamFieldsAfterUnion(playerNode);

    return true;
}



bool world_cup_t::unionBigBuyerTeamToSmallTeam(Node<TeamData> *bigTeamNode, Node<TeamData> *smallTeamNode) {
    if (!bigTeamNode || !smallTeamNode) {
        return false;
    }

    PlayerData* reversedRootBigTeam = bigTeamNode->getKey().getPtrPlayerReverseRoot();
    PlayerData* reversedRootSmallTeam = smallTeamNode->getKey().getPtrPlayerReverseRoot();
    if (!reversedRootBigTeam && !reversedRootSmallTeam) {
        return false;
    }

    int newNumPlayers = bigTeamNode->getKey().getNumPlayers() + smallTeamNode->getKey().getNumPlayers();
    int newNumGoalKeepers = bigTeamNode->getKey().getNumGoalKeepers() + smallTeamNode->getKey().getNumGoalKeepers();
    int newPoints = bigTeamNode->getKey().getTeamPoints() + smallTeamNode->getKey().getTeamPoints();
    int newAbility = bigTeamNode->getKey().getTeamAbility() + smallTeamNode->getKey().getTeamAbility();
    permutation_t newSpirit = bigTeamNode->getKey().getTeamSpirit() * smallTeamNode->getKey().getTeamSpirit();

    int newCalcTotalGamesPlayedSmallTeam = reversedRootSmallTeam->getCalcTotalGamesPlayed() -
                                                                    reversedRootBigTeam->getCalcTotalGamesPlayed();
    reversedRootSmallTeam->setCalcTotalGamesPlayed(newCalcTotalGamesPlayedSmallTeam);

    permutation_t bigTeamSpirit = bigTeamNode->getKey().getTeamSpirit();
    permutation_t reversedRootBigTeamSpirit = reversedRootBigTeam->getCalcPartialSpirit();
    permutation_t reversedRootSmallTeamSpirit = reversedRootSmallTeam->getCalcPartialSpirit();

    reversedRootSmallTeam->setCalcPartialSpirit(bigTeamSpirit * reversedRootSmallTeamSpirit *
                                                reversedRootBigTeamSpirit.inv());

    bigTeamNode->m_key.setNumPlayers(newNumPlayers);
    bigTeamNode->m_key.setNumGoalKeepers(newNumGoalKeepers);
    bigTeamNode->m_key.setPoints(newPoints);
    bigTeamNode->m_key.setTeamAbility(newAbility);
    bigTeamNode->m_key.setTeamSpirit(newSpirit);

    reversedRootSmallTeam->setUp(reversedRootBigTeam);
    reversedRootSmallTeam->setPtrTeam(nullptr);

    smallTeamNode->m_key.setPtrPlayerReverseRoot(nullptr);

    m_teamTree->remove(smallTeamNode->getKey());

    return true;
}



bool world_cup_t::unionSmallBuyerTeamToBigTeam(Node<TeamData> *bigTeamNode, Node<TeamData> *smallTeamNode) {
    if (!bigTeamNode || !smallTeamNode) {
        return false;
    }

    PlayerData* reversedRootBigTeam = bigTeamNode->getKey().getPtrPlayerReverseRoot();
    PlayerData* reversedRootSmallTeam = smallTeamNode->getKey().getPtrPlayerReverseRoot();
    if (!reversedRootBigTeam && !reversedRootSmallTeam) {
        return false;
    }

    int newNumPlayers = bigTeamNode->getKey().getNumPlayers() + smallTeamNode->getKey().getNumPlayers();
    int newNumGoalKeepers = bigTeamNode->getKey().getNumGoalKeepers() + smallTeamNode->getKey().getNumGoalKeepers();
    int newPoints = bigTeamNode->getKey().getTeamPoints() + smallTeamNode->getKey().getTeamPoints();
    int newAbility = bigTeamNode->getKey().getTeamAbility() + smallTeamNode->getKey().getTeamAbility();
    permutation_t newSpirit = bigTeamNode->getKey().getTeamSpirit() * smallTeamNode->getKey().getTeamSpirit();

    int newCalcTotalGamesPlayedSmallTeam = reversedRootSmallTeam->getCalcTotalGamesPlayed() -
                                           reversedRootBigTeam->getCalcTotalGamesPlayed();
    reversedRootSmallTeam->setCalcTotalGamesPlayed(newCalcTotalGamesPlayedSmallTeam);

    permutation_t newCalcPartialSpiritBigTeam = reversedRootBigTeam->getCalcPartialSpirit() *
                                                                    smallTeamNode->getKey().getTeamSpirit();
    reversedRootBigTeam->setCalcPartialSpirit(newCalcPartialSpiritBigTeam);

    permutation_t newCalcPartialSpiritSmallTeam = reversedRootSmallTeam->getCalcPartialSpirit() *
                                                                    newCalcPartialSpiritBigTeam.inv();
    reversedRootSmallTeam->setCalcPartialSpirit(newCalcPartialSpiritSmallTeam);


    bigTeamNode->m_key.setNumPlayers(newNumPlayers);
    bigTeamNode->m_key.setNumGoalKeepers(newNumGoalKeepers);
    bigTeamNode->m_key.setPoints(newPoints);
    bigTeamNode->m_key.setTeamAbility(newAbility);
    bigTeamNode->m_key.setTeamSpirit(newSpirit);

    reversedRootSmallTeam->setUp(reversedRootBigTeam);
    reversedRootSmallTeam->setPtrTeam(nullptr);

    smallTeamNode->m_key.setPtrPlayerReverseRoot(nullptr);

    m_teamTree->remove(smallTeamNode->getKey());
    return true;
}



Node<TeamData>* world_cup_t::findTeamInTeamTree(int teamID, Node<TeamData>* root) {
    Node<TeamData>* temp = root;
    while (temp) {
        int tempID = temp->getKey().getTeamID();
        if (tempID < teamID) {
            temp = temp->getRight();
        }
        else if (tempID > teamID) {
            temp = temp->getLeft();
        }
        else if (tempID == teamID) {
            return temp;
        }
    }
    return nullptr;
}