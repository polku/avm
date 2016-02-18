// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ParserCin.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/24 15:32:27 by jmaurice          #+#    #+#             //
//   Updated: 2015/01/24 20:10:03 by jmaurice         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PARSERCIN_HPP
# define PARSERCIN_HPP

# include <iostream>
# include <stdexcept>

# include "AParser.hpp"
# include "Global.hpp"
# include "VM.hpp"

class ParserCin : public AParser
{
private:
	ParserCin(ParserCin const & src);
	ParserCin & operator=(ParserCin const & other);

public:
	ParserCin();
	~ParserCin();

	virtual void exec(VM & vm);
	virtual void lex(void);
};

#endif
