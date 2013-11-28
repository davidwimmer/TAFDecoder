#ifdef TAFDECODER_EXPORTS
#define TAFDECODER_API __declspec(dllexport) 
#else
#define TAFDECODER_API __declspec(dllimport) 
#endif

#include <string>
#include <sstream> 
#include <vector>
#include <iostream>
#include <stdexcept>


namespace TAFDecoding
{
    // This class is exported from the TAFDecoder.dll
    class TheTAFDecoder
    {
    public: 
        // Returns Formated decoded TAF Message
        static TAFDECODER_API std::string decode(std::string TAFmessage, std::string airport); 

	private:
		static TAFDECODER_API std::vector<std::string> tokenize(std::string str, char delim);
		
		static TAFDECODER_API std::string decoder(std::vector<std::string> messages);
    };
}