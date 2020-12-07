#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


/*!
  * \file
  * \brief W tym pliku znajdują się definicje z klasy  Interp4Rotate 
  */

extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}


/*!
 * \brief
 *  Metoda CreateCmd, klasy Inter4Rotate
 *
 * \return Inter4Rotate::CreateCmd() zwraca nazwe polecenia
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}

/*!
 * \brief
 *  Konstruktor klasy Inter4Rotate
 * 
 *  Przypisuje poczatkowe wartosci do pol klasy
 *
 */
Interp4Rotate::Interp4Rotate(): _rot_speed(0), _angle(0)
{}


/*!
 *   Metoda PrintCmd klasy Inter4Rotate
 * 
 *  Metoda wypisuje na wyjście standardowe wartości pól obiektu
 *
 */
void Interp4Rotate::PrintCmd() const
{
  cout << GetCmdName() << " " << _rot_speed << " " << _angle << endl;
}


/*!
 *
 *  Metoda GetCmdName klasy Inter4Rotate
 * 
 *  Metoda zwraca nazwe użytej komendy
 * 
 */

const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *    Metoda ExecCmd klasy Inter4Rotate
 *    
 *    \param[in] *pMobObj  obiekt klasy MobileObj
 *    \param[in] Socket    gniazdo
 */
bool Interp4Rotate::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}



/*!
 *    Metoda ReadParams klasy Inter4Rotate
 *    Wczytuje wartości pól do strumienia standardowego
 * 
 *    \param[in] Strm_CmdsList strumień wejściowy
 * 
 *    \return Zwraca wartośc bool, czy wczytywanie się udało
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{

	Strm_CmdsList >>_rot_speed >> _angle;
	return !Strm_CmdsList.fail();

}


/*!
 *    Metoda CreateCmd klasy Inter4Rotate
 *    
 *    \return Metoda zwraca dynamiczny obiekt dynamiczny klasy Interp4Command
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *  Metoda PrintSyntax klasy Inter4Rotate
 * 
 *  Metoda wypisuje na wyjście standardowe parametry jakie powinno przyjmować polecenie
 * 
 * 
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  Szybkosc katowa[st/s]  Kat obrotu[st]" << endl;
}
