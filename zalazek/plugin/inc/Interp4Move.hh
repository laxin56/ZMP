#ifndef  COMMAND4MOVE_HH
#define  COMMAND4MOVE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include <string>
#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Move
 *
 * Plik zawiera definicję klasy Interp4Move
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu
 *
 *  Klasa modeluje wtyczke dla polecenie Move
 */
class Interp4Move: public Interp4Command {
  

  /*!
  * \brief
  *  Pole klasy
  *   Definiuje prędkosc poruszania sie obiektu
  *
  * 
  */
  double  _Speed_mS = 0;

  /*!
  * \brief
  * 
  *  Pole klasy
  *   Definiuje droge poruszania sie obiektu
  *
  * 
  */
  double  _Length_m = 0;
 public:
  /*!
   * \brief
   * Konstruktor wpisuje poczatkowe wartosci
   */
  Interp4Move();  
  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
   */
  virtual void PrintCmd() const;
  /*!
   * \brief Wyświetla składnię polecenia
   */
  virtual void PrintSyntax() const;
  /*!
   * \brief Wyświetla nazwę polecenia
   */
  virtual const char* GetCmdName() const;
  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   */
  virtual bool ExecCmd( MobileObj  *pMobObj, int Socket) const;
  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList);
  /*!
   * \brief Wyświetla wartości wczytanych parametrów
   */
  virtual void PrintParams() {}
  /*!
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static Interp4Command* CreateCmd();
 };

#endif
