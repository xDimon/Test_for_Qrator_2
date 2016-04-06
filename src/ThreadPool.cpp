/*
 * ThreadPool.cpp
 *
 *  Created on: 06 апр. 2016 г.
 *      Author: Dmitriy Khaustov aka Dиmon (khaustov.dm@gmail.com)
 */

#include "ThreadPool.hpp"

#include <stddef.h>
#include <map>

ThreadPool::ThreadPool(unsigned int workerNum)
: _stopped(false), _highChainLength(0)
{
	pthread_mutex_init(&_mutex, NULL);
	pthread_cond_init(&_condition, NULL);

	for (unsigned int i = 0; i < workerNum; i++)
	{
		pthread_t tid;
		if (0 == pthread_create(&tid, NULL, &ThreadPool::Worker, this))
		{
			_workers.insert(tid);
		}
	}
}

ThreadPool::~ThreadPool()
{
	Stop();

	pthread_mutex_destroy(&_mutex);
	pthread_cond_destroy(&_condition);
}

void ThreadPool::Stop()
{
	pthread_mutex_lock(&_mutex);

	if (_stopped)
	{
		pthread_mutex_unlock(&_mutex);
		return;
	}
	_stopped = true;

	pthread_cond_broadcast(&_condition);

	pthread_mutex_unlock(&_mutex);

	for (std::set<pthread_t>::iterator i = _workers.begin(); i != _workers.end(); ++i)
	{
		pthread_join(*i, NULL);
	}
}

bool ThreadPool::Enqueue(IAction *action, IAction::Prio prio)
{
	std::queue<IAction *> *queue;

	pthread_mutex_lock(&_mutex);

	if (_stopped)
	{
		pthread_mutex_unlock(&_mutex);
		return false;
	}

	switch (prio)
	{
		case IAction::LOW:
			queue = &_lowQueue;
			break;

		case IAction::NORMAL:
			queue = &_normalQueue;
			break;

		case IAction::HIGH:
			queue = &_highQueue;
			break;
	}

	queue->push(action);

	pthread_cond_signal(&_condition);

	pthread_mutex_unlock(&_mutex);

	return true;
}

void *ThreadPool::Worker(void *arg)
{
	ThreadPool *tp = static_cast<ThreadPool *>(arg);

	for (;;)
	{
		pthread_mutex_lock(&tp->_mutex);

		IAction *action;

		again:
		if (tp->_stopped)
		{
			pthread_mutex_unlock(&tp->_mutex);
			return NULL;
		}
		else if (!tp->_highQueue.empty() && tp->_highChainLength < tp->_highChainLengthLimit)
		{
			action = tp->_highQueue.front();
			tp->_highQueue.pop();
			tp->_highChainLength++;
		}
		else if (!tp->_normalQueue.empty())
		{
			action = tp->_normalQueue.front();
			tp->_normalQueue.pop();
			tp->_highChainLength = 0;
		}
		else if (!tp->_lowQueue.empty())
		{
			action = tp->_lowQueue.front();
			tp->_lowQueue.pop();
			tp->_highChainLength = 0;
		}
		else
		{
			pthread_cond_wait(&tp->_condition, &tp->_mutex);
			goto again;
		}

		pthread_mutex_unlock(&tp->_mutex);

		action->Do();
	}
	return NULL;
}
