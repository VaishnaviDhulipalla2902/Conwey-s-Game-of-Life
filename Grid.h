#include "Gridcell.h"

#ifndef Grid_H_
#define Grid_H_

#include <iostream>
#include <string>

using namespace std;

class Grid{
    public:
        //constructors
        Grid();
        Grid(int rows, int cols, Gridcell** gridcells) ; // constructor //
        ~Grid() ; // destructor //
        Grid(const Grid&) ; // copy constructor //
        //friend function
        friend std::ostream& operator<< (std::ostream &, Grid &) ;
        //getters
        int getRows(){return rows;}
        int getCols(){return cols;}
        Gridcell** getGridcells(){return gridcells;}
        //setters
        void setRows(int rows);
        void setCols(int cols);
        void setGridcells(Gridcell** cells);
        //public functions
        void generate_initial_state();
        void update_neighbourhood();
        int update_grid();
        void print_grid();
        void getNextGenerations(int numOfGenerations);
        int getGeneration(){return generation;}
        int count_total_neighbours(){
            int sum = 0;
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    int num = gridcells[i][j].count_live_neighbours();
                    sum += num;
                }
            }
            return sum;
        }
        int isValid(Gridcell** gridCells){
            for(int i=0;i<rows;i++){
                if(gridCells[i][0].getState() != '0' || gridCells[i][cols-1].getState() != '0') return 0;
            }
            for(int i=0;i<cols;i++){
                if(gridCells[0][i].getState() != '0' || gridCells[rows-1][i].getState() != '0') return 0;
            }
            return 1;
        }
        int isInputValid(int rows, int columns, int generation,string lastline){

            return rows != 0 && columns != 0 && generation == 0 && lastline == "eof";
        }
    private:
        Gridcell** gridcells;
        int rows,cols,generation;
    protected: 
};

#endif