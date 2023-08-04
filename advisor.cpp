#include <map>
#include <set>
#include <iostream>
#include <limits>
#include "advisor.h"


/*
    Check if the target opponent is in the range of the individual
*/
bool Advisor::opponent_in_range(const Individual* individual, const Individual* opponent){

    int range = Individual::statistics.find(individual->type)->second.find("range")->second;

    int distance_to_opponent = abs(opponent->x_coordinate - individual->x_coordinate) + abs(opponent->y_coordinate - individual->y_coordinate);

    return range >= distance_to_opponent;
}


/*
    Find any opponent that is in the range of the individual
*/
const Individual* Advisor::find_opponent_in_range(const Individual* individual, const std::vector<const Individual*>&  opponent_individuals){
    for(const Individual* opponent : opponent_individuals){
        if(opponent_in_range(individual, opponent)) return opponent;
    }
    return nullptr;
}



/*
    Find next x,y coordinates the individual can move on to reach the target.
    A* algorithm implementation
*/

// Sadly cutting all those calculations to the next move
std::pair<int, int> Advisor::find_furthest_point_in_path_within_range(const Individual* individual, const Individual* target, const std::vector<std::vector<cell>>& cell_details){
    // Go from the target through the calculated path towards the individual and Find the farthest possible point you can move within the range of the individual
    int i = target->x_coordinate;
    int j = target->y_coordinate;
    
    while(cell_details[i][j].parent_i != -1){
        if(calculateDistance(individual->x_coordinate, individual->y_coordinate, std::make_pair(i, j)) <= Individual::statistics.find(individual->type)->second.find("range")->second){
            return std::make_pair(i,j);
        }

        i = cell_details[i][j].parent_i;
        j = cell_details[i][j].parent_j; 
    }

    return std::make_pair(-1,-1);
}

std::pair<int, int> Advisor::find_next_step(const Individual* individual, const Individual* target, std::vector<const Individual*>&  opponent_individuals){
    /*
        Create grid map following the rules:
        - obstacles cells are blocked
        - cells with opponent's individuals are blocked 
    */
    
    // game map format is a rectangle, non empty
    int row_nr = game_map.size();
    int col_nr = game_map[0].size();
    
    // grid
    std::vector<std::vector<int>> grid(row_nr , std::vector<int> (col_nr, 0)); 

    for(int i=0; i<row_nr; i++){
        for(int j=0; j<col_nr; j++){
            if(game_map[i][j] == '9') grid[i][j] = 1;
        }
    }

    for(const Individual* i : opponent_individuals){
        grid[i->x_coordinate][i->y_coordinate] = 1;
    }

    // source and destination
    std::pair<int, int> src = std::make_pair(individual->x_coordinate, individual->y_coordinate);
 
    std::pair<int, int>  dest = std::make_pair(target->x_coordinate, target->y_coordinate);

    // closed list
    std::vector<std::vector<bool>> closed_list(row_nr , std::vector<bool> (col_nr, false));

    // details list
    std::vector<std::vector<cell>> cell_details(row_nr , std::vector<cell> (col_nr));

    for (int i = 0; i < row_nr; i++) {
        for (int j = 0; j < col_nr; j++) {
            cell_details[i][j].f = std::numeric_limits<unsigned int>::max();
            cell_details[i][j].g = std::numeric_limits<unsigned int>::max();
            cell_details[i][j].h = std::numeric_limits<unsigned int>::max();
            cell_details[i][j].parent_i = -1;
            cell_details[i][j].parent_j = -1;
        }
    }
 
    // Initialising the parameters of the starting node
    cell_details[src.first][src.second].f = 0;
    cell_details[src.first][src.second].g = 0;
    cell_details[src.first][src.second].h = 0;

    std::set< std::pair<int, std::pair<int, int>> > open_list;
 
    open_list.insert(std::make_pair(0, std::make_pair(src.first, src.second)));

    bool foundDest = false;

    while (!open_list.empty()) {
        std::pair<int, std::pair<int, int>> p = *open_list.begin();
 
        // Remove this vertex from the open list
        open_list.erase(open_list.begin());
 
        // Add this vertex to the closed list
        int x = p.second.first;
        int y = p.second.second;
        closed_list[x][y] = true;

        unsigned int gNew, hNew, fNew;
 
        // Four possible moves left, up, right, down
        std::pair<int,int> shifts[4] = {{-1,0}, {0, 1}, {1, 0}, {0,-1}};

        for(std::pair<int,int>& shift : shifts){
            // Only process this cell if this is a valid one
            if (isValid(x + shift.first, y + shift.second, row_nr, col_nr) ) {
                // If the destination cell is the same as the
                // current successor
                if (isDestination(x + shift.first, y + shift.second, dest)) {
                    // Set the Parent of the destination cell
                    cell_details[x + shift.first][y + shift.second].parent_i = x;
                    cell_details[x + shift.first][y + shift.second].parent_j = y;
                    foundDest = true;


                }
                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                else if (!closed_list[x + shift.first][y + shift.second] && grid[x + shift.first][y + shift.second]==0) {
                    gNew = cell_details[x][y].g + 1;
                    hNew = calculateDistance(x + shift.first, y + shift.second, dest);
                    fNew = gNew + hNew;
    
                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cell_details[x + shift.first][y + shift.second].f  > fNew) {
                        open_list.insert(std::make_pair(fNew, std::make_pair(x + shift.first, y + shift.second)));
    
                        // Update the details of this cell
                        cell_details[x + shift.first][y + shift.second].f = fNew;
                        cell_details[x + shift.first][y + shift.second].g = gNew;
                        cell_details[x + shift.first][y + shift.second].h = hNew;
                        cell_details[x + shift.first][y + shift.second].parent_i = x;
                        cell_details[x + shift.first][y + shift.second].parent_j = y;
                    }
                }
            }
        }//end for
    
        

    }//end while


    // something went wrong
    return std::make_pair(-1, -1);
}

/*
    End of
    Find next x,y coordinates the individual can move on to reach the target.
    A* implementation
    -----------------------------------------------------------------------------
*/


std::vector<std::unique_ptr<Command>> Advisor::advise(){
    std::vector<std::unique_ptr<Command>> commands;

    commands.push_back(std::make_unique<Move>(60, 1, 10, 12));
    commands.push_back(std::make_unique<Attack>(50, 1, 2));
    commands.push_back(std::make_unique<Build>(70, 1, 'C'));


    /*
        Naive attack strategy
        If player's individual can attack the base then attack.
        Attack advisor adds constant priority to every command as attack is the main objective.
        If opponent's individual is within the attack range, then check if one is stronger. When stronger then push to base else attack and fight.  
        Else push the base.
    */ 

    char player = 'P';
    char opponent = 'E';


    // Split individuals
    // It is safe using raw pointers, because individuals exists during program lifetime in the Reader
    const Individual* player_base;
    const Individual* opponent_base;
    
    std::vector<const Individual*>  opponent_individuals;
    std::vector<const Individual*> player_individuals;


    for(const Individual& i : individuals){
        if(i.owner == player){
            if(i.type != 'B') player_individuals.push_back(&i);
            else player_base = &i;
        }
        else{
                if(i.type != 'B') opponent_individuals.push_back(&i);
                else opponent_base = &i;
        }
    }

    
    for(const Individual* i : player_individuals){
        
    }

    return commands;
}