//
// Created by mihailus on 22.09.2019.
//

#define _DEBUG

#include <random>
#include "Experiment.h"


void Experiment::startExperiment() {
    directPassage();
    reversePassage();
    randomPassage();
#ifdef _DEBUG
    std::cout << "amount : " << amountOfElements_ << std::endl;
//  std::cout << "buffer size = " << amountOfElements_ * sizeof(int64_t) / (1024 * 1024 * 8) << " mb" << std::endl;
    std::cout << results_.directDuration.count() << " ms " << std::endl;
    std::cout << results_.reverseDuration.count() << " ms " << std::endl;
    std::cout << results_.randomDuration.count() << " ms " << std::endl;
    std::cout << "-----------------------------------------\n";
#endif
}

void Experiment::directPassage() {
    int64_t value = 0;
    std::cout << "amount_direct_Experiment = " << amountOfElements_ << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < 1000; i++) {
        for (unsigned j = 0; j < amountOfElements_; j++) {
            value = buffer[j];
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    results_.directDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    buffer[0] = value;
}

void Experiment::reversePassage() {
    {
        int64_t value = 0;
        std::cout << "amount_reverse_Experiment = " << amountOfElements_ << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 1000; i++) {
            for (unsigned j = amountOfElements_; j > 0; j--) {
                value = buffer[j];
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        results_.reverseDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        buffer[0] = value;
    }
}

void Experiment::randomPassage() {
    int64_t value = 0;
    std::vector<size_t> indexes(amountOfElements_);
    std::iota(indexes.begin(), indexes.end(), 0);
    std::shuffle(indexes.begin(), indexes.end(), std::mt19937(std::random_device()()));
    std::cout << "amount_random_Experiment = " << amountOfElements_ << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        for (size_t index : indexes) {
            value = buffer[index];
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    results_.randomDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    buffer[0] = value;
}

Experiment::Experiment(int amountOfElements) : amountOfElements_(amountOfElements) {
    std::cout << "amount_CONSTRUCTOR = " << amountOfElements_ << std::endl;

    buffer = std::make_unique<uint64_t[]>(amountOfElements_);
    for (unsigned i = 0; i < amountOfElements_; ++i) {
        buffer[i] = rand();
    }
}