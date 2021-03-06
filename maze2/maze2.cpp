#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <unistd.h>
#include <math.h>
#include "maze2.h"

#include "../maze.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
using std::find;
using std::sort;

MazeNode::MazeNode(){
}

MazeNode::MazeNode(int x, int y){
    x_ = x;
    y_ = y;
}
MazeNode::MazeNode(int x, int y, MazeNodeProperty property){
    x_ = x;
    y_ = y;
    properties_.push_back(property);
}

MazeNode::MazeNode(int x, int y, const vector<MazeNodeProperty>& properties){
    x_ = x;
    y_ = y;
    properties_ = properties;
}

int MazeNode::getX() const{
    return x_;
}

int MazeNode::getY() const{
    return y_;
}

double MazeNode::getGoalDistance() const{
    return goal_distance_;
}

void MazeNode::setGoalDistance(double distance){
    goal_distance_ = distance;
}

bool MazeNode::hasProperty(MazeNodeProperty property){
    for (vector<MazeNodeProperty>::const_iterator i = properties_.begin(); i != properties_.end(); ++i){
        if ((*i) == property) {
            return true;
        }
    }
    return false;
}
void MazeNode::addProperty(MazeNodeProperty property){
    if (!hasProperty(property)){
        properties_.push_back(property);
    }
}

void MazeNode::removeProperty(MazeNodeProperty property){
    for (vector<MazeNodeProperty>::iterator i = properties_.begin(); i != properties_.end(); ++i){
        // No need to care for iterator validity after erase cause we have max 1 property per type
        if ((*i) == property) {
            properties_.erase(i);
            break; // Property erased, continuing the loop is pointless
        }
    }
}

void MazeNode::clearProperties(){
    properties_.clear();
}

void MazeNode::setProperty(MazeNodeProperty property) {
    clearProperties();
    addProperty(property);
}

MazeArc::MazeArc(MazeNode* node, MazeNode* parent){
    node_ = node;
    parent_ = parent;
}

MazeNode* MazeArc::getNode() const{
    return node_;
}

MazeNode* MazeArc::getParent() const{
    return parent_;
}

Maze2::Maze2(){
}
Maze2::Maze2(const string& name){
    name_ = name;
}
void Maze2::LoadFromFile(const string& path){
    ifstream infile(path.c_str());
    if (infile) {
        string s;
        nodes_.clear();
        //Populate the _maze
        int row = 0;
        while (getline(infile,s)) {
            vector<MazeNode> row_vector;
            string::const_iterator string_iter = s.begin();
            int col = 0;
            while (string_iter != s.end()){
                char c = (*string_iter);
                switch (c) {
                    case '#': {
                        MazeNode n = MazeNode(row,col,WALLL);
                        row_vector.push_back(n);
                    } break;
                    case 'S':{
                        MazeNode n = MazeNode(row,col,START);
                        row_vector.push_back(n);
                    } break;
                    case 'G': {
                        MazeNode n = MazeNode(row,col,GOAL);
                        row_vector.push_back(n);
                    } break;
                    default: {
                        MazeNode n = MazeNode(row,col,WALKABLE);
                        row_vector.push_back(n);
                    } break;
                }
                ++string_iter;
                ++col;
            }
            nodes_.push_back(row_vector);
            ++row;
        }
    } else {
        cout << "File " << path << " doesn't exist." << endl;
        exit(1);
    }
    // Initialize interesting nodes for direct access
    initNodesOfInterest();
}

