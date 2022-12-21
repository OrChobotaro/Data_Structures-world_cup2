#ifndef DATA_STRUCTURES_EX1_RANKPLAYERDATA_H
#define DATA_STRUCTURES_EX1_RANKPLAYERDATA_H



#include "LinkedList.h"
#include "avlTree.h"
#include "wet2util.h"
#include <iostream>
#include <memory>


class PlayerData;



class TeamData{
public:

    TeamData() = delete;
    TeamData(int teamID);
    TeamData(const TeamData& otherTeam) = default;
    TeamData& operator=(const TeamData& otherTeam) = default;
    bool operator<(const TeamData& other) const;
    bool operator>(const TeamData& other) const;
    ~TeamData() = default;

    int getTeamID() const;
    int getNumPlayers() const;
    int getNumGoalKeepers() const;
    int getTeamPoints() const;
    int getTeamAbility() const;
    permutation_t getTeamSpirit() const;
    PlayerData* getPtrPlayerReverseRoot() const;


    void setNumPlayers(int numPlayers);
    void setNumGoalKeepers(int numGoalKeepers);
    void setPoints(int points);
    void setTeamAbility(int teamAbility);
    void setTeamSpirit(const permutation_t& teamSpirit);
    void setPtrPlayerReverseRoot(PlayerData* newRoot);

    void increaseTeamAbility(int otherPlayerAbility);
    void increaseTeamFieldsAfterUnion(PlayerData* other);


private:
    int m_teamID;
    int m_numPlayers;
    int m_numGoalKeepers;
    int m_points;
    int m_teamAbility;
    permutation_t m_teamSpirit;
    PlayerData* m_ptrPlayerReverseRoot;
};




class PlayerData {
public:
    PlayerData() = delete;
    PlayerData(int playerID, const permutation_t& spirit, int gamesPlayed, int ability, int cards, bool goalKeeper);
    PlayerData(const PlayerData& otherPlayerData) = default;
    PlayerData& operator=(const PlayerData& otherPlayerData) = default;
    bool operator<(const PlayerData& other) const;
    bool operator>(const PlayerData& other) const;
    ~PlayerData() = default;

    int getPlayerID() const;
    permutation_t getSpirit() const;
    int getIndividualGamesPlayed() const;
    int getAbility() const;
    int getCards() const;
    bool isGoalKeeper() const;
    Node<TeamData>* getPtrTeam() const;
    int getCalcTotalGamesPlayed() const;
    permutation_t getCalcPartialSpirit() const;
    PlayerData* getUp() const;


    void setSpirit(const permutation_t& spirit);
    void setIndividualGamesPlayed(int individualGamesPlayed);
    void setAbility(int ability);
    void setCards(int cards);
    void setPtrTeam(Node<TeamData>* node);
    void setCalcTotalGamesPlayed(int calcGamesPlayed);
    void setCalcPartialSpirit(permutation_t calcPartialSpirit);
    void setUp(PlayerData* up);



private:
    int m_playerID;
    permutation_t m_spirit;
    int m_individualGamesPlayed;
    int m_ability;
    int m_cards;
    bool m_isGoalKeeper;
    int m_calcTotalGamesPlayed;
    permutation_t m_calcPartialSpirit;
    Node<TeamData>* m_ptrTeam;
    PlayerData* m_up;
};





class AbilityDataTeam {
public:
    AbilityDataTeam(int teamID, int ability);
    AbilityDataTeam(const AbilityDataTeam& AbilityDataTeam) = default;
    AbilityDataTeam& operator=(const AbilityDataTeam& AbilityDataTeam) = default;
    ~AbilityDataTeam() = default;
    bool operator<(const AbilityDataTeam& abilityDataTeam) const;
    bool operator>(const AbilityDataTeam& abilityDataTeam) const;

    int getTeamID() const;
    int getTeamAbility() const;
    int getTotalNodesInSubTrees() const;

    void setTotalNodesInSubTrees(int totalNodesInSubTrees);

private:
    int m_teamID;
    int m_ability;
    int m_totalNodesInSubTrees;
};


#endif //DATA_STRUCTURES_EX1_RANKPLAYERDATA_H