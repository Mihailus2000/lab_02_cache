
#define _DEBUG

#include "Analysis.h"

    void Analysis::start() {
        try {
            double start_bufer_size = 0.5 * min_cache_size;  // 0.03125 Мб = 32 Кб = 262144 бит кол-во эл = 252144 / 8

            int64_t amountOfElement = (start_bufer_size * 1024) / sizeof(int64_t);
            int64_t  start_degree = std::log2(start_bufer_size);
            if(start_degree < 0)
                start_degree = 0;
            int64_t degree = start_degree;
            double bufer_size = start_bufer_size; // Мб
            double max_bufer_size = 1.5 * max_cache_size; // Мб
            do {
#ifdef _DEBUG
                //                std::cout << "log2(32) = " << log2(32) << std::endl;
                std::cout << "amount = " << amountOfElement << std::endl;
                std::cout << "buf_Kbi = " << bufer_size << std::endl;
                std::cout << "degree = " << degree << std::endl;
                std::cout << "MAXbuf_Kbi = " << max_bufer_size << std::endl;
#endif
                auto *experiment = new Experiment(amountOfElement);
                experiment->startExperiment();
                listOfResults.push_back(experiment);
                degree++;
                bufer_size = pow(2, degree); // Мб
                amountOfElement = bufer_size * 1024 / sizeof(int64_t);
            } while (bufer_size < max_bufer_size);
        }
        catch (AnalysisExceptions &exception) {
            std::cerr << "Founded error : " << exception.what() << std::endl;
        }
    }