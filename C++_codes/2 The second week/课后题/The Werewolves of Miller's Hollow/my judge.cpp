#include "judge.hpp"
#include<iostream>
using namespace std;
Judge::Judge(){
  m_players_count = 0;
};
Judge::~Judge(){};
void Judge::on(const Player* player){
  m_players[m_players_count] = player;
  m_players_count++;
}
void Judge::call(Player::Role role){
  std::string name;
  switch(role) {
    case 1 : name = "Villager";break;
    case 2 : name = "Werewolf";break;
    case 3 : name = "Seer";break;
    case 4 : name = "Witch";break;
  case 5 : name = "Hunter";break;
  default : break;
  }
  cout << "Calling: " << name << endl;
  for(int i=0;i<m_players_count;i++){
    if(role == 1) {
      m_players[i]->pretend();
      continue;
}
    else {
      if(role == m_players[i]->role()) m_players[i]->answer();
}
}
}