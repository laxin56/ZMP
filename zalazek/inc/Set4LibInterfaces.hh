#ifndef  SET4LIBINTERFACES_HH
#define  SET4LIBINTERFACES_HH

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include "LibInterface.hh"




/*!
 * \file
 * \brief Definicja klasy Set4LibInterfaces 
 *
 * Plik zawiera definicję klasy Set4LibInterfaces 
 */

/*!
 * \brief Klasa modeluje mapę obiektów dla wtyczek, która służy ich wyszukiwaniu i dodawaniu jako wskaźniki dzielone
 *
 */


class Set4LibInterfaces 
{
/*!
 * \brief Pole jest mapą zawierającą słowo kluczowe klasy LibInterface oraz nazwę wtyczki
 */


    std::map<std::string, std::shared_ptr<LibInterface>> set4LibInterfaces;
public:

/*!
 * \brief Konstruktor
 */
    Set4LibInterfaces(){}

/*!
 * \brief Destruktor
 */
    ~Set4LibInterfaces(){}


/*!
 * \brief Metoda szuka konkretnej wtyczki
 */
    std::shared_ptr<LibInterface> findInterface(const std::string& lib_name);

/*!
 * \brief Metoda dodaje nazwe wtyczki do mapy
 */
    bool addInterface(const std::string& lib_name);



};


/*!
 * \brief Metoda szuka konkretnej wtyczki
 * 
 * \param[in] lib_name argument zawierający nazwe konkretnego polecenia
 * \return nazwa_wtyczki zwraca nazwę polecenia z przeszukanej mapy
 */

std::shared_ptr<LibInterface> Set4LibInterfaces::findInterface(const std::string& lib_name)
{
  std::map<std::string, std::shared_ptr<LibInterface>>::iterator _iter = set4LibInterfaces.find(lib_name);
    if (_iter != set4LibInterfaces.end())
    {
        return _iter->second;
    }
    
    return nullptr;
}


/*!
 * \brief Metoda dodaje nazwe wtyczki do mapy, aby następnie móc ją przeszukać
 * \param[in] lib_name nazwa wtyczki
 * 
 * \return value zwraca wartość sygnalizująca polecenie operacji
 */

bool Set4LibInterfaces::addInterface(const std::string& lib_name)
{
    std::shared_ptr<LibInterface> lib_interface = std::make_shared<LibInterface>(lib_name);

    if(!lib_interface->initInterface())
    {
        return false;
    }

    set4LibInterfaces.insert({lib_name, lib_interface});
    
    return true;
}




#endif
