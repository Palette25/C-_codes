#include "player.hpp"
#include <iostream>
#include <string>
using std::cout;
using std::endl;

Player::Player() {
  m_name = "";
  m_role = Uninitialized;
}

void Player::init(std::string name, Player::Role role) {
  m_name = name;
  m_role = role;
}

Player::~Player() {}

Player::Role Player::role() const { return m_role; }

void Player::answer() const {
  const std::string role_names[6] =
    { "Uninitialized", "Villager", "Werewolf", "Seer", "Witch", "Hunter" };
  cout << m_name << ": Shh... I am a " << role_names[m_role] << "." << endl;
}

void Player::pretend() const {
  cout << m_name << ": I am the villager!!" << endl;
}