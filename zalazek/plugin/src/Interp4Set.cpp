#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;

/*!
  * \file
  * \brief W tym pliku znajdują się definicje z klasy  Interp4Set 
  */


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}



/*!
 * \brief
 *  Metoda CreateCmd, klasy Inter4Set
 *
 * \return Inter4Set::CreateCmd() zwraca nazwe polecenia
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}

/*!
 * \brief
 *  Konstruktor klasy Inter4Set
 * 
 *  Przypisuje poczatkowe wartosci do pol klasy
 *
 */
Interp4Set::Interp4Set():  _x_value(0),  _y_value(0),  _z_angle(0)
{}


/*!
 *   Metoda PrintCmd klasy Inter4Set
 * 
 *  Metoda wypisuje na wyjście standardowe wartości pól obiektu
 *
 */
void Interp4Set::PrintCmd() const
{
  cout << GetCmdName() << " " << _x_value << " " << _y_value << " " << _z_angle << endl;
}


/*!
 *
 *  Metoda GetCmdName klasy Inter4Set
 * 
 *  Metoda zwraca nazwe użytej komendy
 * 
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *    Metoda ExecCmd klasy Inter4Set
 *    
 *    \param[in] *pMobObj  obiekt klasy MobileObj
 *    \param[in] Socket    gniazdo
 */
bool Interp4Set::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}



/*!
 *    Metoda ReadParams klasy Inter4Set
 *    Wczytuje wartości pól do strumienia standardowego
 * 
 *    \param[in] Strm_CmdsList strumień wejściowy
 * 
 *    \return Zwraca wartośc bool, czy wczytywanie się udało
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{

  Strm_CmdsList >> _x_value >> _y_value >> _z_angle;
	return !Strm_CmdsList.fail();

}

/*!
 *    Metoda CreateCmd klasy Inter4Set
 *    
 *    \return Metoda zwraca dynamiczny obiekt dynamiczny klasy Interp4Command
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *  Metoda PrintSyntax klasy Inter4Set
 * 
 *  Metoda wypisuje na wyjście standardowe parametry jakie powinno przyjmować polecenie
 * 
 * 
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  WspolrzednaX[m]  WspolrzednaY[m] KatOZ [st]" << endl;
}
