/*
 * Action.cpp
 *
 *  Created on: 06 апр. 2016 г.
 *      Author: Dmitriy Khaustov aka Dиmon (khaustov.dm@gmail.com)
 */

#include "Action.hpp"

#include <iostream>

Action::Action(char letter)
{
	_letter = letter;
}

Action::~Action()
{
}

void Action::Do()
{
	std::cout << _letter << " ";
	std::cout.flush();

	unsigned int n = 0;

	// Emulation long processing
	while (++n < 1 << 24);
}
