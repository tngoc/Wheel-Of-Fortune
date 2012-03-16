#include "utils.h"

double Utils::timecount() {
	static double count_temp;
	double count;
	double result;
	count = timeGetTime();
	result = count-count_temp;
	count_temp = count;
	return result;
}


string Utils::narrow( const wstring& str ){
	ostringstream stm ;
	const ctype<char>& ctfacet =
		use_facet< ctype<char> >( stm.getloc() ) ;
	for( size_t i=0 ; i<str.size() ; ++i )
		stm << ctfacet.narrow( str[i], 0 ) ;
	return stm.str() ;
}
