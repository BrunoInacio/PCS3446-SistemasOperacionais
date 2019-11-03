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
void Memory::allocate(int id, int size) {
	if (size > this->totalSpace - this->usedSpace)
		throw Event::MEMORY_FULL;

	this->usedSpace += size;
	this->mem.insert({ id, size });
}


/**
 * Remove o job 'id' da memória e libera o espaço utilizado.
 */
void Memory::free(int id) {
	this->usedSpace -= this->mem.at(id);
	this->mem.erase(id);
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
