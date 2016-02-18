// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AParser.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/24 15:22:46 by jmaurice          #+#    #+#             //
//   Updated: 2015/02/04 18:26:05 by jmaurice         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef APARSER_HPP
# define APARSER_HPP

# include <iostream>
# include <fstream>
# include <list>
# include <utility>
# include <vector>
# include <algorithm>
# include <boost/algorithm/string.hpp>
# include <regex>

# include "Global.hpp"
# include "IOperand.hpp"
# include "VM.hpp"
# include "OpFactory.hpp"

class AParser
{
private:

protected:
	typedef std::pair<eToken, std::string> Token;
	typedef std::list<Token> Pgm;

	bool _exit;
	bool _finished;
	int _linum;
	Pgm _pgm;
	OpFactory _facto;

	AParser();
	AParser(AParser const & src);
	AParser & operator=(AParser const & other);

	bool isInstr(std::string token);
	bool isType(std::string token);
	bool isInt(std::string token);
	bool isFloat(std::string token);
	bool isSep(std::string token);

public:
	virtual ~AParser();

	bool hasExited(void);
	bool isFinished(void);

	virtual void exec(VM & vm) = 0;
	virtual void lex(void) = 0;
	IOperand const* valueInstr(Pgm::iterator & it);
	bool noValueInstr(Pgm::iterator & it);
	void parse(VM & vm);

	static std::vector<std::string> instructions;
	static std::vector<std::string> types;

	void debug(void);

	static eToken getEToken(std::string value);

	class BadValueException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class LexicalException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class SyntaxException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class NoExitException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

};

#endif
