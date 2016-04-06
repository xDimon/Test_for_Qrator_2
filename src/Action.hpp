/*
 * Action.hpp
 *
 *  Created on: 06 апр. 2016 г.
 *      Author: Dmitriy Khaustov aka Dиmon (khaustov.dm@gmail.com)
 */

#ifndef ACTION_HPP_
#define ACTION_HPP_

#include "IAction.hpp"

class Action: public IAction
{
private:
	char _letter;

public:
	explicit Action(char letter);
	virtual ~Action();

	virtual void Do();
};

#endif /* ACTION_HPP_ */
