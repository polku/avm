// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VM.hpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/23 13:33:38 by jmaurice          #+#    #+#             //
//   Updated: 2015/02/04 19:00:30 by jmaurice         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef VM_H
# define VM_H

# include <iostream>
# include <string>
# include <deque>
# include <cstdint>
# include <stdexcept>
# include "Global.hpp"
# include "IOperand.hpp"
# include "Operand.tpp"
# include "OpFactory.hpp"

class VM
{
private:
    std::deque<const IOperand *> _stack;
	void checkSize(unsigned int) const;
	OpFactory _facto;

public:
    VM(void);
    VM(VM const & src);
    ~VM(void);
    VM & operator=(VM const & other);

	void ipush(const IOperand* op);
	void ipop(void);
	void idump(void) const;
	void iassert(const IOperand* op) const;
	void iadd(void);
	void isub(void);
	void imul(void);
	void idiv(void);
	void imod(void);
	void iprint(void) const;

	class StackSizeException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class AssertException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class PrintException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
};

#endif
