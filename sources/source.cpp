// Copyright 2018 Your Name <your_email>

#include <header.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>

struct ExperimentsResults{
    std::chrono::nanoseconds  directDuration, reverseDuration, randomDuration;
};

class AnalysisExceptions : public std::exception{
public:
    AnalysisExceptions(std::string const &message) : message_(message){}
    virtual ~AnalysisExceptions() = default;
    virtual char const *what() const noexcept{
        return message_.c_str();
    }

private:
    std::string message_;
};

class Experiment{
public:
    Experiment(){}
    virtual ~Experiment(){}

    Experiment(int amountOfElements) : amountOfElements_(amountOfElements){
        Array_.resize(amountOfElements_);
        for(auto index : Array_){    // Заполнение массива
            *index = rand();
        }
    }

    void startExperiment(){
        directPassage();
        reversePassage();
        randomPassage();
    }

protected:
    std::vector<int*> Array_;
    ExperimentsResults results_;
private:
    int amountOfElements_ = -1;

    void directPassage(){
        auto start = std::chrono::high_resolution_clock::now();
        for(unsigned i = 0; i < 1000; i++){
            for (unsigned j = 0; j < Array_.size(); j++){
                Array_.at(j);
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        results_.directDuration = end - start;
    }
    void reversePassage(){
        auto start = std::chrono::high_resolution_clock::now();
        for(unsigned i = 0; i < 1000; i++){
            for (int j = Array_.size(); j >= 0; j--){
                Array_.at(j);
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        results_.reverseDuration = end - start;
    }
    void randomPassage(){
        std::shuffle(Array_.begin(), Array_.end(), std::mt19937(std::random_device()()));
        auto start = std::chrono::high_resolution_clock::now();
        for(unsigned i = 0; i < 1000; i++){
            for (unsigned j = 0; j < Array_.size(); j++){
                Array_.at(j);
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        results_.randomDuration = end-start;
    }
};


class Analysis{
public:
    Analysis() = default;
    virtual ~Analysis(){
        for(auto index : listOfResults){
            delete index;
        }
        listOfResults.clear();
    }

    void start(){
        try {
            double start_bufer_size = 0.5 * min_cache_size;
            double start_degree = std::log2(start_bufer_size);
            double degree = start_degree;
            double bufer_size = start_bufer_size;
            double max_bufer_size = 1.5 * max_cache_size;
            while (bufer_size < max_bufer_size) {
                auto *experiment = new Experiment(int(bufer_size / sizeof(int)));
                experiment->startExperiment();
                listOfResults.push_back(experiment);
                degree++;
                bufer_size = pow(2, degree);
            }
        }
        catch (AnalysisExceptions &exception){
            std::cerr << "Founded error : " << exception.what() << std::endl;
        }
    }

private:


    const int max_cache_size = 3072; // 3072 Кб
    const int min_cache_size = 64; // 64 Кб

    std::vector<Experiment*> listOfResults;
};


int main(){
    Analysis project;
    project.start();
    return 0;
}