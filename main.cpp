// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/23 14:11:25 by jmaurice          #+#    #+#             //
//   Updated: 2015/02/04 18:27:10 by jmaurice         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <fstream>
#include <stdexcept>

#include "Global.hpp"
#include "Operand.tpp"
#include "VM.hpp"
#include "AParser.hpp"
#include "ParserFile.hpp"
#include "ParserCin.hpp"

int main(int ac, char** av)
{
	try
	{
		VM vm;
		AParser* parser;

		if (ac >= 2)
			parser = new ParserFile(av[1]);
		else
			parser = new ParserCin();

		parser->exec(vm);
		if (!parser->hasExited())
			throw AParser::NoExitException();
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "Program ended by exception" << std::endl;
	}

	return 0;
}
