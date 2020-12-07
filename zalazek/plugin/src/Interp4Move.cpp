#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"
#include <string>



  /*! 
  * \file
  * \brief Zawiera definicję metod klasy Interp4Move
  */


using namespace std;

extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *  Metoda CreateCmd, klasy Interp4Move
 *
 * \return Interp4Move::CreateCmd() zwraca nazwe polecenia
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 * \brief
 *  Konstruktor klasy Interp4Move
 * 
 *  Przypisuje poczatkowe wartosci do pol klasy
 *
 */
Interp4Move::Interp4Move(): _Speed_mS(0), _Length_m(0)
{}


/*!
 *   Metoda PrintCmd klasy Interp4move
 * 
 *  Metoda wypisuje na wyjście standardowe wartości pól obiektu
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Speed_mS  << " " <<_Length_m << endl;
}


/*!
 *
 *  Metoda GetCmdName klasy Interp4mo
 * 
 *  Metoda zwraca nazwe użytej komendy
 * 
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *    Metoda ExecCmd klasy Interp4move
 *    
 *    \param[in] *pMobObj  obiekt klasy MobileObj
 *    \param[in] Socket    gniazdo
 */
bool Interp4Move::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *    Metoda ReadParams klasy Interp4move
 *    Wczytuje wartości pól do strumienia standardowego
 * 
 *    \param[in] Strm_CmdsList strumień wejściowy
 * 
 *    \return Zwraca wartośc bool, czy wczytywanie się udało
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _Speed_mS >> _Length_m;
	return !Strm_CmdsList.fail();
}

/*!
 *    Metoda CreateCmd klasy Interp4move
 *    
 *    \return Metoda zwraca dynamiczny obiekt dynamiczny klasy Interp4Command
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *  Metoda PrintSyntax klasy Interp4move
 * 
 *  Metoda wypisuje na wyjście standardowe parametry jakie powinno przyjmować polecenie
 * 
 * 
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
