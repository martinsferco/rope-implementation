#include <concepts>

#include "monoidal.hh"

template <typename T>
concept LazyUpdate =

  requires { typename T::Value ; typename T::Update; } &&

  requires (typename T::Update::Value up, typename T::Value::Value val, int len)
  {
    { T::apply(up, val, len) } -> std::same_as<typename T::Value::Value>;
  };


