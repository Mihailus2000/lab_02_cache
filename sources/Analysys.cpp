
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
                value = buf->bufData[j];
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        results.ResultsOfDirectPassage.emplace(buf, std::chrono::duration_cast<std::chrono::milliseconds>(end - start));
        buf->bufData[0] = value;
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
//            int ind = 0, inf = 0;
            for (int i = 0; i < 1000; i++) {
//                ind++;
                for (unsigned j = buf->amountOfElements; j > 0; j--) {
//                    inf++;
                    value = buf->bufData[j];
                }
//                std::cout << "amount : " << buf->amountOfElements << "\n\n";
//                std::cout << inf << std::endl;
            }
//            std::cout << ind << std::endl << "---------\n";

            auto end = std::chrono::high_resolution_clock::now();
            results.ResultsOfReversePassage.emplace(buf, std::chrono::duration_cast<std::chrono::milliseconds>(end - start));
            buf->bufData[0] = value;
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
                value = buf->bufData[index];
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        results.ResultsOfRandomPassage.emplace(buf, std::chrono::duration_cast<std::chrono::milliseconds>(end - start));
        buf->bufData[0] = value;

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
            fout <<     "      input_data:\n";
            fout << "        buffer_size: \"" << index.first->size << "kb\"\n";
            fout << "      results:\n";
            fout << "        duration: \"" << index.second.count() << "ms\"\n";
            i++;
        }

        fout << std::endl;
        i = 1;
        fout << "investigation:\n";
        fout << "  travel_order: \"backward\"\n ";
        fout << "  experiments:\n";
        for(auto index : results.ResultsOfReversePassage){
            fout << "  - experiment:\n";
            fout << "      number: " << i << std::endl;
            fout << "      input_data:\n";
            fout << "        buffer_size: \"" << index.first->size << "kb\"\n";
            fout << "      results:\n";
            fout << "        duration: \"" << index.second.count() << "ms\"\n";
            i++;
        }

        fout << std::endl;
        i = 1;
        fout << "investigation:\n";
        fout << "  travel_order: \"random\"\n ";
        fout << "  experiments:\n";
        for(auto index : results.ResultsOfRandomPassage){
            fout << "  - experiment:\n";
            fout << "      number: " << i << std::endl;
            fout << "      input_data:\n";
            fout << "        buffer_size: \"" << index.first->size << "kb\"\n";
            fout << "      results:\n";
            fout << "        duration: \"" << index.second.count() << "ms\"\n";
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
        int64_t amountOfElement = (MIN_CACHE_SIZE / 2.0 * 1024) / sizeof(int64_t);
        double buferSize = MIN_CACHE_SIZE / 2;
        int64_t degree = std::log2(buferSize);
        do {
            Buffer buf;
            std::unique_ptr<uint64_t[]> buffer = std::make_unique<uint64_t[]>(amountOfElement);

            /*Прогрев буфера*/
            for (unsigned i = 0; i < amountOfElement; ++i) {
                buffer[i] = rand();
            }
            /*--------------*/

            buf.size = buferSize;
            buf.amountOfElements = amountOfElement;
            buf.bufData = std::move(buffer);
            arrayOfBuffers.push_back(std::move(buf));
            degree++;
            buferSize = pow(2, degree); // Мб
            amountOfElement = buferSize * 1024 / sizeof(int64_t);
        } while (buferSize < MAX_CACHE_SIZE * 1.5);

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
     item.first->bufData.reset(nullptr);
    }
    results.ResultsOfDirectPassage.clear();

    for(auto item : results.ResultsOfReversePassage){
        item.first->bufData.reset(nullptr);
    }
    results.ResultsOfReversePassage.clear();

    for(auto item : results.ResultsOfRandomPassage){
        item.first->bufData.reset(nullptr);
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
        std::cout << "        buffer_size: \"" << index.first->size << "kb\"\n";
        std::cout << "      results:\n";
        std::cout << "        duration: \"" << index.second.count() << "ms\"\n";
        i++;
    }

    std::cout << std::endl;
    i = 1;
    std::cout << "investigation:\n";
    std::cout << "  travel_order: \"backward\"\n ";
    std::cout << "  experiments:\n";
    for (auto index : results.ResultsOfReversePassage) {
        std::cout << "  - experiment:\n";
        std::cout << "      number: " << i << std::endl;
        std::cout << "      input_data:\n";
        std::cout << "        buffer_size: \"" << index.first->size << "kb\"\n";
        std::cout << "      results:\n";
        std::cout << "        duration: \"" << index.second.count() << "ms\"\n";
        i++;
    }

    std::cout << std::endl;
    i = 1;
    std::cout << "investigation:\n";
    std::cout << "  travel_order: \"random\"\n ";
    std::cout << "  experiments:\n";
    for (auto index : results.ResultsOfRandomPassage) {
        std::cout << "  - experiment:\n";
        std::cout << "      number: " << i << std::endl;
        std::cout << "      input_data:\n";
        std::cout << "        buffer_size: \"" << index.first->size << "kb\"\n";
        std::cout << "      results:\n";
        std::cout << "        duration: \"" << index.second.count() << "ms\"\n";
        i++;
    }
}
