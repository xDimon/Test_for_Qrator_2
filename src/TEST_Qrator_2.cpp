/*
 * TEST_Qrator_2.cpp
 *
 *  Created on: 06.04.2016
 *      Author: Dmitriy Khaustov (khaustov.dm@gmail.com)
 */

#include <unistd.h>

#include "Action.hpp"
#include "IAction.hpp"
#include "ThreadPool.hpp"

int main(int argc, const char *argv[])
{
	ThreadPool threadPool(3);

	Action A('A');
	Action B('B');
	Action C('C');
	Action D('D');
	Action E('E');
	Action F('F');
	Action G('G');
	Action H('H');
	Action I('I');
	Action J('J');
	Action K('K');
	Action L('L');
	Action M('M');
	Action N('N');

	threadPool.Enqueue(&A, IAction::LOW);
	threadPool.Enqueue(&B, IAction::LOW);
	threadPool.Enqueue(&C, IAction::LOW);
	threadPool.Enqueue(&D, IAction::LOW);
	threadPool.Enqueue(&E, IAction::NORMAL);
	threadPool.Enqueue(&F, IAction::NORMAL);
	threadPool.Enqueue(&G, IAction::NORMAL);
	threadPool.Enqueue(&H, IAction::NORMAL);
	threadPool.Enqueue(&I, IAction::HIGH);
	threadPool.Enqueue(&J, IAction::HIGH);
	threadPool.Enqueue(&K, IAction::HIGH);
	threadPool.Enqueue(&L, IAction::HIGH);
	threadPool.Enqueue(&M, IAction::HIGH);
	threadPool.Enqueue(&N, IAction::HIGH);

	sleep(30);

	threadPool.Stop();

	return 0;
}
