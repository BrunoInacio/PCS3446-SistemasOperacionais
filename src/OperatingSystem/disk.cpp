/**
 * disk.cpp
 * PCS 3446 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "disk.hpp"

#include <iostream>
#include <iomanip>


Disk::Disk(double totalSize, double readSpeed, double writeSpeed, double responseTime)
    : totalSize(totalSize),
    readSpeed(readSpeed),
    writeSpeed(writeSpeed),
    responseTime(responseTime),
    isRunning(false),
    currentOperation(Disk::IO::NONE),
    fileSize(0.0),
    totalRead(0.0),
    totalWrite(0.0) {}

/**
 * Inicia o processamento de uma operação 'operation' de um arquivo
 * de tamanho 'size'. Enquanto a operação estiver em andamento, o disco 
 * é considerado ocupado e não pode fazer outra operação.
 */
Disk::Result Disk::processIO(Disk::IO operation, double fileSize) {
    if (this->isRunning)
        return Disk::Result::ERROR_DISK_UNAVAILABLE;

    switch (operation) {
    case Disk::IO::READ:
        this->totalRead += fileSize;
        break;

    case Disk::IO::WRITE:
        this->totalWrite += fileSize;
        break;

    default:
        return Disk::Result::ERROR_INVALID_OPERATION;
    }

    this->currentOperation = operation;
    this->fileSize = fileSize;
    this->isRunning = true;
    return Disk::Result::SUCCESS;
}

/**
 * Finaliza a operação de IO, liberando o uso do disco.
 */
Disk::Result Disk::completeIO() {
    if (!this->isRunning)
        return Disk::Result::ERROR_NO_CURRENT_OPERATION;

    this->isRunning = false;
    this->currentOperation = Disk::IO::NONE;
    this->fileSize = 0.0;
    return Disk::Result::SUCCESS;
}

/**
 * Calcula o tempo de uma operação de IO em um arquivo de tamanho 'size'.
 */
int Disk::getIODuration() const {
    auto speed = this->currentOperation == IO::READ ? this->readSpeed : this->writeSpeed;
    return static_cast<int>(this->responseTime + 1000. * this->fileSize / speed);
}

/**
 * Exibe informações referentes ao disco.
 */
void Disk::info() {
    std::cout << "=== Disco ===" << std::endl;
    std::cout << "Tamanho total: " << this->totalSize << " MB" << std::endl;
    std::cout << "Velocidade de leitura: " << std::setprecision(2) << this->readSpeed << " MB/s" << std::endl;
    std::cout << "Velocidade de escrita: " << std::setprecision(2) << this->writeSpeed << " MB/s" << std::endl;
    std::cout << "Total de leituras feitas: " << std::setprecision(2) << this->totalRead << " MB" << std::endl;
    std::cout << "Total de escritas feitas: " << std::setprecision(2) << this->totalWrite << " MB" << std::endl;
    std::cout << std::endl;
}
