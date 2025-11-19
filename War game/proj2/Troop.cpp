// File: troop.cpp
// project: CMSC 202 project 2, Fall 2017
// Author: Steve Cabral Tchounkeu Nana
// E-mail: steve20@umbc.edu
// Section: 17
// Date: 10/09/2017
//
// This file contains the main program for the file Troop.h

#include "Troop.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

Troop::Troop(string name, int health, int damage, string target, bool isFlying){
  m_name = name;
  m_health = health;
  m_damage = damage;
  m_target = target;
  m_isFlying = isFlying;
  
}


string Troop::GetName(){
  return m_name;
}

void Troop::SetName(string name){
  m_name = name;
}

int Troop::GetHealth(){
  return m_health;
}

void Troop::SetHealth(int health){
  m_health = health;
}

int Troop::GetDamage(){
  return m_damage;
}

string Troop::GetTarget(){
  return m_target;
}

bool Troop::GetIsFlying(){ 
  return m_isFlying;
}

void Troop::AttackTroop(Troop& targetTroop){

  //if the player can only attack the ground and the target is flying 
  //notify the user
  if(m_target == "Ground" and targetTroop.m_isFlying == 1){
    cout << "Your troop cannot attack a flying troop" << endl;
  }

  //if the player can only attack the ground and the target is on the 
  //ground get the damage and modify the health
  else if(m_target == "Ground" and targetTroop.m_isFlying == 0){
    cout << m_name << " attacks " << targetTroop.GetName() << " on the ground!" << endl;
    cout << "Damage occuring " << m_damage <<endl;
    targetTroop.m_health = (targetTroop.m_health - m_damage);//modify health
  }

  //if the troop can attack both, get the damage and modify the health 
  else if(m_target == "Both"){
    cout << m_name << " attacks "<< targetTroop.GetName() << " on the ground!" << endl;
    cout << "Damage occuring " << m_damage <<endl;
    targetTroop.m_health = (targetTroop.m_health - m_damage);// modify health
  }
  
}
