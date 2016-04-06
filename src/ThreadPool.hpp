/*
 * ThreadPool.hpp
 *
 *  Created on: 06 апр. 2016 г.
 *      Author: Dmitriy Khaustov aka Dиmon (khaustov.dm@gmail.com)
 */

#ifndef THREADPOOL_HPP_
#define THREADPOOL_HPP_

#include <pthread.h>
#include <queue>
#include <set>

#include "IAction.hpp"

class ThreadPool
{
private:
	static const unsigned int _highChainLengthLimit = 3;

	std::set<pthread_t> _workers;

	bool _stopped;

	std::queue<IAction *> _lowQueue;
	std::queue<IAction *> _normalQueue;
	std::queue<IAction *> _highQueue;

	pthread_mutex_t _mutex;
	pthread_cond_t _condition;

	unsigned int _highChainLength;

	static void *Worker(void *arg);

public:
	explicit ThreadPool(unsigned int workerNumber);
	virtual ~ThreadPool();

	void Enqueue(IAction *action, IAction::Prio prio);
	void Stop();
};

#endif /* THREADPOOL_HPP_ */
