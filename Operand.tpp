// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operand.tpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/23 13:09:23 by jmaurice          #+#    #+#             //
//   Updated: 2015/02/04 19:01:32 by jmaurice         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OPERAND_TPP
# define OPERAND_TPP

# include <iostream>
# include <sstream>
# include <cmath>
# include <boost/lexical_cast.hpp>
# include "IOperand.hpp"
# include "Global.hpp"
# include "OpFactory.hpp"

template <typename T>

class Operand : public IOperand
{
private:
	T _value;
	eOperandType _type;
	const std::string _description;
	Operand() {}
	Operand(Operand const & src) {}
	Operand& operator=(Operand const & other) {}

	OpFactory facto;

public:
	Operand(std::string const & value, eOperandType type) : _description(value)
	{
		this->_value = boost::numeric_cast<T>(boost::lexical_cast<double>(value));
		this->_type = type;
	}

	~Operand() {}

	int getPrecision( void ) const
	{
		switch(this->_type)
		{
		case INT8 :
			return 8;
		case INT16:
			return 16;
		case INT32:
			return 32;
		case FLOAT:
			return sizeof(float);
		case DOUBLE:
			return sizeof(double);
		}
		return 0;
	}

	eOperandType getType( void ) const
	{
		return this->_type;
	}

	T getValue(void) const
	{
		return this->_value;
	}

	IOperand const * operator+( IOperand const & rhs ) const
	{
		long double a = boost::lexical_cast<long double>(rhs.toString());
		long double b = boost::lexical_cast<long double>(this->toString());
		long double tmp = a + b;
		std::string result = boost::lexical_cast<std::string>(tmp);
		eOperandType type = (this->getType() > rhs.getType() ? this->getType() : rhs.getType());

		IOperand const * ret = this->facto.createOperand(type, result);
		return ret;
	}

	IOperand const * operator-( IOperand const & rhs ) const
	{
		long double b = boost::lexical_cast<long double>(rhs.toString());
		long double a = boost::lexical_cast<long double>(this->toString());
		long double tmp = a - b;
		std::string result = boost::lexical_cast<std::string>(tmp);
		eOperandType type = (this->getType() > rhs.getType() ? this->getType() : rhs.getType());

		IOperand const * ret = this->facto.createOperand(type, result);
		return ret;
	}

	IOperand const * operator*( IOperand const & rhs ) const
	{
		long double b = boost::lexical_cast<long double>(rhs.toString());
		long double a = boost::lexical_cast<long double>(this->toString());
		long double tmp = a * b;
		std::string result = boost::lexical_cast<std::string>(tmp);
		eOperandType type = (this->getType() > rhs.getType() ? this->getType() : rhs.getType());

		IOperand const * ret = this->facto.createOperand(type, result);
		return ret;
	}

	IOperand const * operator/( IOperand const & rhs ) const
	{
		long double b = boost::lexical_cast<long double>(rhs.toString());
		long double a = boost::lexical_cast<long double>(this->toString());

		if (b == 0)
			throw OpFactory::ArithmeticException();
		long double tmp = a / b;
		std::string result = boost::lexical_cast<std::string>(tmp);
		eOperandType type = (this->getType() > rhs.getType() ? this->getType() : rhs.getType());

		IOperand const * ret = this->facto.createOperand(type, result);
		return ret;
	}

	IOperand const * operator%( IOperand const & rhs ) const
	{
		long double b = boost::lexical_cast<long double>(rhs.toString());
		long double a = boost::lexical_cast<long double>(this->toString());

		if (b == 0)
			throw OpFactory::ArithmeticException();
		long double tmp = std::fmod(a, b);
		std::string result = boost::lexical_cast<std::string>(tmp);
		eOperandType type = (this->getType() > rhs.getType() ? this->getType() : rhs.getType());

		IOperand const * ret = this->facto.createOperand(type, result);
		return ret;
	}

	std::string const & toString( void ) const
	{
		return this->_description;
	}

};

#endif
