#include <concepts>


template <typename T>
concept LazyUpdate =

  // Necesito que tenga definidos dos tipos: Value y Update
  requires { typename T::Value ; typename T::Update; } &&

  // Necesito que tenga un metodo apply 
  requires (typename T::Update up, typename T::Value val, int len)
  {
    { T::apply(up, val, len) } -> std::same_as<typename T::Value>;
  };
