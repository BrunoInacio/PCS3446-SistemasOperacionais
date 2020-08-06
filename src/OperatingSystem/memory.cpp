/**
 * memory.cpp
 * PCS 3446 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "memory.hpp"
#include "event.hpp"

#include <iostream>
#include <iomanip>


/**
 * Realiza a alocação do job referente ao 'id' e que possui tamanho 'size'.
 * Se a memória não possuir espaço livre o suficiente será retornado um erro.
 */
Memory::Result Memory::allocate(int jobID, int size) {
    if (size + this->usedSpace > this->totalSpace)
        return Memory::Result::ERROR_MEMORY_FULL;

    this->usedSpace += size;
    this->content.insert({ jobID, size });

    return Memory::Result::SUCCESS;
}

/**
 * Remove o job 'id' da memória e libera o espaço utilizado.
 */
Memory::Result Memory::free(int jobID) {
    this->usedSpace -= this->content.at(jobID);
    this->content.erase(jobID);

    return Memory::Result::SUCCESS;
}

/**
 * Exibe o estado atual da memória.
 */
void Memory::info() {
    std::cout << "=== Memoria Principal ===" << std::endl;
    std::cout << std::setw(4) 
        << this->usedSpace << "/" << this->totalSpace
        << " MB em uso\n" << std::endl;

    std::cout << "  ID | Memoria em uso" << std::endl;

    for (const auto& job : this->content)
        std::cout << std::setw(4)
        << job.first << std::setw(14) << job.second
        << " MB" << std::endl;

    std::cout << std::endl;
}
