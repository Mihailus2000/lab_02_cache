// Copyright 2018 Your Name <your_email>

#define _DEBUG

#include <header.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <memory>
//#include "gtest/gtest.h"



struct ExperimentsResults {
    std::chrono::milliseconds directDuration, reverseDuration, randomDuration;
};

class AnalysisExceptions : public std::exception {
public:
    AnalysisExceptions(std::string const &message) : message_(message) {}

    virtual ~AnalysisExceptions() = default;

    virtual char const *what() const noexcept {
        return message_.c_str();
    }

private:
    std::string message_;
};

class Experiment {
public:
    Experiment() {}

    virtual ~Experiment() {}

    Experiment(int amountOfElements) : amountOfElements_(amountOfElements) {
        buffer = std::make_unique<uint64_t[]>(amountOfElements_);
        for (unsigned i = 0; i < amountOfElements_; ++i) {
            buffer[i] = rand();
        }
//        for (unsigned i = 0; i < Array_.size(); ++i) {
//            Array_.
//        }
    }

    void startExperiment() {
        directPassage();
        reversePassage();
        randomPassage();
#ifdef _DEBUG
        std::cout << "amount : " << amountOfElements_ << std::endl;
        std::cout << "buffer size = " << amountOfElements_ * sizeof(int64_t) / (1024 * 1024 * 8) << " mb" << std::endl;
        std::cout << results_.directDuration.count() << " ms " << std::endl;

        std::cout << results_.reverseDuration.count() << " ms " << std::endl;

        std::cout << results_.randomDuration.count() << " ms " << std::endl;

        std::cout << "-----------------------------------------\n";
#endif
    }

private:
    unsigned amountOfElements_ = 0;
//    std::vector<int64_t>* Array_;
    std::unique_ptr<uint64_t[]> buffer;
    ExperimentsResults results_;

    void directPassage() {
        int64_t value;
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

    void reversePassage() {
        int64_t value;
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

    void randomPassage() {
        int64_t value;
        std::vector<size_t> indexes(amountOfElements_);
        std::iota(indexes.begin(), indexes.end(), 0);
        std::shuffle(indexes.begin(), indexes.end(), std::mt19937(std::random_device()()));

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
};


class Analysis {
public:
    Analysis() = default;

    virtual ~Analysis() {
        for (auto index : listOfResults) {
            delete index;
        }
        listOfResults.clear();
    }

    void start() {
        try {
            double start_bufer_size = 0.5 * min_cache_size;  // 0.03125 Мб = 32 Кб = 262144 бит кол-во эл = 252144 / 8
            int64_t amountOfElement = (start_bufer_size * 1024 * 1024 * 8) / sizeof(int64_t);
            int64_t  start_degree = std::log2(start_bufer_size);
            if(start_degree < 0)
                start_degree = 0;
            int64_t degree = start_degree;
            double bufer_size = start_bufer_size; // Мб
            double max_bufer_size = 1.5 * max_cache_size; // Мб
            while (bufer_size < max_bufer_size) {
#ifdef _DEBUG
//                std::cout << "log2(32) = " << log2(32) << std::endl;
                std::cout << "amount = " << amountOfElement << std::endl;
                std::cout << "buf_mebaB = " << bufer_size << std::endl;
                std::cout << "degree = " << degree << std::endl;
                std::cout << "MAXbuf_mebaB = " << max_bufer_size << std::endl;
#endif
                auto *experiment = new Experiment(amountOfElement);
                experiment->startExperiment();
                listOfResults.push_back(experiment);
                degree++;
                bufer_size = pow(2, degree); // Мб
                amountOfElement = bufer_size * 1024 * 1024 * 8 / sizeof(int64_t);
            }
        }
        catch (AnalysisExceptions &exception) {
            std::cerr << "Founded error : " << exception.what() << std::endl;
        }
    }

private:


    const double_t max_cache_size = 3; // 3 Мб = 3072 Кб = 25165824 бит
    const double_t min_cache_size = 0.0625; // 64 Кб = 524288 бит

    std::vector<Experiment *> listOfResults;
};


int main() {
    Analysis project;
    project.start();
    return 0;
}

#undef _DEBUG