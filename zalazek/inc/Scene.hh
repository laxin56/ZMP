#include <stdio>
#include <iostream>
#include <string>
#include "MobileObj.hh"


using namespace std;

/*!
 * \file
 * \brief Definicja klasy Scene
 *
 * Plik zawiera definicję klasy Scene ...
 */

/*!
 * \brief Modeluje pojecie przestrzeni na której ustawiają się obiekty
 *
 */

typedef map<string,shared_ptr<MobileObj>> Set4Obj
  
class Scene{

  /*!
    * \brief 
    * Wskaznik dzielony na typ MobileObj 
    */
  Set4Obj Set_MobileObj;
  
  
 public:

    /*!
    * \brief Szuka obiektu MobileObj
    */
  shared_ptr<MobileObj> FindMobileObj (const char *_obj )
  {
    
    //???

  }


    /*!
    * \brief Szuka obiektu MobileObj
    */
  shared_ptr<MobileObj> FindMobileObj (const string &_obj)
  {

    shared_ptr<MobileObj> object;
    
    Set4Obj::const_iterator it = Set_MobileObj.find(_obj);

    object = it->second;

    return object;
    
  }
  

};
