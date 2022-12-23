#include "worldcup23a2.h"

// todo: update rank tree in union func

world_cup_t::world_cup_t()
{

    // creating teams' tree
    std::shared_ptr<AvlTree<TeamData>> teamTree(new AvlTree<TeamData>);
    m_teamTree = teamTree;

    // creating hash table
    std::shared_ptr<HashTable> hashTable(new HashTable(20));
    m_hashTable = hashTable;

    // creating rank tree
    std::shared_ptr<RankTree> rankTree(new RankTree);
    m_rankAbilityTree = rankTree;

    m_numberOfTeams = 0;
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

    m_numberOfTeams++;
    AbilityDataTeam abilityObj(teamId, 0);
    m_rankAbilityTree->insert(abilityObj);
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
    m_numberOfTeams--;
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

    // todo: remove and add to rank tree
    AbilityDataTeam abilityTempToDelete(teamId, team->getKey().getTeamAbility());
    m_rankAbilityTree->remove(abilityTempToDelete);

    unionPlayerToTeam(playerId, team);

    AbilityDataTeam abilityTempToInsert(teamId, team->getKey().getTeamAbility());
    m_rankAbilityTree->insert(abilityTempToInsert);

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

    // if both teams are valid, increase played games by 1.
    team1->m_key.getPtrPlayerReverseRoot()->increaseCalcTotalGamesPlayed(1);
    team2->m_key.getPtrPlayerReverseRoot()->increaseCalcTotalGamesPlayed(1);

    int totalTeam1 = team1->getKey().getTeamPoints() + team1->getKey().getTeamAbility();
    int totalTeam2 = team2->getKey().getTeamPoints() + team2->getKey().getTeamAbility();

    int team1Strengh = team1->getKey().getTeamSpirit().strength();
    int team2Strengh = team2->getKey().getTeamSpirit().strength();


    if(totalTeam1 > totalTeam2){
        team1->m_key.increasePoints(3);
        return 1;
    }
    else if (totalTeam2 > totalTeam1){
        team2->m_key.increasePoints(3);
        return 3;
    }
    else {
        if(team1Strengh > team2Strengh){
            team1->m_key.increasePoints(3);
            return 2;
        }
        else if (team2Strengh > team1Strengh){
            team2->m_key.increasePoints(3);
            return 4;
        }
        else {
            team1->m_key.increasePoints(1);
            team2->m_key.increasePoints(1);
            return 0;
        }
    }

}

output_t<int> world_cup_t::num_played_games_for_player(int playerId) // todo: test when buy team is ready!!!
{

    if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }

	// find player in hash
    PlayerData* player = m_hashTable->find(playerId);

    if(!player){
        return StatusType::FAILURE;
    }

    // run find for shrinking - O(log*n)
    findTeam(player);

    int gamesPlayedCounter = player->getIndividualGamesPlayed();

    // sum all calc fields
    // after shrink, player node should point to reverse root
    gamesPlayedCounter += player->getCalcTotalGamesPlayed();
    if(player->getUp()){
        gamesPlayedCounter += player->getUp()->getCalcTotalGamesPlayed();
    }


	return gamesPlayedCounter;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{

    if(playerId <= 0 || cards < 0){
        return StatusType::INVALID_INPUT;
    }

    // if player doesnt exist:
    PlayerData* player = m_hashTable->find(playerId);
    if(!player){
        return StatusType::FAILURE;
    }
    // check if player not in valid team:
    Node<TeamData>* team = findTeam(player);

    if(!team){
        return StatusType::FAILURE;
    }

    player->increaseCards(cards);


	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{

    if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
	PlayerData* player = m_hashTable->find(playerId);

    if(!player){
        return StatusType::FAILURE;
    }

	return player->getCards();
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }

    Node<TeamData>* team = m_teamTree->find(teamId);
    if(!team){
        return StatusType::FAILURE;
    }

	return team->getKey().getTeamPoints();
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// check there are teams in the system
    if(!m_teamTree->getRoot() || i < 0 || i >= m_numberOfTeams){
        return StatusType::FAILURE;
    }

    return m_rankAbilityTree->findIndex(i)->getKey().getTeamID();

}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }

    PlayerData* player = m_hashTable->find(playerId);
    if(!player){
        return StatusType::FAILURE;
    }

    Node<TeamData>* team = findTeam(player);
    if(!team){
        return StatusType::FAILURE;
    }

    permutation_t per = permutation_t::neutral();

    per = per * player->getSpirit();
    per = per * player->getCalcPartialSpirit();
    if(player->getUp()){
        per = per * player->getUp()->getCalcPartialSpirit();
    }

	return per;
}



StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
        return StatusType::INVALID_INPUT;
    }

    Node<TeamData>* buyerTeam = findTeamInTeamTree(teamId1, m_teamTree->getRoot());
    Node<TeamData>* boughtTeam = findTeamInTeamTree(teamId2, m_teamTree->getRoot());
    if (!buyerTeam || !boughtTeam) {
        return StatusType::FAILURE;
    }

    int numPlayersBuyerTeam = buyerTeam->getKey().getNumPlayers();
    int numPlayersBoughtTeam = boughtTeam->getKey().getNumPlayers();

    if (numPlayersBuyerTeam >= 0  &&  numPlayersBoughtTeam == 0) {
        remove_team(boughtTeam->getKey().getTeamID());
        return StatusType::SUCCESS;
    }

    else if (numPlayersBuyerTeam == 0  &&  numPlayersBoughtTeam > 0) {
        PlayerData* reversedRootBoughtTeam = boughtTeam->getKey().getPtrPlayerReverseRoot();
        boughtTeam->m_key.setPtrPlayerReverseRoot(nullptr);
        reversedRootBoughtTeam->setPtrTeam(buyerTeam);
        buyerTeam->m_key.setPtrPlayerReverseRoot(reversedRootBoughtTeam);

        buyerTeam->m_key.setNumPlayers(boughtTeam->getKey().getNumPlayers());
        buyerTeam->m_key.setNumGoalKeepers(boughtTeam->getKey().getNumGoalKeepers());
        buyerTeam->m_key.setPoints(boughtTeam->getKey().getTeamPoints());
        buyerTeam->m_key.setTeamAbility(boughtTeam->getKey().getTeamAbility());
        buyerTeam->m_key.setTeamSpirit(boughtTeam->getKey().getTeamSpirit());

        remove_team(boughtTeam->getKey().getTeamID());;
        return StatusType::SUCCESS;
    }

    else if (numPlayersBuyerTeam >= numPlayersBoughtTeam) {
        unionBigBuyerTeamToSmallTeam(buyerTeam, boughtTeam);
        return StatusType::SUCCESS;
    }

    else if (numPlayersBuyerTeam < numPlayersBoughtTeam) {
        unionSmallBuyerTeamToBigTeam(boughtTeam, buyerTeam);
        return StatusType::SUCCESS;
    }

	return StatusType::SUCCESS;
}







