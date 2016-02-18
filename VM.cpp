// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VM.cpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/23 13:35:59 by jmaurice          #+#    #+#             //
//   Updated: 2015/02/04 19:00:53 by jmaurice         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "VM.hpp"

VM::VM()
{}

VM::VM(VM const & src)
{
    *this = src;
}

VM::~VM()
{
	auto ite = this->_stack.cend();

	for (auto it = this->_stack.cbegin() ; it != ite ; ++it)
		delete *it;
}

VM & VM::operator=(VM const & other)
{
    this->_stack = other._stack;
    return *this;
}

void VM::checkSize(unsigned int size) const
{
	if (this->_stack.size() < size)
		throw VM::StackSizeException();
}

void VM::ipush(const IOperand* op)
{
	this->_stack.push_front(op);
}

void VM::ipop(void)
{
	this->checkSize(1);

	const IOperand* tmp = *(this->_stack.begin());

	this->_stack.pop_front();
	delete tmp;
}

void VM::idump(void) const
{
	auto ite = this->_stack.cend();

	for (auto it = this->_stack.cbegin() ; it != ite ; ++it)
	{
		const IOperand* tmp = *it;
		std::cout << tmp->toString() << std::endl;
	}
}

void VM::iassert(const IOperand* op) const
{
	this->checkSize(1);

	auto tmp = this->_stack.begin();

	if (op->getType() != (*tmp)->getType() || op->toString() != (*tmp)->toString())
		throw VM::PrintException();
}

void VM::iadd(void)
{
	this->checkSize(2);

	auto			a = this->_stack.begin();
	auto			b = this->_stack.begin();
	b++;

	Operand<double> *	c = static_cast<Operand<double> *>(const_cast<IOperand *>(*a));
	Operand<double> * 	d = static_cast<Operand<double> *>(const_cast<IOperand *>(*b));
	IOperand const * result = *d + *c;
	this->ipop();
	this->ipop();
	this->ipush(result);
}

void VM::isub(void)
{
	this->checkSize(2);

	auto			a = this->_stack.begin();
	auto			b = this->_stack.begin();
	b++;

	Operand<double> *	c = static_cast<Operand<double> *>(const_cast<IOperand *>(*a));
	Operand<double> * 	d = static_cast<Operand<double> *>(const_cast<IOperand *>(*b));
	IOperand const * result = *d - *c;
	this->ipop();
	this->ipop();
	this->ipush(result);
}

void VM::imul(void)
{
	this->checkSize(2);

	auto			a = this->_stack.begin();
	auto			b = this->_stack.begin();
	b++;

	Operand<double> *	c = static_cast<Operand<double> *>(const_cast<IOperand *>(*a));
	Operand<double> * 	d = static_cast<Operand<double> *>(const_cast<IOperand *>(*b));
	IOperand const * result = *d * *c;
	this->ipop();
	this->ipop();
	this->ipush(result);
}

void VM::idiv(void)
{
	this->checkSize(2);

	auto			a = this->_stack.begin();
	auto			b = this->_stack.begin();
	b++;

	Operand<double> *	c = static_cast<Operand<double> *>(const_cast<IOperand *>(*a));
	Operand<double> * 	d = static_cast<Operand<double> *>(const_cast<IOperand *>(*b));
	IOperand const * result = *d / *c;
	this->ipop();
	this->ipop();
	this->ipush(result);
}

void VM::imod(void)
{
	this->checkSize(2);

	auto			a = this->_stack.begin();
	auto			b = this->_stack.begin();
	b++;

	Operand<double> *	c = static_cast<Operand<double> *>(const_cast<IOperand *>(*a));
	Operand<double> * 	d = static_cast<Operand<double> *>(const_cast<IOperand *>(*b));
	IOperand const * result = *d % *c;
	this->ipop();
	this->ipop();
	this->ipush(result);
}

void VM::iprint(void) const
{
	this->checkSize(1);
	auto it = this->_stack.begin();
	if ((*it)->getType() == INT8)
	{
		const Operand<int8_t>* tmp = dynamic_cast<const Operand<int8_t>*>(*it);
		std::cout << tmp->getValue() << std::endl;
	}
	else
		throw VM::PrintException();
}

const char* VM::StackSizeException::what() const throw()
{
	return("VM : Stack has not enough elements for this operation");
}

const char* VM::AssertException::what() const throw()
{
	return("VM : Assert failed");
}

const char* VM::PrintException::what() const throw()
{
	return("VM : Print on non-int8");
}
