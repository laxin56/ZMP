#ifndef  COMMAND4PAUSE_HH
#define  COMMAND4PAUSE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Pause
 *
 * Plik zawiera definicję klasy Interp4Pause
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego pauzę
 *
 *  Klasa modeluje wtyczke dla polecenie Pause
 */
class Interp4Pause: public Interp4Command {
 

 /*!
  * \brief
  *  Pole klasy
  *  Definiuje czas zatrzymania

  */
  double  _Pause_Time_ms = 0;

 public:
  /*!
   * \brief
   * Konstruktor
   */
  Interp4Pause();  
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
