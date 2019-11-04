/**
 * job.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "job.hpp"

std::tuple<Job::Operation, double> Job::getNextOperation() {
	return std::tuple<Operation, double>(Job::Operation::FINISH, 0.0);
}
