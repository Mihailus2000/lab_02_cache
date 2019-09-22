#ifndef ANALYSECACHE_ANALYSIS_H
#define ANALYSECACHE_ANALYSIS_H

#include <iostream>
#include <cmath>
#include "Experiment.h"
#include "AnasysisExceptions.h"

class Analysis {
public:
    Analysis() = default;

    virtual ~Analysis() {
        for (auto index : listOfResults) {
            delete index;
        }
        listOfResults.clear();
    }

    void start();

private:
    const double_t max_cache_size = 3*1024; // 3 Мб = 3072 Кб = 25165824 бит
    const double_t min_cache_size = 64; // 64 Кб = 524288 бит
    std::vector<Experiment *> listOfResults;
};


#endif //ANALYSECACHE_ANALYSIS_H
