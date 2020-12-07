#ifndef  COMMAND4SET_HH
#define  COMMAND4SET_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Set
 *
 * Plik zawiera definicję klasy Interp4Set
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza ustawienie na scenie
 *
 *  Klasa modeluje wtyczke dla polecenie Set
 */
class Interp4Set: public Interp4Command {
  
   /*!
  * \brief
  *  Pole klasy
  *  Definiuje współrzędną X
  * 
  */
  double  _x_value = 0;
   /*!
  * \brief
  *  Pole klasy
  *  Definiuje współrzędną Y
  *
  * 
  */
  double  _y_value = 0;
   /*!
  * \brief
  *  Pole klasy
  *  Definiuje kąt obrotu w osi OZ
  *
  * 
  */
  double  _z_angle = 0;
 public:
  /*!
   * \brief
   * Konstruktor
   */
  Interp4Set();  
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
