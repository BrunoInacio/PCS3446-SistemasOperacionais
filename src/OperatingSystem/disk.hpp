/**
 * disk.hpp
 * PCS 3446 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include <tuple>

/**
 * 'size': Tamanho do disco em MB.
 * 'readSpeed': Velocidade de leitura em MB/s.
 * 'writeSpeed': Velocidade de escrita em MB/s.
 * 'responseTime': Tempo de resposta em ms.
 */
class Disk {
public:
    Disk(double totalSize, double readSpeed, double writeSpeed, double responseTime);
    ~Disk() {};

    enum class IO;
    enum class Result;

    Result processIO(Disk::IO operation, double size);
    Result completeIO();

    int getIODuration() const;
    const double totalSize;
    void info();

private:
    bool isRunning;
    IO currentOperation;
    double fileSize;

    const double responseTime;
    const double readSpeed;
    const double writeSpeed;

    double totalRead;
    double totalWrite;
};

enum class Disk::IO {
    NONE,
    READ,
    WRITE
};

enum class Disk::Result {
    SUCCESS,
    ERROR_DISK_UNAVAILABLE,
    ERROR_NO_CURRENT_OPERATION,
    ERROR_INVALID_OPERATION,
};