////// To check in the fatherFunc that player != nullptr
Node<TeamData>* world_cup_t::findTeam(PlayerData *player) {

  assert(player);
    if (!player) {
        return nullptr;
    }
    

    PlayerData* temp = player;
    int sumTotalGamesPlayed = 0;
    permutation_t multiplePartialSpirit = permutation_t::neutral();

    //if returns NULL, it means that the player was the root and that the team was deleted
    if(!temp->getUp()){
        return player->getPtrTeam();
    }

    while (temp->getUp()) {
        sumTotalGamesPlayed += temp->getCalcTotalGamesPlayed();
        multiplePartialSpirit = multiplePartialSpirit * temp->getCalcPartialSpirit();
        temp = temp->getUp();
    }

    PlayerData* reversedRoot = temp;

    //in case the team was deleted
    if (!reversedRoot->getPtrTeam()) {
        return nullptr;
    }

/*    sumTotalGamesPlayed -= reversedRoot->getCalcTotalGamesPlayed();
    multiplePartialSpirit = multiplePartialSpirit * (reversedRoot->getCalcPartialSpirit()).inv();*/

    int toSubtract = 0;
    permutation_t toDivide = permutation_t::neutral();

    temp = player;
    while (temp != reversedRoot) {
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




bool world_cup_t::unionPlayerToTeam(int playerID, Node<TeamData>* teamNode) {
    PlayerData* playerNode = m_hashTable->find(playerID);

    if (!playerNode || !teamNode) {
        return false;
    }
    if (playerNode->getPtrTeam() || playerNode->getUp()) {
        return false;
    }

    AbilityDataTeam oldAbilityTeam(teamNode->getKey().getTeamID(), teamNode->getKey().getTeamAbility());
    m_rankAbilityTree->remove(oldAbilityTeam);

    if (teamNode->getKey().getPtrPlayerReverseRoot()) {
        unionPlayerToRegularTeam(playerNode, teamNode);
    }
    else {
        unionPlayerToEmptyTeam(playerNode, teamNode);
    }

    AbilityDataTeam newAbilityTeam(teamNode->getKey().getTeamID(), teamNode->getKey().getTeamAbility());
    m_rankAbilityTree->insert(newAbilityTeam);
    return true;
}


void world_cup_t::unionPlayerToEmptyTeam(PlayerData* playerNode, Node<TeamData>* teamNode) {
    playerNode->setPtrTeam(teamNode);
    teamNode->m_key.setPtrPlayerReverseRoot(playerNode);
    teamNode->m_key.increaseTeamFieldsAfterUnion(playerNode);
}



void world_cup_t::unionPlayerToRegularTeam(PlayerData* playerNode, Node<TeamData>* teamNode) {
    PlayerData* reversedRoot = teamNode->getKey().getPtrPlayerReverseRoot();

    playerNode->setCalcTotalGamesPlayed(-reversedRoot->getCalcTotalGamesPlayed());
    permutation_t newCalcPartialSpirit = (teamNode->getKey().getTeamSpirit() * playerNode->getCalcPartialSpirit()) *
            reversedRoot->getCalcPartialSpirit().inv();
    playerNode->setCalcPartialSpirit(newCalcPartialSpirit);

    playerNode->setUp(reversedRoot);
    teamNode->m_key.increaseTeamFieldsAfterUnion(playerNode);
}



void world_cup_t::unionBigBuyerTeamToSmallTeam(Node<TeamData> *bigTeamNode, Node<TeamData> *smallTeamNode) {

    PlayerData* reversedRootBigTeam = bigTeamNode->getKey().getPtrPlayerReverseRoot();
    PlayerData* reversedRootSmallTeam = smallTeamNode->getKey().getPtrPlayerReverseRoot();
    assert(reversedRootBigTeam && reversedRootSmallTeam);

    int newNumPlayers = bigTeamNode->getKey().getNumPlayers() + smallTeamNode->getKey().getNumPlayers();
    int newNumGoalKeepers = bigTeamNode->getKey().getNumGoalKeepers() + smallTeamNode->getKey().getNumGoalKeepers();
    int newPoints = bigTeamNode->getKey().getTeamPoints() + smallTeamNode->getKey().getTeamPoints();
    int newAbility = bigTeamNode->getKey().getTeamAbility() + smallTeamNode->getKey().getTeamAbility();
    permutation_t newSpirit = bigTeamNode->getKey().getTeamSpirit() * smallTeamNode->getKey().getTeamSpirit();

    AbilityDataTeam oldAbilityBigTeam(bigTeamNode->getKey().getTeamID(), bigTeamNode->getKey().getTeamAbility());
    m_rankAbilityTree->remove(oldAbilityBigTeam);
    AbilityDataTeam oldAbilitySmallTeam(smallTeamNode->getKey().getTeamID(), smallTeamNode->getKey().getTeamAbility());
    m_rankAbilityTree->remove(oldAbilitySmallTeam);

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

    AbilityDataTeam newAbilityBigTeam(bigTeamNode->getKey().getTeamID(), bigTeamNode->getKey().getTeamAbility());
    m_rankAbilityTree->insert(newAbilityBigTeam);

    reversedRootSmallTeam->setUp(reversedRootBigTeam);
    reversedRootSmallTeam->setPtrTeam(nullptr);

    smallTeamNode->m_key.setPtrPlayerReverseRoot(nullptr);

    remove_team(smallTeamNode->getKey().getTeamID());
}



void world_cup_t::unionSmallBuyerTeamToBigTeam(Node<TeamData> *bigTeamNode, Node<TeamData> *smallTeamNode) {

    PlayerData* reversedRootBigTeam = bigTeamNode->getKey().getPtrPlayerReverseRoot();
    PlayerData* reversedRootSmallTeam = smallTeamNode->getKey().getPtrPlayerReverseRoot();
    assert(reversedRootBigTeam && reversedRootSmallTeam);

    int newNumPlayers = bigTeamNode->getKey().getNumPlayers() + smallTeamNode->getKey().getNumPlayers();
    int newNumGoalKeepers = bigTeamNode->getKey().getNumGoalKeepers() + smallTeamNode->getKey().getNumGoalKeepers();
    int newPoints = bigTeamNode->getKey().getTeamPoints() + smallTeamNode->getKey().getTeamPoints();
    int newAbility = bigTeamNode->getKey().getTeamAbility() + smallTeamNode->getKey().getTeamAbility();
    permutation_t newSpirit = bigTeamNode->getKey().getTeamSpirit() * smallTeamNode->getKey().getTeamSpirit();

    AbilityDataTeam oldAbilityBigTeam(bigTeamNode->getKey().getTeamID(), bigTeamNode->getKey().getTeamAbility());
    m_rankAbilityTree->remove(oldAbilityBigTeam);
    AbilityDataTeam oldAbilitySmallTeam(smallTeamNode->getKey().getTeamID(), smallTeamNode->getKey().getTeamAbility());
    m_rankAbilityTree->remove(oldAbilitySmallTeam);

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

    AbilityDataTeam newAbilityBigTeam(bigTeamNode->getKey().getTeamID(), bigTeamNode->getKey().getTeamAbility());
    m_rankAbilityTree->insert(newAbilityBigTeam);

    reversedRootSmallTeam->setUp(reversedRootBigTeam);
    reversedRootSmallTeam->setPtrTeam(nullptr);

    smallTeamNode->m_key.setPtrPlayerReverseRoot(nullptr);

    remove_team(smallTeamNode->getKey().getTeamID());
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
