#include "TAFDecoder.h"

using namespace std;

namespace TAFDecoding
{
	std::string TheTAFDecoder::decode(std::string TAFmessage, std::string airport)
    {
		char delimiter = ' ';
		std::vector<std::string> tokmessage = tokenize(TAFmessage, delimiter);

		std::string decodedM = decoder(tokmessage);

        return decodedM;
    }

	std::vector<std::string> TheTAFDecoder::tokenize(std::string str, char delim)  
	{ 
		std::vector<std::string> tokens; 
		std::stringstream mySstream(str); 
		std::string temp; 

		while(getline(mySstream, temp, delim))
		{
			tokens.push_back(temp);
		}
		return tokens; 
	}

	std::string TheTAFDecoder::decoder(std::vector<std::string> messages){

		string decMessage;
		string temp;

		for(int i=0; i <= messages.size()-1; i++){
			temp = messages[i];

			if(temp.find("Z") != string::npos){
				decMessage.append(temp + "\t\t" + temp.substr(0,2) + " day of the actual month - time at: " + temp.substr(2,2) + ":" + temp.substr(4,2));
				if(messages[i+1].find("/") != string::npos){
					decMessage.append("period of validity " + messages[i+1]);
					i++;
				}
				else{
					decMessage.append("\n");
				}
			}
			else if(temp.find("KT") != string::npos){
				decMessage.append(temp + "\t\t" + temp.substr(0,3) + "degree - direction of the wind and " + temp.substr(3,2) + " Knoten windspeed");
				if(temp.find("G") != string::npos){
					decMessage.append("\n\t\tGusts with " + temp.substr(5,7) + "KT");
				}
				if(messages[i+1].find("V") != string::npos){
					decMessage.append("\n\t\twith Variation of two extreme winds " + messages[i+1] + "\n");
					i++;
					if(messages[i+1].find("9999") != string::npos){
						decMessage.append(messages[i+1] + "\t\tview is 10km or more\n");
						i++;
					}
					else if(messages[i+1].find("4000") != string::npos){
						decMessage.append(messages[i+1] + "\t\tview to floor\n");
						i++;
					}
				}
				else{
					decMessage.append("\n");
				}
			}
			else if(temp.find("SCT") != string::npos){
				decMessage.append(messages[i] + "\t\tScattered - clouds at " + temp.substr(3,3) + "00 ft (SCT is 3-4 OKTAS of a possible 8)\n");
			}
			else if(temp.find("BKN") != string::npos){
				decMessage.append(messages[i] + "\t\tBroken - clouds at " + temp.substr(3,3) + "00 ft (BKN is 5-7 OKTAS of a possible 8)\n");
			}
			else if(temp.find("OVC") != string::npos){
				decMessage.append(messages[i] + "\t\t Overcast - clouds at " + temp.substr(3,3) + "00 ft (OVC is 8 OKTAS of a possible 8)\n");
			}
			else if(temp.find("FEW") != string::npos){
				decMessage.append(messages[i] + "\t\t Few - clouds at " + temp.substr(3,3) + "00 ft (FEW is 1-2 OKTAS of a possible 8)\n");
			}
			else if(temp == "CAVOK"){
				decMessage.append(temp + "\t\tClouds and visibility OK\n");
			}
			else if(temp == "NOSIG"){
				decMessage.append(temp + "\t\tNo significant changes\n");
			}
			else{
				decMessage.append(temp + "\n");
			}
		}
		return decMessage;
	}
}