// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ParserFile.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/24 15:24:52 by jmaurice          #+#    #+#             //
//   Updated: 2015/02/04 19:44:06 by jmaurice         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PARSERFILE_HPP
# define PARSERFILE_HPP

# include <fstream>
# include <boost/lexical_cast.hpp>

# include "AParser.hpp"
# include "Global.hpp"
# include "VM.hpp"

class ParserFile : public AParser
{
private:
	std::fstream _input;

	ParserFile();
	ParserFile(ParserFile const & src);
	ParserFile & operator=(ParserFile const & other);

public:
	ParserFile(std::string file);
	~ParserFile();

	virtual void exec(VM & vm);
	virtual void lex(void);

	class MissingFileException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
};

#endif
