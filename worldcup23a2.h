// 
// 234218 Data Structures 1.
// Semester: 2023A (winter).
// Wet Exercise #2.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef WORLDCUP23A2_H_
#define WORLDCUP23A2_H_

#include "wet2util.h"
#include "UnionFindData.h"
#include "hashTable.h"
#include "RankTree.h"


class world_cup_t {

public: // todo: change to private!!!
    std::shared_ptr<AvlTree<TeamData>> m_teamTree;
    std::shared_ptr<HashTable> m_hashTable;
    std::shared_ptr<RankTree> m_rankAbilityTree;
    int m_numberOfTeams;

    Node<TeamData>* findTeam(PlayerData* player);
    Node<TeamData>* unionTeamsAux(Node<TeamData>* team1, Node<TeamData>* team2);


    bool unionPlayerToTeam(int playerID, Node<TeamData>* teamNode);
    void unionPlayerToEmptyTeam(PlayerData* playerNode, Node<TeamData>* teamNode);
    void unionPlayerToRegularTeam(PlayerData* playerNode, Node<TeamData>* teamNode);
    void unionBigBuyerTeamToSmallTeam(Node<TeamData>* bigTeamNode, Node<TeamData>* smallTeamNode);
    void unionSmallBuyerTeamToBigTeam(Node<TeamData>* bigTeamNode, Node<TeamData>** smallTeamNode);
    Node<TeamData>* findTeamInTeamTree(int teamID, Node<TeamData>* root);

    permutation_t calcMultiple(PlayerData* player);


	

	// <DO-NOT-MODIFY> {


	world_cup_t();
	virtual ~world_cup_t();
	
	StatusType add_team(int teamId);
	
	StatusType remove_team(int teamId);
	
	StatusType add_player(int playerId, int teamId,
	                      const permutation_t &spirit, int gamesPlayed,
	                      int ability, int cards, bool goalKeeper);
	
	output_t<int> play_match(int teamId1, int teamId2);
	
	output_t<int> num_played_games_for_player(int playerId);
	
	StatusType add_player_cards(int playerId, int cards);
	
	output_t<int> get_player_cards(int playerId);
	
	output_t<int> get_team_points(int teamId);
	
	output_t<int> get_ith_pointless_ability(int i);
	
	output_t<permutation_t> get_partial_spirit(int playerId);
	
	StatusType buy_team(int teamId1, int teamId2);
	
	// } </DO-NOT-MODIFY>
};

#endif // WORLDCUP23A1_H_
