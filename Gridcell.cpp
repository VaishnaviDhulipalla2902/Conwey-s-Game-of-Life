#include "Gridcell.h"
#include<stdio.h>

//constructors
Gridcell::Gridcell(){}

Gridcell::Gridcell(int x,int y,unsigned char state) : x(x), y(y), state(state) {}

Gridcell::~Gridcell(){
    x = 0;
    y = 0;
    state = '0';
    //delete[] neighbourhood;
}

Gridcell::Gridcell(const Gridcell &G) : x(G.x),y(G.y),state(G.state){
    for(int i=0;i<8;i++){
        neighbourhood[i] = G.neighbourhood[i];
    }
}

//set functions
void Gridcell::setState(unsigned char newState){
    state = newState;
    return;
}

void Gridcell::setNeighbourhood(unsigned char* newNeighbourhood){
    for(int i=0;i<8;i++){
        neighbourhood[i] = newNeighbourhood[i];
    }
    return;
}

void Gridcell::setX(int xNew){
    x = xNew;
}

void Gridcell::setY(int yNew){
    y = yNew;
}

//public functions
// int Gridcell::count_live_neighbours(){
// 	int count = 0;
// 	for(int i=0;i<8;i++){
// 		if(neighbourhood[i]-'1'==0) count++;
// 	}
// 	return count;
// }


