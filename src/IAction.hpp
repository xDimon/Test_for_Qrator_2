/*
 * IAction.hpp
 *
 *  Created on: 06 апр. 2016 г.
 *      Author: Dmitriy Khaustov aka Dиmon (khaustov.dm@gmail.com)
 */

#ifndef IACTION_HPP_
#define IACTION_HPP_

class IAction
{
public:
	enum Prio {
		LOW,
		NORMAL,
		HIGH
	};
	virtual ~IAction(){};

	virtual void Do(void) = 0;
};

#endif /* IACTION_HPP_ */
