#ifndef  LIBINTERFACE_HH
#define  LIBINTERFACE_HH

#include <iostream>
#include <string>
#include "Interp4Command.hh"
#include <dlfcn.h>
#include <memory>


/*!
 * \file
 * \brief Definicja klasy LibInterface
 *
 * Plik zawiera definicję klasy LibInterface
 */

/*!
 * \brief Klasa modeluje interfejs dla wtyczek
 *
 */

class LibInterface
{
  
 /*!
  *  \brief Pole przechowujące nazwe polecenia
  */

    std::string _CmdName;

/*!
  *  \brief Pole przechowujące wskaźnik na biblioteke
  */
  
    void *LibHnd;

    /*!
  *  \brief Pole przechowujące wskaźnik na wskaźnik Interp4Command
  * 
  */
  
    Interp4Command *(*pCreateCmd)(void);
  
public:

        /*!
    *  \brief 
    * Konstruktor inicjuje pole klasy
    * 
    * 
    */

    LibInterface(std::string _name){ this -> _CmdName = _name;};

        /*!
        *  \brief 
        * Destruktor
        * Zamyka biblioteke
        */
    ~LibInterface(){ dlclose(LibHnd);}
  

       /*!
        *  \brief 
        * Metoda wczytuje polecenia do strumienia i je wypisuje
        * 
        */
    bool ExecActions(std::istream &strm);

          /*!
            *  \brief 
            * Wczytuje biblioteki
            * 
            */
    bool initInterface();
 
  
};


          /*!
            *  \brief 
            * Wczytuje biblioteki za pomocą pola _CmdName
            * 
            * \return value zwraca wartość, która wskazuje na to, czy operacja się udała
            * 
            */

bool LibInterface::initInterface()
{
    std::string libName;

    libName = "libInterp4" + _CmdName + ".so";

    std::cout << "Wczytanie biblioteki " << libName.c_str() << std::endl;
    
    LibHnd = dlopen(libName.c_str(),RTLD_LAZY); 

    if(!LibHnd)
    {
      std::cerr << "Nie udalo sie wczytac biblioteki " << libName.c_str() << std::endl;
        return false;
    }

    void *pFun;
    
    pFun = dlsym(LibHnd,"CreateCmd");

    if(!pFun)
    {
      std::cerr << "Nie znaleziono polecenia Create CMD " << std::endl;
        return false;
    }

    pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);

    return true;
}



       /*!
            *  \brief 
            * 
            * Metoda wczytuje polecenia do strumienia i je wypisuje
            * 
            * \param[in] strm parametr wejściowy to strumień do którego czytane są polecenia
            * 
            * \return value zwraca wartość, która wskazuje na to, czy operacja się udała
            * 
            */

bool LibInterface::ExecActions(std::istream &strm)
{
    Interp4Command *pCmd = pCreateCmd();
    
    std::cout << std::endl;
    std::cout << "##################################" << std::endl;
    std::cout << "Polecenie: " << pCmd->GetCmdName()   << std::endl;
    
    pCmd->PrintSyntax();
  
    if(!pCmd->ReadParams(strm))
    {
        return false;
    }

    std::cout << std::endl;
     pCmd->PrintCmd();
    std::cout << std::endl;

    delete pCmd;


    return true;
}





#endif
