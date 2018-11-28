// testObject.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<string>
#include<vector>
#include<assert.h>
#include <iostream> 


/* All alphanumeric characters except for "0", "I", "O", and "l" */
static const char* pszBase58 = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
std::string EncodeBase58(const unsigned char* pbegin, const unsigned char* pend)
{
	// Skip & count leading zeroes.
	int zeroes = 0;
	while (pbegin != pend && *pbegin == 0)
	{
		pbegin++;
		zeroes++;
	}
	// Allocate enough space in big-endian base58 representation.
	std::vector<unsigned char> b58((pend - pbegin) * 138 / 100 + 1); // log(256) / log(58), rounded up.
																	 // Process the bytes.
	while (pbegin != pend)
	{
		int carry = *pbegin;
		// Apply "b58 = b58 * 256 + ch".
		for (std::vector<unsigned char>::reverse_iterator it = b58.rbegin(); it != b58.rend(); it++)
		{
			carry += 256 * (*it);
			*it = carry % 58;
			carry /= 58;
		}
		assert(carry == 0);
		pbegin++;
	}
	// Skip leading zeroes in base58 result.
	std::vector<unsigned char>::iterator it = b58.begin();
	while (it != b58.end() && *it == 0)
		it++;
	// Translate the result into a string.
	std::string str;
	str.reserve(zeroes + (b58.end() - it));
	str.assign(zeroes, '1');
	while (it != b58.end())
		str += pszBase58[*(it++)];
	return str;
}
int main()
{
	assert(true);
	std::vector< unsigned char> vc = {'s','f','g','h','r','s','h','s'};
	std::string str = EncodeBase58(&vc[0],&vc[0]+vc.size());
	std::cout << str << std::endl;
	system("pause");
    return 0;
}

