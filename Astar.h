#ifndef ASTAR_H_
#define ASTAR_H_

#include "stlastar.h" // See header for copyright and usage information
#include <iostream>
#include <stdio.h>
#include <MapSearchNode.h>

#define DEBUG_LISTS 0
#define DEBUG_LIST_LENGTHS_ONLY 0
#define DISPLAY_SOLUTION 1

/*******************   NOTES ON THE INPUT MAP   **************************

   Each element contains an integer from 0 to 5 which indicates the cost 
   of travel across the terrain. Zero means the least possible difficulty 
   in travelling (think ice rink if you can skate) whilst 5 represents the 
   most difficult. 9 indicates that we cannot pass.

**************************************************************************/

std::vector<int> MapSearchNode::map;
int MapSearchNode::MAP_WIDTH;
int MapSearchNode::MAP_HEIGHT;
    

class Astar
{

    int gridSizeX;	
	int gridSizeY;

    AStarSearch<MapSearchNode> astarsearch;
    std::vector<int> access_map;
    int start, target;
    
public:
    Astar() {}
    Astar(std::vector<int> a_map, int sizeX, int sizeY):
        
        gridSizeX(sizeX),
        gridSizeY(sizeY)     
    {
        MapSearchNode::map = a_map;
        MapSearchNode::MAP_WIDTH = sizeX;
        MapSearchNode::MAP_HEIGHT = sizeY;
    }
    
    std::vector<int> astarPath;
    void run(int v_start, int v_target);
    void printSolution();

};


    
void Astar::run(int v_start, int v_target){
    
    start = v_start;
    target = v_target;
    astarPath.clear();
    
    access_map = MapSearchNode::map;

    MapSearchNode nodeStart;
    nodeStart.x = start/gridSizeY;
    nodeStart.y = start%gridSizeY; 

    MapSearchNode nodeEnd;
    nodeEnd.x = target/gridSizeY;						
    nodeEnd.y = target%gridSizeY;

    cout << "Start: " << start << "\tTarget: " << target << endl;

    // Set Start and goal states

    astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

    unsigned int SearchState;
    //unsigned int SearchSteps = 0;

    do
    {
	    SearchState = astarsearch.SearchStep();

	    //SearchSteps++;

#if DEBUG_LISTS

	    //cout << "Steps:" << SearchSteps << "\n";

	    int len = 0;

	    cout << "Open:\n";
	    MapSearchNode *p = astarsearch.GetOpenListStart();
	    while( p )
	    {
		    len++;
#if !DEBUG_LIST_LENGTHS_ONLY			
		    ((MapSearchNode *)p)->PrintNodeInfo();
#endif
		    p = astarsearch.GetOpenListNext();	
	    }

	    cout << "Open list has " << len << " nodes\n";

	    len = 0;

	    cout << "Closed:\n";
	    p = astarsearch.GetClosedListStart();
	    while( p )
	    {
		    len++;
#if !DEBUG_LIST_LENGTHS_ONLY			
		    p->PrintNodeInfo();
#endif			
		    p = astarsearch.GetClosedListNext();
	    }

	    cout << "Closed list has " << len << " nodes\n";
#endif

    }
    while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );

    if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
    {
	    //cout << "Search found goal state\n";

	    MapSearchNode *node = astarsearch.GetSolutionStart();
	    
	    /// Saving solution in Vector
	    do{

		    astarPath.push_back(node->x * gridSizeY+node->y);
		    access_map.at(node->x * gridSizeY+node->y) = -1;
		    node = astarsearch.GetSolutionNext();    
	
	    }while( node != NULL );
	    
#if DISPLAY_SOLUTION
        printSolution();
#endif
	    
	    // Once you're done with the solution you can free the nodes up
	    astarsearch.FreeSolutionNodes();

    }
    else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED ) 
    {
	    cout << "Search terminated. No traversable path found.\n";

    }

    astarsearch.EnsureMemoryFreed();

}

void Astar::printSolution(){

    cout << "Displaying solution (path length=" << astarPath.size() << "):" << endl;		    

    for(int i=0; i<astarPath.size(); i++){
        cout << astarPath.at(i) << " ";	    
    }
    cout << endl;

    for(int i=0; i<access_map.size(); i++){
        if(i%gridSizeY == 0) printf("\n");
        if(i == start) printf("S ");
        else if(i == target) printf("T ");
        else if(access_map.at(i) >=0 && access_map.at(i) <= 5) printf(". ");	
        else if(access_map.at(i) == 9) printf("■ ");
        else if(access_map.at(i) == -1) printf("X ");
	    
    }
    cout << endl;
}

#endif

