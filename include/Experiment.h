//
// Created by mihailus on 22.09.2019.
//

#ifndef ANALYSECACHE_EXPERIMENT_H
#define ANALYSECACHE_EXPERIMENT_H

#include <iostream>
#include <memory>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>

struct ExperimentsResults {
    std::chrono::milliseconds directDuration, reverseDuration, randomDuration;
};

class Experiment {
public:
    Experiment() {}

    virtual ~Experiment() {}

    explicit Experiment(int amountOfElements);

    void startExperiment();

private:
    unsigned amountOfElements_ = 0;
    std::unique_ptr<uint64_t[]> buffer;
    ExperimentsResults results_;

    void directPassage();

    void reversePassage();

    void randomPassage();
};


#endif //ANALYSECACHE_EXPERIMENT_H
