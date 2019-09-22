
//#define _DEBUG

#include <random>
#include <memory>
#include <algorithm>
#include <chrono>
#include "Analysis.h"

void Analysis::directPassage() {
    int64_t value = 0;

#ifdef _DEBUG
    std::cout << "investigation:\n";
    std::cout << "  travel_order: \"forward\"\n ";
    std::cout << "  experiments:\n";
#endif
    for(unsigned k = 0; k < arrayOfBuffers.size();k++) {

        Buffer *buf = &arrayOfBuffers[k];
        auto start = std::chrono::high_resolution_clock::now();
        for (unsigned i = 0; i < 1000; i++) {
            for (unsigned j = 0; j < buf->amountOfElements; j++) {
                value = buf->buf_data[j];
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        results.ResultsOfDirectPassage.emplace(buf, end - start);
        buf->buf_data[0] = value;
#ifdef _DEBUG
        std::cout << "  - experiment:\n";
        std::cout << "      number: " << k+1 << std::endl;
        std::cout << "      input_data:\n";
        std::cout << "        buffer_size: \"" << buf->size << "mb\"\n";
        std::cout << "      results:\n";
        std::cout << "        duration: \"" << (end-start).count() << "ns\"\n";
#endif
    }

#ifdef _DEBUG
    std::cout << std::endl;
#endif

}

void Analysis::reversePassage() {
        int64_t value = 0;

#ifdef _DEBUG
    std::cout << "investigation:\n";
    std::cout << "  travel_order: \"backward\"\n ";
    std::cout << "  experiments:\n";
#endif

        for(unsigned k = 0; k < arrayOfBuffers.size();k++) {
            Buffer *buf = &arrayOfBuffers[k];
//            std::cout << "amount_reverse_Experiment = " << amountOfElements_ << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 1000; i++) {
                for (unsigned j = buf->amountOfElements; j > 0; j--) {
                    value = buf->buf_data[j];
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            results.ResultsOfReversePassage.emplace(buf, end - start);
            buf->buf_data[0] = value;
#ifdef _DEBUG
            std::cout << "  - experiment:\n";
            std::cout << "      number: " << k+1 << std::endl;
            std::cout << "      input_data:\n";
            std::cout << "        buffer_size: \"" << buf->size << "mb\"\n";
            std::cout << "      results:\n";
            std::cout << "        duration: \"" << (end-start).count() << "ns\"\n";
#endif

//            buffer[0] = value;
        }

#ifdef _DEBUG
    std::cout << std::endl;
#endif

}


void Analysis::randomPassage() {
    int64_t value = 0;
#ifdef _DEBUG
    std::cout << "investigation:\n";
    std::cout << "  travel_order: \"random\"\n ";
    std::cout << "  experiments:\n";
#endif
    for(unsigned k = 0; k < arrayOfBuffers.size();k++) {
        Buffer *buf = &arrayOfBuffers[k];
        std::vector<size_t> indexes(buf->amountOfElements);
        std::iota(indexes.begin(), indexes.end(), 0);
        std::shuffle(indexes.begin(), indexes.end(), std::mt19937(std::random_device()()));
//        std::cout << "amount_random_Experiment = " << amountOfElements_ << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 1000; i++) {
            for (size_t index : indexes) {
                value = buf->buf_data[index];
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        results.ResultsOfRandomPassage.emplace(buf, end - start);
        buf->buf_data[0] = value;

//        buffer[0] = value;

#ifdef _DEBUG
        std::cout << "  - experiment:\n";
        std::cout << "      number: " << k+1 << std::endl;
        std::cout << "      input_data:\n";
        std::cout << "        buffer_size: \"" << buf->size << "mb\"\n";
        std::cout << "      results:\n";
        std::cout << "        duration: \"" << (end-start).count() << "ns\"\n";
#endif
    }

#ifdef _DEBUG
    std::cout << std::endl;
#endif

}



void Analysis::InvestigetionOutputInFile() {
    std::ofstream fout;
    fout.open("results.txt");
    if(fout.is_open()){
        int i = 1;
        fout << "investigation:\n";
        fout << "  travel_order: \"forward\"\n ";
        fout << "  experiments:\n";
        for(auto index : results.ResultsOfDirectPassage){
            fout << "  - experiment:\n";
            fout << "      number: " << i << std::endl;
            fout << "      input_data:\n";
            fout << "        buffer_size: \"" << index.first->size << "mb\"\n";
            fout << "      results:\n";
            fout << "        duration: \"" << index.second.count() << "ns\"\n";
            i++;
        }

        fout << std::endl;
        i = 1;
        fout << "investigation:\n";
        fout << "  travel_order: \"backward\"\n ";
        fout << "  experiments:\n";
        for(auto index : results.ResultsOfDirectPassage){
            fout << "  - experiment:\n";
            fout << "      number: " << i << std::endl;
            fout << "      input_data:\n";
            fout << "        buffer_size: \"" << index.first->size << "mb\"\n";
            fout << "      results:\n";
            fout << "        duration: \"" << index.second.count() << "ns\"\n";
            i++;
        }

        fout << std::endl;
        i = 1;
        fout << "investigation:\n";
        fout << "  travel_order: \"random\"\n ";
        fout << "  experiments:\n";
        for(auto index : results.ResultsOfDirectPassage){
            fout << "  - experiment:\n";
            fout << "      number: " << i << std::endl;
            fout << "      input_data:\n";
            fout << "        buffer_size: \"" << index.first->size << "mb\"\n";
            fout << "      results:\n";
            fout << "        duration: \"" << index.second.count() << "ns\"\n";
            i++;
        }
        fout.close();
    } else{
        std::cout << "Error : File not open!\n";
        return;
    }
    std::cout << "\nThe same results of program have been written to the file 'results.txt' in one of cmake-build directories \n\n";

}

void Analysis::start() {
    try {

        double start_bufer_size = 0.5 * min_cache_size;  // 0.03125 Мб = 32 Кб = 262144 бит кол-во эл = 252144 / 8
        int64_t amountOfElement = (start_bufer_size * 1024) / sizeof(int64_t);
        int64_t start_degree = std::log2(start_bufer_size);
        if (start_degree < 0)
            start_degree = 0;
        int64_t degree = start_degree;
        double bufer_size = start_bufer_size; // Мб
        double max_bufer_size = 1.5 * max_cache_size; // Мб
        do {
            Buffer buf;
            std::unique_ptr<uint64_t[]> buffer = std::make_unique<uint64_t[]>(amountOfElement);
            for (unsigned i = 0; i < amountOfElement; ++i) {
                buffer[i] = rand();
            }
            buf.size = bufer_size;
            buf.buf_data = std::move(buffer);
            arrayOfBuffers.push_back(std::move(buf));
            degree++;
            bufer_size = pow(2, degree); // Мб
            amountOfElement = bufer_size * 1024 / sizeof(int64_t);

        } while (bufer_size < max_bufer_size);

        directPassage();
        reversePassage();
        randomPassage();
    }
    catch (AnalysisExceptions &exception) {
        std::cerr << "Founded error : " << exception.what() << std::endl;
    }
}

Analysis::~Analysis() {
    for(auto item : results.ResultsOfDirectPassage){
     item.first->buf_data.reset(nullptr);
    }
    results.ResultsOfDirectPassage.clear();

    for(auto item : results.ResultsOfReversePassage){
        item.first->buf_data.reset(nullptr);
    }
    results.ResultsOfReversePassage.clear();

    for(auto item : results.ResultsOfRandomPassage){
        item.first->buf_data.reset(nullptr);
    }
    results.ResultsOfRandomPassage.clear();

}

void Analysis::InvestigetionOutputInConsole() {
    int i = 1;
    std::cout << "Output in CONSOLE: \n";
    std::cout << "\ninvestigation:\n";
    std::cout << "  travel_order: \"forward\"\n ";
    std::cout << "  experiments:\n";
    for (auto index : results.ResultsOfDirectPassage) {
        std::cout << "  - experiment:\n";
        std::cout << "      number: " << i << std::endl;
        std::cout << "      input_data:\n";
        std::cout << "        buffer_size: \"" << index.first->size << "mb\"\n";
        std::cout << "      results:\n";
        std::cout << "        duration: \"" << index.second.count() << "ns\"\n";
        i++;
    }

    std::cout << std::endl;
    i = 1;
    std::cout << "investigation:\n";
    std::cout << "  travel_order: \"backward\"\n ";
    std::cout << "  experiments:\n";
    for (auto index : results.ResultsOfDirectPassage) {
        std::cout << "  - experiment:\n";
        std::cout << "      number: " << i << std::endl;
        std::cout << "      input_data:\n";
        std::cout << "        buffer_size: \"" << index.first->size << "mb\"\n";
        std::cout << "      results:\n";
        std::cout << "        duration: \"" << index.second.count() << "ns\"\n";
        i++;
    }

    std::cout << std::endl;
    i = 1;
    std::cout << "investigation:\n";
    std::cout << "  travel_order: \"random\"\n ";
    std::cout << "  experiments:\n";
    for (auto index : results.ResultsOfDirectPassage) {
        std::cout << "  - experiment:\n";
        std::cout << "      number: " << i << std::endl;
        std::cout << "      input_data:\n";
        std::cout << "        buffer_size: \"" << index.first->size << "mb\"\n";
        std::cout << "      results:\n";
        std::cout << "        duration: \"" << index.second.count() << "ns\"\n";
        i++;
    }
}