mazeData * Maze2::toArray(mazeData * md){

  for (vector<vector<MazeNode> >::const_iterator row_iterator = nodes_.begin(); row_iterator != nodes_.end(); ++row_iterator){
      for (vector<MazeNode>::const_iterator col_iterator = row_iterator->begin(); col_iterator != row_iterator->end(); ++col_iterator){
          MazeNode node = (*col_iterator);
          if (node.hasProperty(WALLL)){
              //cout << "#";
          }
          if (node.hasProperty(START)){
              //cout << yellow_color_start << "S" << yellow_color_end;
          }
          if (node.hasProperty(GOAL)){
              //cout << green_color_start << "G" << green_color_end;
          }
          if (node.hasProperty(WALKABLE)){
              //cout << " ";
          }
          if (node.hasProperty(VISITED)){
              //cout << red_color_start << "*" << red_color_end;
          }
          if (node.hasProperty(SOLUTION)){
              //cout << blue_color_start << "o" << blue_color_end;
              md->maze_data[node.getY()][node.getX()]=2;
          }
      }
      //cout << endl;
  }

return md;
  //return md;

}
void Maze2::PrintMaze() const{
    const string red_color_start ="\033[1;31m";
    const string red_color_end ="\033[0m";
    const string green_color_start = "\033[1;32m";
    const string green_color_end ="\033[0m";
    const string yellow_color_start = "\033[1;33m";
    const string yellow_color_end ="\033[0m";
    const string blue_color_start = "\033[1;34m";
    const string blue_color_end ="\033[0m";

    for (vector<vector<MazeNode> >::const_iterator row_iterator = nodes_.begin(); row_iterator != nodes_.end(); ++row_iterator){
        for (vector<MazeNode>::const_iterator col_iterator = row_iterator->begin(); col_iterator != row_iterator->end(); ++col_iterator){
            MazeNode node = (*col_iterator);
            if (node.hasProperty(WALLL)){
                cout << "#";
            }
            if (node.hasProperty(START)){
                cout << yellow_color_start << "S" << yellow_color_end;
            }
            if (node.hasProperty(GOAL)){
                cout << green_color_start << "G" << green_color_end;
            }
            if (node.hasProperty(WALKABLE)){
                cout << " ";
            }
            if (node.hasProperty(VISITED)){
                cout << red_color_start << "*" << red_color_end;
            }
            if (node.hasProperty(SOLUTION)){
                cout << blue_color_start << "o" << blue_color_end;
            }
        }
        cout << endl;
    }
}

void Maze2::setName(const std::string& name) {
    name_ = name;
}

std::string Maze2::getName() const{
    return name_;
}

MazeNode* Maze2::getGoalNode() const{
    return goal_node_;
}

MazeNode* Maze2::getStartNode() const{
    return start_node_;
}

MazeNode* Maze2::getNodeAt(unsigned int row, unsigned int col) {
    if ((row < nodes_.size()) && (col < nodes_[row].size())) {
        return &nodes_[row][col];
    }
    return NULL;
}

vector<MazeNode*> Maze2::getSurroundingAt(int row, int col) {
    vector<MazeNode*> surrounding;
    // check if central node exists
    MazeNode* target = getNodeAt(row,col);
    if (target == NULL) {
        return surrounding;
    }
    // fetch surrounding nodes
    MazeNode* top = getNodeAt(row-1,col);
    MazeNode* right = getNodeAt(row,col+1);
    MazeNode* bottom = getNodeAt(row+1,col);
    MazeNode* left = getNodeAt(row, col-1);
    // check for null pointers and return not null node references
    if (top != NULL) { surrounding.push_back(top); }
    if (right != NULL) { surrounding.push_back(right); }
    if (bottom != NULL) { surrounding.push_back(bottom); }
    if (left != NULL) { surrounding.push_back(left); }
    return surrounding;
}

vector<MazeNode*> Maze2::getLegalSurroundingAt(int row, int col) {
    vector<MazeNode*> surrounding = getSurroundingAt(row,col);
    vector<MazeNode*> legal_surrounding;
    for (vector<MazeNode*>::const_iterator iter = surrounding.begin(); iter != surrounding.end(); ++iter ){
        if ((*(*iter)).hasProperty(WALKABLE)) {
            legal_surrounding.push_back((*iter));
        } else if ((*(*iter)).hasProperty(GOAL)) {
            legal_surrounding.push_back((*iter));
        }
    }
    return legal_surrounding;
}

