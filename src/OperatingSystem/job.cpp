/**
 * job.cpp
 * PCS 3446 - Sistemas Operacionais - 2019
 * Bruno Brand�o In�cio
 */

#include "job.hpp"

#include <algorithm>


/**
 * Construtor que recebe 'totalTime', 'memoryUsed', 'totalIO' e 'priority'.
 */
Job::Job(int totalTime, int memoryUsed, Priority priority)
    : totalTime(totalTime),
      memoryUsed(memoryUsed),
      priority(priority),
      id(++lastId),
      processedTime(0),
      state(State::SUBMIT) {
    this->operations.push_back(std::make_tuple(totalTime, Job::Operation::FINISH, 0.0));
}


/**
 * Adiciona uma opera��o � lista de opera��es que devem ser realizadas pelo job.
 */
void Job::addOperation(std::tuple<int, Job::Operation, double> operation) {
    auto position = std::lower_bound(this->operations.begin(), this->operations.end(), operation);
    this->operations.insert(position, operation);
}


/**
 * Realiza o processamento de 'duration' de tempo.
 */
void Job::process(int duration) {
    this->processedTime += duration;
}


/**
 * Obt�m a pr�xima opera��o que deve ser realizada pelo 'job'.
 * Por exemplo, opera��es de IO ou finaliza��o do processamento.
 */
std::tuple<int, Job::Operation, double> Job::getNextOperation() {
    for (const auto [time, operation, value]: this->operations)
        if (this->processedTime < time)
            return std::make_tuple(time - this->processedTime, operation, value);

    return std::make_tuple(0, Job::Operation::FINISH, 0.0);
}
