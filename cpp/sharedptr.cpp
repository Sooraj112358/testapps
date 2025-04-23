#include<iostream>


int32_t IvcAcrnRW::startInterface () {
    //IVC_LOG_DEBUG("IvcAcrnRW::startInterface called");


    if (writerCb != NULL) {
        killWriterThread = false;
        //std::thread writeThread(&IvcAcrnRW::writerThread, this, writerCb);
        //clientThreads.push_back(move(writeThread));
        std::shared_ptr<std::thread> writeThread = std::make_shared<std::thread>(&IvcAcrnRW::writerThread, this, writerCb);
        //clientThreads.push_back(std::make_shared<std::thread>(&IvcAcrnRW::writerThread, this, writerCb));
        clientThreads.push_back(writeThread);
    }

    //IVC_LOG_DEBUG("IvcAcrnRW::startInterface completed");
    return 0;
}

