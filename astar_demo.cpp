
#include "stlastar.h" // See header for copyright and usage information
#include <iostream>
#include <stdio.h>
#include <Astar.h>


/*******************   NOTES ON THE INPUT MAP   **************************

   Each element contains an integer from 0 to 5 which indicates the cost 
   of travel across the terrain. Zero means the least possible difficulty 
   in travelling (think ice rink if you can skate) whilst 5 represents the 
   most difficult. 9 indicates that we cannot pass.

**************************************************************************/

int aMap[] = {

//  0   2   4   6   8  10  12  14  16  18
//    1   3   5   7   9  11  13  15  17  19
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,   // 00
	1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,1,   // 01
	1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 02
	1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 03
	1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1,   // 04
	1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1,   // 05
	1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1,   // 06
	1,9,9,9,9,9,9,9,9,1,1,1,9,9,9,9,9,9,9,1,   // 07
	1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,   // 08
	1,9,1,9,9,9,9,9,9,9,1,1,9,9,9,9,9,9,9,1,   // 09
	1,9,1,1,1,1,9,1,1,9,1,1,1,1,1,1,1,1,1,1,   // 10
	1,9,9,9,9,9,1,9,1,9,1,9,9,9,9,9,1,1,1,1,   // 11
	1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 12
	1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 13
	1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1,   // 14
	1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1,   // 15
	1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1,   // 16
	1,1,9,9,9,9,9,9,9,1,1,1,9,9,9,1,9,9,9,9,   // 17
	1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,   // 18
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,   // 19

};


int main( int argc, char *argv[] )
{

    std::vector<int> access_map(aMap, aMap + sizeof(aMap)/sizeof(int));
    std::vector<int> solutionPath;
    
    Astar myAstar(access_map, 20, 20);
    
    //First run, printing solution using the Astar method
    myAstar.run(43,380);
    cout << "[Using class method] ";
    myAstar.printSolution();  
    cout << endl;
    
    //Second run, printing solution by getting the path
    myAstar.run(380,43);   
    solutionPath = myAstar.path;  
    cout << "[Getting Path] Path from 380 to 43:" << endl;    
    for(int i=0; i<solutionPath.size();i++){
        cout << " " << solutionPath.at(i);  
    }
    cout << endl;
   
	

    return 0;
}

