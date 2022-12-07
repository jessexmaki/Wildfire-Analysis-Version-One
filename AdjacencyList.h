#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;

class AdjacencyList {
    struct county {
        string FIPS_CODE = "";
        string latitude, longitude = "";
        string countyName = "";
        vector<pair<county, float>> edges;
        county() {}
        county(string latitude, string longitude, string countyName) :
            latitude(latitude), longitude(longitude), countyName(countyName) {}
    };

    map<string, county> counties;

public:
    float findDistance(county &src, county &dest);
    void findTotalDistance(vector<string> &path);
    void insertCounty(string latitude, string longitude, string countyName);
    void insertEdges();
    void bfs(string src, string dest);
    void dfs(string src, string dest, vector<string> &path);
    
};

