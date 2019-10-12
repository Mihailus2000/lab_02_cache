#ifndef ANALYSECACHE_ANALYSIS_H
#define ANALYSECACHE_ANALYSIS_H

#include <iostream>
#include <cmath>
#include "AnasysisExceptions.h"
#include <fstream>
#include <map>
#include <bits/unique_ptr.h>
#include <chrono>
#include <vector>

struct Buffer{
    std::unique_ptr<uint64_t[]> bufData;
    unsigned amountOfElements = 0;
    double size = 0;
};

class Analysis {
public:
    Analysis() = default;
    virtual ~Analysis();
    void start();
    void InvestigetionOutputInFile();
    void InvestigetionOutputInConsole();

private:
    struct AnalysysResults {
        std::map<Buffer*, std::chrono::milliseconds> ResultsOfDirectPassage;
        std::map<Buffer*, std::chrono::milliseconds> ResultsOfReversePassage;
        std::map<Buffer*, std::chrono::milliseconds> ResultsOfRandomPassage;

    };

    void reversePassage();
    void directPassage();
    void randomPassage();

    AnalysysResults results;
    std::vector<Buffer> arrayOfBuffers ;
    const double_t MAX_CACHE_SIZE = 3*1024; // 3 Мб = 3072 Кб = 25165824 бит
    const double_t MIN_CACHE_SIZE = 64; // 64 Кб
};


#endif //ANALYSECACHE_ANALYSIS_H
