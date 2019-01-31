#include "Grid.h"
#include<bits/stdc++.h>

using namespace std;

Grid* genGridFromInput(char* filename){

	// printf("filename = %s \n",filename);
	ifstream fin;  
	string line;
    fin.open(filename); 
	getline(fin, line); 
	string delimiter = " ";
	size_t pos = 0;
	string token;
	int rows,cols,generation;
	int count = 0;
	if(fin.is_open()){
		while (count < 3) {
			pos = line.find(delimiter);
			token = line.substr(0, pos);
			if(count == 0) rows = stoi(token);
			else if(count == 1) cols = stoi(token);
			else generation = stoi(token);
			count++;
			line.erase(0, pos + delimiter.length());
		} 
	
		int i = 0;
		Gridcell** gridcells = new Gridcell*[rows] ;
		for (int i = 0 ; i < rows ; i++) 
			gridcells[i] = new Gridcell[cols] ;
		while (i < rows) { 
			getline(fin, line); 
			int j = 0;
			while (j<cols) {
				pos = line.find(delimiter);
				gridcells[i][j].setX(i);
				gridcells[i][j].setY(j);
				token = line.substr(0, pos);
				if(token[0]=='+') gridcells[i][j].setState('1');
				else if(token[0]=='o')gridcells[i][j].setState('0');
				else return NULL;
				line.erase(0, pos + delimiter.length());
				j++;
			} 
			i++;
		} 
		getline(fin, line); 
		Grid* grid = new Grid(rows,cols,gridcells);
		int isInputValid = grid->isInputValid(rows, cols, generation, line);
		if(!isInputValid) return NULL;
		fin.close();
		return grid;
	}
	return NULL;
}

int main(int argc, char** argv) {
	
	Grid* grid = new Grid;
	char* filename = (char*)malloc(100*sizeof(char));
	filename = argv[1];
	grid = genGridFromInput(filename);
	if(!grid){
		ofstream myfile;
		myfile.open ("outfile.txt");
		myfile << "0 0 0 \neof\n";
	} 
	else{
		int numOfGenerations = stoi(argv[2]);
		grid->getNextGenerations(numOfGenerations);
		ofstream myfile;
		myfile.open ("outfile.txt");
		myfile << grid->getRows()<<" "<<grid->getCols()<<" "<< grid->getGeneration()<<"\n";
		myfile << *grid;
		myfile << "eof\n" ; 
		myfile.close();
	}
	return 0;
}