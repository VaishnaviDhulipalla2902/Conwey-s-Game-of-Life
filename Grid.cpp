#include "Grid.h"
#include <stdlib.h>
#include <time.h>
#include<iostream>
#include "Gridcell.h"

using namespace std;

//constructors
Grid::Grid(){}

Grid::Grid(int r,int c,Gridcell** cells):rows(r),cols(c){
	
	gridcells = new Gridcell*[rows] ;
    generation = 0;
	for (int i = 0 ; i < rows ; i++) 
        gridcells[i] = new Gridcell[cols] ;
	
	for (int i = 0; i < rows; i++) 
        for (int j = 0; j < cols; j++) 
	        gridcells[i][j] = cells[i][j];
	this->update_neighbourhood();
}


Grid::~Grid(){
    for(int i=0;i<rows;i++){
        delete[] gridcells[i];
    }
    delete[] gridcells;
    rows = 0;
    cols = 0;
}

Grid::Grid(const Grid& G):rows(G.rows),cols(G.cols){
    gridcells = new Gridcell*[rows] ;
    for (int i = 0 ; i < rows ; i++) 
        gridcells[i] = new Gridcell[cols] ;
    
    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < cols; j++) 
	        gridcells[i][j] = G.gridcells[i][j];
}

void Grid::setRows(int rowsNew){
    rows = rowsNew;
}

void Grid::setCols(int colsNew){
    cols = colsNew;
}

void Grid::setGridcells(Gridcell** cells){
    
    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < cols; j++) 
	        gridcells[i][j] = cells[i][j];

	this->update_neighbourhood();
}

// int Grid::count_total_neighbours(){
// 	int sum = 0;
// 	for(int i=0;i<rows;i++){
// 		for(int j=0;j<cols;j++){
// 			int num = gridcells[i][j].count_live_neighbours();
// 			sum += num;
// 		}
// 	}
// 	return sum;
// }


void Grid::update_neighbourhood(){
    unsigned char neighbourhood[8];
    for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			if(j!=cols-1)neighbourhood[0] = gridcells[i][j+1].getState();
			else neighbourhood[0] = '0';
			if(j!=cols-1 && i!=0)neighbourhood[1] = gridcells[i-1][j+1].getState();
			else neighbourhood[1] = '0';
			if(i!=0)neighbourhood[2] = gridcells[i-1][j].getState();
			else neighbourhood[2] = '0';
			if(j!=0 && i!=0)neighbourhood[3] = gridcells[i-1][j-1].getState();
			else neighbourhood[3] = '0';
			if(j!=0)neighbourhood[4] = gridcells[i][j-1].getState();
			else neighbourhood[4] = '0';
			if(j!=0 && i!=rows-1)neighbourhood[5] = gridcells[i+1][j-1].getState();
			else neighbourhood[5] = '0';
			if(i!=rows-1)neighbourhood[6] = gridcells[i+1][j].getState();
			else neighbourhood[6] = '0';
			if(j!=cols-1 && i!=rows-1)neighbourhood[7] = gridcells[i+1][j+1].getState();
			else neighbourhood[7] = '0';
			gridcells[i][j].setNeighbourhood(neighbourhood);
		}
	}
}

void Grid::generate_initial_state(){
	srand(time(0));
    for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			gridcells[i][j].setX(i);
			gridcells[i][j].setY(j); 
			if(i==0 || j==0 || i==rows-1 || j==cols-1){
				gridcells[i][j].setState('0');
			}
			else{
				int random = rand()%2;
				if(random) gridcells[i][j].setState('1');
				else gridcells[i][j].setState('0');
			}
		}
	}
	this->update_neighbourhood();
}

int Grid::update_grid(){
    Gridcell** newGrid = new Gridcell*[rows] ;
    for (int i = 0 ; i < rows ; i++) 
        newGrid[i] = new Gridcell[cols] ;
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			int num = gridcells[i][j].count_live_neighbours();
			if(gridcells[i][j].getState()-'0'==0){
				if(num==3) newGrid[i][j].setState ('1');
				else newGrid[i][j]. setState ('0');
			}
			else{
				if(num==2 || num==3){
					newGrid[i][j].setState('1');
				}
				else{
					newGrid[i][j].setState('0');
				}
			}
		}
	}
	int isValid = this->isValid(newGrid);
	if(isValid){
		this->setGridcells(newGrid);
		// this->update_neighbourhood();
		return 1;
	}
	else{
		return 0;
	}
}

void Grid::getNextGenerations(int numOfGenerations){
	int isValid = this->isValid(this->gridcells);
	if(isValid){
		for(int i=0;i<numOfGenerations;i++){
			isValid = this->update_grid();
			if(!isValid) return ;
			generation++;
		}
	}
}

void Grid::print_grid(){
    for(int j=0;j<rows;j++){
        for(int k=0;k<cols;k++){
            // std:: cout<<"%c ",gridcells[j][k].getState();
			printf("%c ",gridcells[j][k].getState());
        }
        std:: cout<<"\n";
    }
    std:: cout<<"\n";
};


// Friend functions //
std::ostream& operator<<(std::ostream& os, Grid& g) {

	for(int j=0;j<g.rows;j++){
        for(int k=0;k<g.cols;k++){
			if(g.gridcells[j][k].getState() == '0') os << "o ";
			else os << "+ ";
			//os << g.gridcells[j][k].getState() << " " ;
        }
        os << std::endl;
    }
  	return os;
}

