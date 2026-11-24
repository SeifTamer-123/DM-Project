//
// Created by ziad shady hamdy on 11/22/2026.
//

#ifndef DATAMINING_DATASET_H
#define DATAMINING_DATASET_H
#include <fstream>
#include <bits/stdc++.h>
#include <iosfwd>
#include <map>
using namespace std;
class DataSet {
    // read only.
    ifstream file;
    double min_support{};
    double min_conf{};
    map<int, set<string>> horizontal;
    map<string, set<int>> vertical;
    map<string, set<int>> to_vertical_format() const;
    map<int, set<string>> preprocess();

public:
    explicit DataSet(ifstream &file, double min_support = 0.6, double min_conf = 0.7);
    void set_min_support(double min_supp);
    void set_min_conf(double min_con);
    double get_min_support() const;
    double get_min_conf() const;
    map<string, set<int>> &get_vertical_items();
    map<int, set<string>> &get_horizontal_items();
    ~DataSet();
};


#endif //DATAMINING_DATASET_H