void Maze2::initNodesOfInterest() {
    //Set start node and goal node
    for (vector<vector<MazeNode> >::iterator row_iterator = nodes_.begin(); row_iterator != nodes_.end(); ++row_iterator){
        for (vector<MazeNode>::iterator col_iterator = row_iterator->begin(); col_iterator != row_iterator->end(); ++col_iterator){
            if (col_iterator->hasProperty(GOAL)){
                goal_node_ = &(*col_iterator);
            }
            if (col_iterator->hasProperty(START)){
                start_node_ = &(*col_iterator);
            }
        }
    }
    // Set distance from goal for every node
    for (vector<vector<MazeNode> >::iterator row_iterator = nodes_.begin(); row_iterator != nodes_.end(); ++row_iterator){
        for (vector<MazeNode>::iterator col_iterator = row_iterator->begin(); col_iterator != row_iterator->end(); ++col_iterator){
            int current_x,current_y,goal_x,goal_y;
            current_x = col_iterator->getX();
            current_y = col_iterator->getY();
            goal_x = goal_node_->getX();
            goal_y = goal_node_->getY();
            double distance = sqrt(pow((current_x-goal_x),2)+pow((current_y-goal_y),2));
            col_iterator->setGoalDistance(distance);
        }
    }
}

vector<MazeArc> Maze2::solve(SearchStrategy strategy, bool interactive){
    return solve(start_node_, strategy, interactive);
}

vector<MazeArc> Maze2::solve(MazeNode* start_node, SearchStrategy strategy, bool interactive){
    vector<MazeArc> closed_arcs;
    const int interactive_mode_wait_time = 40000;
    switch (strategy){
        case DFS:{
            vector<MazeArc> open_arcs;
            MazeArc current_arc = MazeArc(start_node, NULL);
            open_arcs.push_back(current_arc);
            while (open_arcs.size() != 0) {
                popArcDfs(current_arc, open_arcs);
                closed_arcs.push_back(current_arc);
                if (!(current_arc.getNode()->hasProperty(START) ||current_arc.getNode()->hasProperty(GOAL))){
                    current_arc.getNode()->setProperty(VISITED);
                }
                if (interactive) printAndWaitFor(interactive_mode_wait_time);
                if (current_arc.getNode()->hasProperty(GOAL)) {
                    closed_arcs.push_back(current_arc);
                    return closed_arcs;
                } else {
                    expandArcs(current_arc, open_arcs, closed_arcs);
                }
            }
        } break;
        case BFS:{
            //TODO: needs optimizations... vector is not the appropriate container
            vector<MazeArc> open_arcs;
            vector<MazeArc> closed_arcs;
            MazeArc current_arc = MazeArc(start_node, NULL);
            open_arcs.push_back(current_arc);
            while (open_arcs.size() != 0) {
                popArcBfs(current_arc, open_arcs);
                closed_arcs.push_back(current_arc);
                if (!(current_arc.getNode()->hasProperty(START) ||current_arc.getNode()->hasProperty(GOAL))){
                    current_arc.getNode()->setProperty(VISITED);
                }
                // If in interactive mode print the maze and wait
                if (interactive) printAndWaitFor(interactive_mode_wait_time);
                if (current_arc.getNode()->hasProperty(GOAL)) {
                    closed_arcs.push_back(current_arc);
                    return closed_arcs;
                } else {
                    expandArcs(current_arc, open_arcs, closed_arcs);
                }
            }
        };break;
        case BEFS:{
            vector<MazeArc> open_arcs;
            vector<MazeArc> closed_arcs;
            MazeArc current_arc = MazeArc(start_node, NULL);
            open_arcs.push_back(current_arc);
            while (open_arcs.size() != 0) {
                popArcsBefs(current_arc, open_arcs);
                closed_arcs.push_back(current_arc);
                if (!(current_arc.getNode()->hasProperty(START) ||current_arc.getNode()->hasProperty(GOAL))){
                    current_arc.getNode()->setProperty(VISITED);
                }
                if (interactive) printAndWaitFor(interactive_mode_wait_time);
                if (current_arc.getNode()->hasProperty(GOAL)) {
                    closed_arcs.push_back(current_arc);
                    return closed_arcs;
                } else {
                    expandArcs(current_arc, open_arcs, closed_arcs);
                }
            }
        } break;
    }
    closed_arcs.clear();
    return closed_arcs;
}

