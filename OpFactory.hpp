// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OpFactory.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/24 19:07:19 by jmaurice          #+#    #+#             //
//   Updated: 2015/02/04 19:00:23 by jmaurice         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OPFACTORY_HPP
# define OPFACTORY_HPP

# include <map>
# include <cstdint>
# include <limits>
# include <regex>
# include <boost/algorithm/string.hpp>
# include <stdexcept>
# include "IOperand.hpp"
# include "Global.hpp"

template<class T>
class Operand;

class OpFactory
{
private:
	typedef IOperand const * (OpFactory::*Func)(std::string const &) const;
	Func functions[5];
	IOperand const * createInt8 (std::string const & value) const;
	IOperand const * createInt16 (std::string const & value) const;
	IOperand const * createInt32 (std::string const & value) const;
	IOperand const * createFloat (std::string const & value) const;
	IOperand const * createDouble (std::string const & vlaue) const;

	OpFactory(OpFactory const & other);
	OpFactory& operator=(OpFactory const & other);

public:
	OpFactory();
	~OpFactory();
	IOperand const * createOperand(eOperandType type, std::string const & value) const;

	class OverflowException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class UnderflowException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class InfiniteException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class ArithmeticException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
};

#endif
