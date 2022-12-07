#include "AdjacencyList.h"
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>
#define PI 3.14159265358979323846
#define EARTH_RADIUS 6372.79756085
#define DEGREES_RADIANS PI / 180
using namespace std;


float AdjacencyList::findDistance(county &src, county &dest) {

    //converst lat/long to radians
    float lat1 = stof(src.latitude) * DEGREES_RADIANS;
    float lat2 = stof(dest.latitude) * DEGREES_RADIANS;
    float long1 = stof(src.longitude) * DEGREES_RADIANS;
    float long2 = stof(dest.longitude) * DEGREES_RADIANS;

    double haversine; //haversine formula for distance between points on a sphere (in km) https://en.wikipedia.org/wiki/Haversine_formula
    float temp;
    float distance;

    haversine = (pow(sin((1.0 / 2) * (lat2 - lat1)), 2)) + ((cos(lat1)) * (cos(lat2)) * (pow(sin((1.0 / 2) * (long2 - long1)), 2)));
    temp = 2 * asin(min(1.0, sqrt(haversine)));
    distance = EARTH_RADIUS * temp;

    return distance;

}

void AdjacencyList::findTotalDistance(vector<string> &path) {
    float totalDistance = 0;

    for (int i = 0; i < path.size() - 1; i++) {
        cout << path.at(i) << "->";
        totalDistance = totalDistance + findDistance(counties[path.at(i)], counties[path.at(i + 1)]);
    }
    cout << path.at(path.size() - 1) << endl << "Total Distance:" << totalDistance << "!" << endl;
}

void AdjacencyList::insertCounty(string latitude, string longitude, string countyName) {
    county newCounty(latitude, longitude, countyName);

    counties.insert(make_pair(countyName, newCounty));
}

void AdjacencyList::insertEdges() {
    for (auto it : counties) {
        for (auto again : counties) {
            if (counties[it.first].countyName != counties[again.first].countyName)
                counties[it.first].edges.push_back(make_pair(counties[again.first], findDistance(it.second, again.second)));
        }
    }
    return;
}



void AdjacencyList::bfs(string src, string dest) {
    queue<string> q;
    q.push(src);

    map<string, bool> visited;
    map<string, county> parents;

    bool destReached = false;
    float totalDistance = 0;

    while (!q.empty() && !destReached) {
        string top = q.front();
        cout << top << "->";
        q.pop();

        for (auto it : counties) {
            if (!visited[it.first] && it.first != src) {
                visited[it.first] = true;
                q.push(it.first);

                totalDistance += findDistance(counties[src], counties[it.first]);

                if (it.first == dest) {
                    destReached = true;
                    break;
                }
                else
                    cout << it.first << "->";
            }
        }
    }
    cout << dest << "!" << endl << "Total Distance: " << totalDistance << "km!" << endl;

}

void AdjacencyList::dfs(string src, string dest, vector<string> &path) {

    unordered_map<string, bool> visited;

    if (src != dest) {
        visited[src] = true;
        path.push_back(src);
        for (auto iter : counties) {
            if (!visited[iter.first]) {
                if (iter.first == dest) {
                    break;
                }
                else {
                    dfs(iter.first, dest, path);
                }
            }
        }
    }
 
}

