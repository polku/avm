// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ParserFile.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/24 15:26:27 by jmaurice          #+#    #+#             //
//   Updated: 2015/02/04 19:43:39 by jmaurice         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ParserFile.hpp"

ParserFile::ParserFile()
{}

ParserFile::ParserFile(std::string file) : AParser()
{
	this->_input.open(file);
	if (!this->_input)
		throw ParserFile::MissingFileException();
}

ParserFile::ParserFile(ParserFile const & src) : AParser(src)
{
	*this = src;
}

ParserFile & ParserFile::operator=(ParserFile const & other)
{
	AParser::operator=(other);
	return *this;
}

ParserFile::~ParserFile()
{}

void ParserFile::exec(VM & vm)
{
	this->lex();
	this->parse(vm);
}

void ParserFile::lex(void)
{
	std::string line;

	while (!this->_finished)
	{
		std::getline(this->_input, line);

		if (this->_input.eof())
			this->_finished = true;
		if (line == "" || line == "\n")
			continue;
		if (std::regex_match(line, std::regex("^;.*")))
			continue;
		std::replace(line.begin(), line.end(), '\t', ' ');
		std::string line2 = line.substr(0, line.find(";"));
		std::vector<std::string> substr;
		boost::split(substr, line2, boost::is_any_of(" ()"));
		substr.push_back("\n");
		this->_linum += 1;
		for (auto it = substr.begin() ; it != substr.end() ; ++it)
		{
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

			std::string n_line = boost::lexical_cast<std::string>(this->_linum);
			throw AParser::LexicalException();
		}
	}
}

const char* ParserFile::MissingFileException::what() const throw()
{
	return("ParserFile : File not found");
}