bool Maze2::compareArcDistance(const MazeArc& first, const MazeArc& second) {
    return second.getNode()->getGoalDistance() < first.getNode()->getGoalDistance();
}

void Maze2::popArcDfs(MazeArc& current_arc, vector<MazeArc>& open_arcs){
    current_arc = (*(open_arcs.end()-1));
    open_arcs.erase(open_arcs.end()-1);
}

void Maze2::popArcBfs(MazeArc& current_arc, vector<MazeArc>& open_arcs){
    current_arc = (*(open_arcs.begin()));
    open_arcs.erase(open_arcs.begin());
}

void Maze2::popArcsBefs(MazeArc& current_arc, vector<MazeArc>& open_arcs){
    sort(open_arcs.begin(), open_arcs.end(), Maze2::compareArcDistance);
    current_arc = (*(open_arcs.end()-1));
    open_arcs.erase(open_arcs.end()-1);
}

void Maze2::printAndWaitFor(unsigned int useconds) const{
    usleep(useconds);
    const int empty_lines_number = 50;
    for (int i = 0; i!=empty_lines_number; ++i){
        cout << endl;
    }
    PrintMaze();
}

void Maze2::expandArcs(const MazeArc &current_arc, std::vector<MazeArc> &open_arcs, std::vector<MazeArc> &closed_arcs){
    vector<MazeNode*> surrounding_nodes = getLegalSurroundingAt(current_arc.getNode()->getX(), current_arc.getNode()->getY());
    for (vector<MazeNode*>::iterator nodes_iter = surrounding_nodes.begin(); nodes_iter != surrounding_nodes.end(); ++nodes_iter){
        bool visited = false;
        for (vector<MazeArc>::iterator open_arcs_iter = open_arcs.begin(); open_arcs_iter != open_arcs.end(); ++open_arcs_iter){
            if ((*nodes_iter) == (open_arcs_iter->getNode())){
                visited = true;
            }
        }
        for (vector<MazeArc>::iterator closed_arcs_iter = closed_arcs.begin(); closed_arcs_iter != closed_arcs.end(); ++closed_arcs_iter){
            if ((*nodes_iter) == (closed_arcs_iter->getNode())){
                visited = true;
            }
        }
        if (!visited) {
            MazeArc arc = MazeArc((*nodes_iter), current_arc.getNode());
            open_arcs.push_back(arc);
        }
    }
}

void Maze2::setSolution(const vector<MazeArc>& closed_arcs, bool interactive) {
    const int interactive_mode_wait_time = 40000;
    if (closed_arcs.size() != 0) {
        solution_path_lenght_ = 0;
        MazeArc current_arc = *(closed_arcs.rbegin());
        while (current_arc.getParent() != NULL) {
            if (!(current_arc.getNode()->hasProperty(START) ||current_arc.getNode()->hasProperty(GOAL))){
                current_arc.getNode()->setProperty(SOLUTION);
                if (interactive) printAndWaitFor(interactive_mode_wait_time);
                ++solution_path_lenght_;
            }
            for (vector<MazeArc>::const_iterator iter = closed_arcs.begin(); iter != closed_arcs.end(); ++iter){
                MazeNode* current_parent = current_arc.getParent();
                MazeNode* parent_node = iter->getNode();
                if (current_parent == parent_node) {
                    current_arc = (*iter);
                    break;
                }
            }
        }
    }
}

int Maze2::getSolutionSathLenght() const{
    return solution_path_lenght_;
}
