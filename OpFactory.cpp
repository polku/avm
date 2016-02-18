// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OpFactory.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/24 19:09:20 by jmaurice          #+#    #+#             //
//   Updated: 2015/02/04 19:02:41 by jmaurice         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Operand.tpp"
#include "OpFactory.hpp"

OpFactory::OpFactory()
{
	this->functions[INT8] = &OpFactory::createInt8;
	this->functions[INT16] = &OpFactory::createInt16;
	this->functions[INT32] = &OpFactory::createInt32;
	this->functions[FLOAT] = &OpFactory::createFloat;
	this->functions[DOUBLE] = &OpFactory::createDouble;
}

OpFactory::~OpFactory()
{}

OpFactory::OpFactory(OpFactory const & other)
{
	*this = other;
}

OpFactory& OpFactory::operator=(OpFactory const & other)
{
	this->functions[0] = other.functions[0];
	return *this;
}

IOperand const * OpFactory::createInt8 (std::string const & value) const
{
	try
	{
		boost::numeric_cast<int8_t>(boost::lexical_cast<int>(value));
	}
	catch (std::bad_cast & e)
	{
		throw OpFactory::OverflowException();
	}

	IOperand* result = new Operand<int8_t>(value, INT8);
	return result;
}

IOperand const * OpFactory::createInt16 (std::string const & value) const
{
	try
	{
		boost::lexical_cast<int16_t>(value);
	}
	catch (std::bad_cast & e)
	{
		throw OpFactory::OverflowException();
	}

	IOperand* result = new Operand<int16_t>(value, INT16);
	return result;
}

IOperand const * OpFactory::createInt32 (std::string const & value) const
{
	try
	{
		boost::lexical_cast<int32_t>(value);
	}
	catch (std::bad_cast & e)
	{
		throw OpFactory::OverflowException();
	}

	IOperand* result = new Operand<int32_t>(value, INT32);
	return result;
}

IOperand const * OpFactory::createFloat (std::string const & value) const
{
	float tmp;
	std::string copy = value;

	boost::trim(copy);
	try
	{
		tmp = boost::lexical_cast<float>(copy);
	}
	catch (std::bad_cast & e)
	{
		throw OpFactory::OverflowException();
	}
	if (tmp == 0 && !std::regex_match(copy, std::regex("[-]?[0]*[\\.]?[0]*$")))
		throw OpFactory::UnderflowException();
	if (tmp == std::numeric_limits<float>::infinity() || -tmp == std::numeric_limits<float>::infinity())
		throw OpFactory::InfiniteException();

	IOperand* result = new Operand<float>(copy, FLOAT);
	return result;
}

IOperand const * OpFactory::createDouble (std::string const & value) const
{
	double tmp;
	std::string copy = value;

	boost::trim(copy);
	try
	{
		tmp = boost::lexical_cast<double>(copy);
	}
	catch (std::bad_cast & e)
	{
		throw OpFactory::OverflowException();
	}
	if (tmp == 0 && !std::regex_match(copy, std::regex("[-]?[0]*[\\.]?[0]*$")))
		throw OpFactory::UnderflowException();
	if (tmp == std::numeric_limits<double>::infinity() || -tmp == std::numeric_limits<double>::infinity())
		throw OpFactory::InfiniteException();

	IOperand* result = new Operand<double>(copy, DOUBLE);
	return result;
}

IOperand const * OpFactory::createOperand (eOperandType type, std::string const & value) const
{
	Func func;

	func = this->functions[type];
	return (this->*func)(value);
}

const char* OpFactory::OverflowException::what() const throw()
{
	return("OpFactory : Overflow exception");
}

const char* OpFactory::UnderflowException::what() const throw()
{
	return("OpFactory : Underflow exception");
}

const char* OpFactory::InfiniteException::what() const throw()
{
	return("OpFactory : Infinite exception");
}

const char* OpFactory::ArithmeticException::what() const throw()
{
	return("VM : Arithmetic error");
}
