/**
 * memory.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "memory.hpp"
#include "event.hpp"

#include <iostream>
#include <iomanip>

/**
 * Realiza a alocação do job referente ao 'id' e que possui tamanho 'size'.
 * Se a memória não possuir espaço livre o suficiente será lançada uma exceção para o SO.
 */
void Memory::allocate(int jobID, int size) {
	if (size > this->totalSpace - this->usedSpace)
		throw Error::MEMORY_FULL;

	this->usedSpace += size;
	this->mem.insert({ jobID, size });
}


/**
 * Remove o job 'id' da memória e libera o espaço utilizado.
 */
void Memory::free(int jobID) {
	this->usedSpace -= this->mem.at(jobID);
	this->mem.erase(jobID);
}


/**
 * Exibe o estado atual da memória.
 */
void Memory::log() {
	std::cout << "=== Memoria Principal ===" << std::endl;
	std::cout << std::setw(4) << this->usedSpace << "/" << this->totalSpace
		<< " MB em uso\n" << std::endl;
	std::cout << "  ID | Memoria em uso" << std::endl;

	for (const auto& process : this->mem)
		std::cout << std::setw(4) << process.first << std::setw(14) << process.second
		<< " MB" << std::endl;
}


/**
 * Retorna um unordered_map com as informações referentes à memória.
 */
std::unordered_map<int, int> Memory::getInfo() const {
	return this->mem;
}
