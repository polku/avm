// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AParser.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/24 15:25:04 by jmaurice          #+#    #+#             //
//   Updated: 2015/02/04 19:03:24 by jmaurice         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "AParser.hpp"

std::vector <std::string> AParser::instructions = {"push" , "pop", "dump", "assert", "add", "sub", "mul", "div", "mod", "print", "exit"};

std::vector <std::string> AParser::types = {"int8", "int16", "int32", "float", "double"};

AParser::AParser() : _exit(false), _finished(false), _linum(0)
{}

AParser::AParser(AParser const & src)
{
	*this = src;
}

AParser & AParser::operator=(AParser const & other)
{
	this->_finished = other._finished;
	this->_linum = other._linum;
	return *this;
}

AParser::~AParser()
{}

bool AParser::isFinished(void)
{
	return this->_finished;
}

bool AParser::hasExited(void)
{
	return this->_exit;
}

bool AParser::isInstr(std::string token)
{
	if ( std::find( AParser::instructions.begin(), AParser::instructions.end(), token) != AParser::instructions.end() )
	{
		eToken tmp = getEToken(token);
		Token tk(tmp, token);
		this->_pgm.push_back(tk);
		return true;
	}
	return false;
}

bool AParser::isType(std::string token)
{
	if ( std::find( AParser::types.begin(), AParser::types.end(), token) != AParser::types.end() )
	{
		eToken tmp = getEToken(token);
		Token tk(tmp, token);
		this->_pgm.push_back(tk);
		return true;
	}
	return false;
}

bool AParser::isInt(std::string token)
{
	if (std::regex_match(token, std::regex("[-]?[0-9]+")))
	{
		Token tk(TKV_INT, token);
		this->_pgm.push_back(tk);
		return true;
	}
	return false;
}

bool AParser::isFloat(std::string token)
{
	if (std::regex_match(token, std::regex("[-]?[0-9]+[\\.][0-9]+")))
	{
		Token tk(TKV_FLOAT, token);
		this->_pgm.push_back(tk);
		return true;
	}
	return false;
}

bool AParser::isSep(std::string token)
{
	if (token == "\n")
	{
		Token tk(TK_SEP, token);
		this->_pgm.push_back(tk);
		return true;
	}
	return false;
}

void AParser::debug(void)
{
	for (auto it = this->_pgm.begin() ; it != this->_pgm.end() ; ++it)
	{
		Token tmp = *it;
		std::cout << std::get<0>(tmp) << " / " << std::get<1>(tmp) << std::endl;
	}
}

IOperand const* AParser::valueInstr(Pgm::iterator & it)
{
	IOperand const* res = 0;

	it++;
	switch (std::get<0>(*it))
	{
		case TKT_INT8:
			it++;
			if (std::get<0>(*it) != TKV_INT)
				throw AParser::BadValueException();
			res = this->_facto.createOperand(INT8, std::get<1>(*it));
			break;

		case TKT_INT16:
			it++;
			if (std::get<0>(*it) != TKV_INT)
				throw AParser::BadValueException();
			res = this->_facto.createOperand(INT16, std::get<1>(*it));
			break;

		case TKT_INT32:
			it++;
			if (std::get<0>(*it) != TKV_INT)
				throw AParser::BadValueException();
			res = this->_facto.createOperand(INT32, std::get<1>(*it));
			break;

		case TKT_FLOAT:
			it++;
			if (std::get<0>(*it) != TKV_FLOAT && std::get<0>(*it) != TKV_INT)
				throw AParser::BadValueException();
			res = this->_facto.createOperand(FLOAT, std::get<1>(*it));
			break;

		case TKT_DOUBLE:
			it++;
			if (std::get<0>(*it) != TKV_FLOAT && std::get<0>(*it) != TKV_INT)
				throw AParser::BadValueException();
			res = this->_facto.createOperand(DOUBLE, std::get<1>(*it));
			break;

		default:
			throw AParser::SyntaxException();
			break;
	}
	it++;
	if (std::get<0>(*it) != TK_SEP)
 	{
		throw AParser::SyntaxException();
	}

	return res;
}

bool AParser::noValueInstr(Pgm::iterator & it)
{
	it++;
	if (std::get<0>(*it) == TK_SEP)
		return true;
	else
		throw AParser::SyntaxException();
}

void AParser::parse(VM & vm)
{
	IOperand const * op;

	for (auto it = this->_pgm.begin() ; it != this->_pgm.end() ; ++it)
	{
		switch(std::get<0>(*it))
		{
			case TKI_PUSH:
				op = valueInstr(it);
			 	vm.ipush(op);
				break;

			case TKI_POP:
				noValueInstr(it);
				vm.ipop();
				break;

			case TKI_DUMP:
				noValueInstr(it);
				vm.idump();
				break;

			case TKI_ASSERT:
				op = valueInstr(it);
				if (op)
					vm.iassert(op);
			 	break;

			case TKI_ADD:
				noValueInstr(it);
				vm.iadd();
				break;

			case TKI_SUB:
				noValueInstr(it);
				vm.isub();
				break;

			case TKI_MUL:
				noValueInstr(it);
				vm.imul();
				break;

			case TKI_DIV:
				noValueInstr(it);
				vm.idiv();
				break;

			case TKI_MOD:
				noValueInstr(it);
				vm.imod();
				break;

			case TKI_PRINT:
				noValueInstr(it);
				vm.iprint();
				break;

			case TKI_EXIT:
				this->_exit = true;
			 	break;

			case TK_SEP:
				break;

			default:
				std::cout << "default pas affiche" << std::endl;
				break;
		}
	}
}

eToken AParser::getEToken(std::string token)
{
	if (token == "push") return TKI_PUSH;
	if (token == "pop") return TKI_POP;
	if (token == "dump") return TKI_DUMP;
	if (token == "assert") return TKI_ASSERT;
	if (token == "add") return TKI_ADD;
	if (token == "sub") return TKI_SUB;
	if (token == "mul") return TKI_MUL;
	if (token == "div") return TKI_DIV;
	if (token == "mod") return TKI_MOD;
	if (token == "print") return TKI_PRINT;
	if (token == "exit") return TKI_EXIT;
	if (token == "int8") return TKT_INT8;
	if (token == "int16") return TKT_INT16;
	if (token == "int32") return TKT_INT32;
	if (token == "float") return TKT_FLOAT;
	if (token == "double") return TKT_DOUBLE;
	return TKI_EXIT;
}

const char* AParser::BadValueException::what() const throw()
{
	return("Parser : value don't match the type for variable");
}

const char* AParser::LexicalException::what() const throw()
{
	return("Parser : Unknown token");
}

const char* AParser::SyntaxException::what() const throw()
{
	return("Parser : Syntax error");
}

const char* AParser::NoExitException::what() const throw()
{
	return("Parser : no exit found");
}
