#include <iostream>
#include "Interp4Pause.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


/*!
  *   \file
  * \brief W tym pliku znajdują się definicje z klasy  Interp4Pause 
  */

extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Pause"; }
}




/*!
 * \brief
 *  Metoda CreateCmd, klasy Inter4Pause
 *
 * \return Inter4Pause::CreateCmd() zwraca nazwe polecenia
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}


/*!
 * \brief
 *  Konstruktor klasy Inter4Pause
 * 
 *  Przypisuje poczatkowe wartosci do pol klasy
 *
 */
Interp4Pause::Interp4Pause(): _Pause_Time_ms(0)
{}


/*!
 *   Metoda PrintCmd klasy Inter4Pause
 * 
 *  Metoda wypisuje na wyjście standardowe wartości pól obiektu
 *
 */
void Interp4Pause::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Pause_Time_ms  <<  endl;
}


/*!
 *
 *  Metoda GetCmdName klasy Inter4Pause
 * 
 *  Metoda zwraca nazwe użytej komendy
 * 
 */
const char* Interp4Pause::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *    Metoda ExecCmd klasy Inter4Pause
 *    
 *    \param[in] *pMobObj  obiekt klasy MobileObj
 *    \param[in] Socket    gniazdo
 */
bool Interp4Pause::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *    Metoda ReadParams klasy Inter4Pause
 *    Wczytuje wartości pól do strumienia standardowego
 * 
 *    \param[in] Strm_CmdsList strumień wejściowy
 * 
 *    \return Zwraca wartośc bool, czy wczytywanie się udało
 */
bool Interp4Pause::ReadParams(std::istream& Strm_CmdsList)
{
	Strm_CmdsList >>_Pause_Time_ms;
	return !Strm_CmdsList.fail();

}


/*!
 *    Metoda CreateCmd klasy Inter4Pause
 *    
 *    \return Metoda zwraca dynamiczny obiekt dynamiczny klasy Interp4Command
 */
Interp4Command* Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}

/*!
 *  Metoda PrintSyntax klasy Inter4Pause
 * 
 *  Metoda wypisuje na wyjście standardowe parametry jakie powinno przyjmować polecenie
 * 
 * 
 */
void Interp4Pause::PrintSyntax() const
{
  cout << "   Pause  NazwaObiektu  Pauza[ms]" << endl;
}
