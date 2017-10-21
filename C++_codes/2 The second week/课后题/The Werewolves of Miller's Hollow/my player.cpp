#include "player.hpp"
#include <iostream>
using namespace std;
Player::Player(){};
Player::~Player(){};
void Player::init(std::string name, Role role){
  m_name = name;
  m_role = role;
}
Player::Role Player::role() const{
  return m_role;
}
void Player::answer() const{
  std::string name;
  switch(m_role) {
    case 1 : name = "Villager";break;
    case 2 : name = "Werewolf";break;
    case 3 : name = "Seer";break;
    case 4 : name = "Witch";break;
  case 5 : name = "Hunter";break;
  default : break;
  }
  cout << m_name << ": Shh... I am a " << name << "." <<endl;
}
void Player::pretend() const{
  cout << m_name << ": I am the villager!!" <<endl;
}