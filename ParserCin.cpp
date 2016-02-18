// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ParserCin.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/24 15:33:41 by jmaurice          #+#    #+#             //
//   Updated: 2015/02/04 18:07:49 by jmaurice         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ParserCin.hpp"

ParserCin::ParserCin() : AParser()
{}

ParserCin::ParserCin(ParserCin const & src) : AParser(src)
{
	*this = src;
}

ParserCin & ParserCin::operator=(ParserCin const & other)
{
	AParser::operator=(other);
	return *this;
}

ParserCin::~ParserCin()
{}

void ParserCin::exec(VM & vm)
{
	while (!this->isFinished())
	{
		this->lex();
		this->parse(vm);
	}
}

void ParserCin::lex(void)
{
	std::string line;

	this->_pgm.clear();

	std::cout << "~> ";
	std::getline(std::cin, line);
	if (std::cin.eof() || (line.at(0) == ';' && line.at(1) == ';'))
		this->_finished = true;
	std::replace(line.begin(), line.end(), '\t', ' ');
	std::string line2 = line.substr(0, line.find(";"));
	std::vector<std::string> substr;
	boost::split(substr, line2, boost::is_any_of(" ()"));
	substr.push_back("\n");
	for (auto it = substr.begin() ; it != substr.end() ; ++it)
	{
		this->_linum += 1;
		if (isInstr(*it))
			continue;
		if (isType(*it))
			continue;
		if (isInt(*it))
			continue;
		if (isFloat(*it))
			continue;
		if (isSep(*it))
			continue;
		if (*it == "")
			continue;
		throw AParser::LexicalException();
	}

}
