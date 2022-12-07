#include "AdjacencyList.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

void RemoveMarks(string& word) {

    bool wasPrevMark = false;
    for (int i = 0; i < word.length(); i++) {
        char curr = word.at(i);

        if (curr == '"' && !wasPrevMark) {
            word.erase(word.begin() + i);
            wasPrevMark = true;
            i--;
        }
        else wasPrevMark = false;
    }
}

int main() {

    AdjacencyList graph;
    vector<string> row;
    vector<vector<string>> content;
    string line, word;

    // file pointer
    ifstream file;

    // opens an existing csv file or creates a new file.
    file.open("FIRES.csv", ios::in);
    if (file.is_open())
    {
        int count = 0;
        while (getline(file, line) && count < 35)
        {
            row.clear();
            stringstream str(line);

          
            while (getline(str, word, ',')) {

                if (word.find("\"") != string::npos) {
                    RemoveMarks(word);
                }

                if (row.size() < 3 && word.find(",") != string::npos)
                {
                    while (word.find(",") != string::npos)
                        word.erase(word.begin() + word.find(","));
                }


                row.push_back(word);
            }

            if (row.size() == 3) {
                if (content.size() == 0)
                    content.push_back(row);
                else {
                    bool isUnique = true;
                    for (int i = 0; i < content.size(); i++) {
                        if ((row.at(2) == content.at(i).at(2))) {
                            isUnique = false;
                            break;
                        }
                    }
                    if (isUnique)
                        content.push_back(row);
                }
             
               
            }
            count++;
        }
        file.close();

    }
    else {
        cout << "Could not open the file\n";
        return -1;
    }
    
    for (int i = 0; i < content.size(); i++) {
        vector<string> curr = content.at(i);
        graph.insertCounty(curr.at(0), curr.at(1), curr.at(2));
    }
    graph.insertEdges();
    
    bool run = true;
    cout << "Welcome to Wildfire Analysis!" << endl;
    cout << "-----------------------------" << endl;
    cout << "------by Emily Anderson------" << endl;
    cout << "-------and Jesse Maki--------" << endl;
    cout << "-----------------------------" << endl;

    while (run) {
        cout << "Please input starting county: " << endl;
        string county1;
        getline(cin, county1);

        cout << "Please input destination county: " << endl;
        string county2;
        getline(cin, county2);

        cout << "Counties: " << county1 << " and " << county2 << endl << endl;

        cout << "Select an option: " << endl;
        cout << "1. Perform Breadth-First Search between Source and Destination\n";
        cout << "2. Perform Depth-First Search between Source and Destination\n";

        int search;
        cin >> search;

        if (!(search == 1 || search == 2)) {
            bool valid = false;
            while (!valid) {
                cout << "Please input a valid option:" << endl;
                cin >> search;
                if (search == 1 || search == 2 || search == 3)
                    valid = true;
            }
        }
           
        if (search == 1) {
            cout << "Performing Breadth-First Search" << endl;
            auto start = high_resolution_clock::now();
            graph.bfs(county1, county2);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Time for BFS: " << duration.count() << " microseconds" << endl;
        }
        if (search == 2) {
            vector<string> path;
            cout << "Performing Depth-First Search" << endl;
            auto start = high_resolution_clock::now();
            graph.dfs(county1, county2, path);
            path.push_back(county2);
            graph.findTotalDistance(path);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Time for DFS: " << duration.count() << " microseconds" << endl;
        }

        cout << "Run again? Enter 1 for yes, 0 for no: " << endl;
        int repeat;
        cin >> repeat;
        cin.ignore();

        if (repeat == 0)
            run = false;
    }

    return -1;
}
