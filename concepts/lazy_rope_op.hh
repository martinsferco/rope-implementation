#include "lazy_update.hh"

template <typename T>
concept LazyRopeOp =

  requires { LazyUpdate<T>; } &&

  requires { Monoidal<typename T::Value>; } &&

  requires { Monoidal<typename T::Update>; }; 