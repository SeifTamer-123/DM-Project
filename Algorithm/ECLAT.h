//
// Created by ziad shady hamdy on 11/23/2026.
//

#ifndef DATAMINING_ECLAT_H
#define DATAMINING_ECLAT_H
#include "DataSet.h"

class ECLAT {
    using ItemSet = std::vector<std::string>;
    using Level = std::map<ItemSet, std::set<int>>;

    DataSet &data;
    Level frequent_item_set;

    void prune(Level &level) const;
    static Level join(Level &level);
    [[nodiscard]] Level level_one() const;
public:
    explicit ECLAT(DataSet &data);
    void run();
    Level &get_frequent_item_set();
};


#endif //DATAMINING_ECLAT_H
