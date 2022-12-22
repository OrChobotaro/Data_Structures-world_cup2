#include "UnionFindData.h"



TeamData::TeamData(int teamID): m_teamID(teamID), m_numPlayers(0), m_numGoalKeepers(0), m_points(0),
    m_teamAbility(0), m_teamSpirit(permutation_t::neutral()), m_ptrPlayerReverseRoot(nullptr) {}


bool TeamData::operator<(const TeamData& other) const{
    if(this->m_teamID < other.m_teamID){
        return true;
    }
    return false;
}

bool TeamData::operator>(const TeamData& other) const{
    return (other < *this);
}



int TeamData::getTeamID() const {
    return this->m_teamID;
}

int TeamData::getNumPlayers() const {
    return this->m_numPlayers;
}

int TeamData::getNumGoalKeepers() const{
    return this->m_numGoalKeepers;
}

int TeamData::getTeamPoints() const{
    return this->m_points;
}

int TeamData::getTeamAbility() const {
    return m_teamAbility;
}

permutation_t TeamData::getTeamSpirit() const {
    return m_teamSpirit;
}

/*permutation_t TeamData::getTeamSpiritStrength() const {
    return m_teamSpiritStrength;
}*/

PlayerData* TeamData::getPtrPlayerReverseRoot() const {
    return m_ptrPlayerReverseRoot;
}



void TeamData::setNumPlayers(int numPlayers) {
    m_numPlayers = numPlayers;
}
void TeamData::setNumGoalKeepers(int numGoalKeepers){
    m_numGoalKeepers = numGoalKeepers;
}

void TeamData::setPoints(int points){
    m_points = points;
}

void TeamData::increasePoints(int points){
    m_points+=points;
}

void TeamData::setTeamAbility(int teamAbility) {
    m_teamAbility = teamAbility;
}

void TeamData::setTeamSpirit(const permutation_t& teamSpirit) {
    m_teamSpirit = teamSpirit;
}

void TeamData::setPtrPlayerReverseRoot(PlayerData *newRoot) {
    m_ptrPlayerReverseRoot = newRoot;
}


void TeamData::increaseTeamAbility(int otherPlayerAbility) {
    m_teamAbility += otherPlayerAbility;
}


void TeamData::increaseTeamFieldsAfterUnion(PlayerData* other) {
    m_numPlayers += 1;
    if (other->isGoalKeeper()) {
        m_numGoalKeepers += 1;
    }
    m_teamAbility += other->getAbility();
    m_teamSpirit = m_teamSpirit * other->getSpirit();
}




///////////////////////------------------------------------------------------------------------------------------



PlayerData::PlayerData(int playerID, const permutation_t& spirit, int gamesPlayed, int ability, int cards, bool goalKeeper) :
    m_playerID(playerID), m_spirit(spirit), m_individualGamesPlayed(gamesPlayed), m_ability(ability), m_cards(cards),

    m_isGoalKeeper(goalKeeper), m_calcPartialSpirit(permutation_t::neutral()), m_calcTotalGamesPlayed(0), m_ptrTeam(nullptr), m_up(nullptr) {}




int PlayerData::getPlayerID() const {
    return m_playerID;
}

permutation_t PlayerData::getSpirit() const {
    return m_spirit;
}

int PlayerData::getIndividualGamesPlayed() const {
    return m_individualGamesPlayed;
}

int PlayerData::getAbility() const {
    return m_ability;
}

int PlayerData::getCards() const {
    return m_cards;
}

Node<TeamData>* PlayerData::getPtrTeam() const {
    return m_ptrTeam;
}

bool PlayerData::isGoalKeeper() const{
    return m_isGoalKeeper;
}

int PlayerData::getCalcTotalGamesPlayed() const {
    return m_calcTotalGamesPlayed;
}


permutation_t PlayerData::getCalcPartialSpirit() const {
    return m_calcPartialSpirit;
}

PlayerData* PlayerData::getUp() const {
    return m_up;
}



void PlayerData::setSpirit(const permutation_t &spirit) {
    m_spirit = spirit;
}

void PlayerData::setIndividualGamesPlayed(int individualGamesPlayed) {
    m_individualGamesPlayed = individualGamesPlayed;
}

void PlayerData::setAbility(int ability) {
    m_ability = ability;
}

void PlayerData::setCards(int cards) {
    m_cards = cards;
}

void PlayerData::setPtrTeam(Node<TeamData>* other) {
    m_ptrTeam = other;
}

void PlayerData::setCalcTotalGamesPlayed(int calcGamesPlayed) {
    m_calcTotalGamesPlayed = calcGamesPlayed;
}

void PlayerData::setCalcPartialSpirit(permutation_t calcPartialSpirit) {
    m_calcPartialSpirit = calcPartialSpirit;
}

void PlayerData::setUp(PlayerData *up) {
    m_up = up;
}

void PlayerData::increaseCalcTotalGamesPlayed(int games){
    m_calcTotalGamesPlayed += games;
}

bool PlayerData::operator<(const PlayerData &other) const {
    return m_playerID < other.m_playerID;
}

bool PlayerData::operator>(const PlayerData &other) const {
    return m_playerID > other.m_playerID;
}



///////////////////////------------------------------------------------------------------------------------------


AbilityDataTeam::AbilityDataTeam(int teamID, int ability) : m_teamID(teamID), m_ability(ability),
                                    m_totalNodesInSubTrees(0) {}


bool AbilityDataTeam::operator<(const AbilityDataTeam &abilityDataTeam) const {
    if (m_ability < abilityDataTeam.m_ability) {
        return true;
    }
    else if (m_ability == abilityDataTeam.m_ability) {
        if (m_teamID < abilityDataTeam.m_teamID) {
            return true;
        }
    }
    return false;
}


bool AbilityDataTeam::operator>(const AbilityDataTeam &abilityDataTeam) const {
    if (m_ability > abilityDataTeam.m_ability) {
        return true;
    }
    else if (m_ability == abilityDataTeam.m_ability) {
        if (m_teamID > abilityDataTeam.m_teamID) {
            return true;
        }
    }
    return false;
}



int AbilityDataTeam::getTeamID() const {
    return m_teamID;
}

int AbilityDataTeam::getTeamAbility() const {
    return m_ability;
}

int AbilityDataTeam::getTotalNodesInSubTrees() const {
    return m_totalNodesInSubTrees;
}

void AbilityDataTeam::setTotalNodesInSubTrees(int totalNodesInSubTrees) {
    m_totalNodesInSubTrees = totalNodesInSubTrees;
}