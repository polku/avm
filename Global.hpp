// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Global.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/23 13:23:41 by jmaurice          #+#    #+#             //
//   Updated: 2015/01/24 19:29:16 by jmaurice         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GLOBAL_HPP
# define GLOBAL_HPP

enum eOperandType { INT8 = 0,
					INT16 = 1,
					INT32 = 2,
					FLOAT = 3,
					DOUBLE = 4
};

enum eToken { TKI_PUSH,
			  TKI_POP,
			  TKI_DUMP,
			  TKI_ASSERT,
			  TKI_ADD,
			  TKI_SUB,
			  TKI_MUL,
			  TKI_DIV,
			  TKI_MOD,
			  TKI_PRINT,
			  TKI_EXIT,
			  TKT_INT8,
			  TKT_INT16,
			  TKT_INT32,
			  TKT_FLOAT,
			  TKT_DOUBLE,
			  TKV_INT,
			  TKV_FLOAT,
			  TK_SEP
};


#endif
