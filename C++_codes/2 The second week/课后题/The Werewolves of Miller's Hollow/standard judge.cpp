#include "judge.hpp"
#include <iostream>
using std::cout;
using std::endl;

Judge::Judge() {
  m_players_count = 0;
}

Judge::~Judge() {}

void Judge::on(const Player* player) {
  m_players[m_players_count++] = player;
}

void Judge::call(Player::Role role) {
  const std::string role_names[6] =
    { "Uninitialized", "Villager", "Werewolf", "Seer", "Witch", "Hunter" };
  cout << "Calling: " << role_names[role] << endl;
  
  for (int i = 0; i < m_players_count; ++i) {
    if (role == Player::Villager) {
      m_players[i]->pretend();
    } else {
      if (m_players[i]->role() == role)
        m_players[i]->answer();
    }
  }
}