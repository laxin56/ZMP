#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <list>

#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include <sstream>
#include <list>
#include <thread>
#include <mutex>
#include <vector>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "xmlinterp.hh"
#include "Interp4Command.hh"
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"
#include "MobileObj.hh"
#include "Port.hh"
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Configuration.hh"

using namespace std;
using namespace xercesc;

#define LINE_SIZE 500



/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool ReadFile(const char* sFileName, Configuration &rConfig)
{
   try {

            XMLPlatformUtils::Initialize();
        }

   catch (const XMLException& toCatch) {

            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;

   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
   //DefaultHandler* pHandler = new XMLInterp4Config();
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar("config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/actions.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}


/*!
* \file
* \brief Plik main.cpp
* Tutaj wykonują się polecenia
*/

bool ExecPreprocesor( const char * NazwaPliku, std::istringstream &IStrm4Cmds )
{
    std::string Cmd4Preproc = "cpp -P ";
    char Line[LINE_SIZE];

    std::ostringstream OTmpStrm;
    Cmd4Preproc += NazwaPliku;

    FILE* pProc = popen(Cmd4Preproc.c_str(),"r");
    if (!pProc) return false;

    while (fgets(Line,LINE_SIZE,pProc)) {
        OTmpStrm << Line;
    }
    IStrm4Cmds.str(OTmpStrm.str());

    return pclose(pProc) == 0;
}



int Send(int Sk2Server, const char *sMesg)
{
  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);

  while ((IlWyslanych = write(Sk2Server,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    cerr << "*** Blad przeslania napisu." << endl;
  }
  return 0;
}

bool OpenConnection(int &rSocket)
{
  int x;

  struct sockaddr_in  serwer_dane;

  bzero((char *)&serwer_dane, sizeof(serwer_dane));


  serwer_dane.sin_family = AF_INET;
  serwer_dane.sin_addr.s_addr = inet_addr("127.0.0.1");
  serwer_dane.sin_port = htons(PORT);


  rSocket = socket(AF_INET, SOCK_STREAM, 0);

  if (rSocket < 0) {
     cerr << "*** Blad otwarcia gniazda." << endl;
     return false;
  }

  x = connect(rSocket,(struct sockaddr*)&serwer_dane,sizeof(serwer_dane));
  if (x < 0)
   {
     cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
     return false;
   }
   else if( x >= 0 )
   {
     cout << endl;
     cout << " PODLACZONO DO PORTU : " << PORT << endl;
     cout << endl;
   }

  return true;
}


int main(int argc, char **argv)
{ 
 if(argc < 2)
  {
      cerr << "Zbyt duzo arguentow wywolania!" << endl;;
      return 1;
  }

  istringstream IStrm4Cmds;

  if(!ExecPreprocesor(argv[1], IStrm4Cmds))
  {
      cerr<< "Niepoprawne wczytanie agrumentow!" << endl;;
      return 1;
  }

  cout << IStrm4Cmds.str() << endl;  
  cout << "############################" << endl;



   Configuration new_config;

  if (!ReadFile("config/config.xml", new_config) )
  {
    return 1;
  }

  int Socket4Sending;  

  if (!OpenConnection(Socket4Sending)) return 1;
  Send(Socket4Sending,"Clear\n");

    for(int i = 0; i < new_config.sceneConfiguration.size(); i++ ){


      char size[new_config.sceneConfiguration[i].size.length() +1];
      char color[new_config.sceneConfiguration[i].color.length() +1];

      strcpy(size, new_config.sceneConfiguration[i].size.c_str());
      strcpy(color, new_config.sceneConfiguration[i].color.c_str());

      Send(Socket4Sending,"Cube ");
      Send(Socket4Sending, size);
      Send(Socket4Sending, " 0 0 0 ");
      Send(Socket4Sending, " 0 0 0 ");
      Send(Socket4Sending, color);
      Send(Socket4Sending,"\n");
    }

  Send(Socket4Sending,"Close\n");
  close(Socket4Sending);


Set4LibInterfaces Lib_Interface;
string libName, object;

  while(IStrm4Cmds >> libName >> object)
  {

     shared_ptr<LibInterface> interface;
     
     if(!Lib_Interface.addInterface(libName))
     {
       cerr << " Nie zainicjowano bilbioteki " << libName << endl;
     }

      interface = Lib_Interface.findInterface(libName);    

     if(!interface->ExecActions(IStrm4Cmds))
     {
       
       cerr << "Nie wykonano operacji dla polecenia: " << IStrm4Cmds.str()<<  endl;
       return 1;

     }
  }
  
  return 0;

}
