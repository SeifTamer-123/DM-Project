//
// Created by ziad shady hamdy on 11/23/2026.
//

#include "ECLAT.h"

ECLAT::ECLAT(DataSet &data) : data(data) {}

void ECLAT::run() {
    Level current = level_one();
    prune(current);
    frequent_item_set.clear();
    while (!current.empty()) {
        frequent_item_set.insert(current.begin(), current.end());
        current = join(current);
        prune(current);
    }
}

void ECLAT::prune(Level &level) const {
    // get the support count.
    const double min_supp = data.get_min_support() * static_cast<double>(data.get_horizontal_items().size());
    for (auto it = level.begin(); it != level.end(); ) {
        if (static_cast<double>(it->second.size()) < min_supp) it = level.erase(it);
        else ++it;
    }
}

ECLAT::Level ECLAT::join(Level &level) {
    Level result;
    for (auto i = level.begin(); i != level.end(); ++i) {
        for (auto j = next(i); j != level.end(); ++j) {
            const ItemSet &a = i->first;
            const ItemSet &b = j->first;
            const int k = static_cast<int>(a.size());

            // first (k - 1) not equal
            if (!equal(a.begin(), a.begin() + (k - 1), b.begin()))
                break;

            // join
            ItemSet merged = a;
            merged.push_back(b.back());

            // intersect between the ids
            set<int> ids;
            ranges::set_intersection(i->second, j->second,
                                     inserter(ids, ids.end()));

            if (!ids.empty())
                result[merged] = std::move(ids);
        }
    }
    return result;
}

ECLAT::Level ECLAT::level_one() const {
    Level result;
    for (auto &[item, ids] : data.get_vertical_items()) {
        ItemSet itm;
        itm.push_back(item);
        result[itm].insert(ids.begin(), ids.end());
    }
    return result;
}

ECLAT::Level &ECLAT::get_frequent_item_set(){
    return frequent_item_set;
}
