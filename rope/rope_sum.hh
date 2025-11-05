#ifndef __ROPE_SUM_HH__
#define __ROPE_SUM_HH__

#include <vector>

class RopeSum {

public:

  /// @brief Crea un nuevo Rope de enteros de tamanio n
  /// @param n Tamanio del rope de enteros a crear.
  RopeSum(int n);

  /// @brief Actualiza una posicion del Rope
  /// @param i Posicion que queremos actualizar.
  /// @param x Nuevo valor que queremos poner.
  void update(int i, int x);

  /// @brief Nos devuelve la suma de un determinado rango del Rope.
  /// @param l Limite inferior del rango a consultar (incluyendolo).
  /// @param r Limite superior del rango a consultar (sin incluir).
  /// @return La suma del rango seleccionado.
  int interval_sum(int l, int r);

private:

  std::vector<int> data;
  void update_aux(int nodo, int l_, int r_, int i, int x);
  int interval_sum_aux(int node, int l_, int r_, int l, int r);
  int left_child(int node);
  int right_child(int node);
};

#endif // __ROPE_SUM_HH__