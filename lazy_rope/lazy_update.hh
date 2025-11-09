#include <concepts>

template <typename T>
concept LazyUpdate =

  // Necesito que tenga definidos dos tipos: Value y Update
  requires { typename T::Value ; typename T::Update; } &&

  // Necesito que tenga un metodo apply 
  requires (typename T::Update up, typename T::Value val, int len)
  {
    { T::apply(up, val, len) } -> std::same_as<typename T::Value>;
  } &&

  requires (typename T::Update x, typename T::Update y) {
    
    { T::update_op(x, y) } -> std::same_as<typename T::Update>;

    { T::neut_update() } -> std::same_as<typename T::Update>;
    // T::update_op(x, T::neut_update()) == x
    // T::update_op(T::neut_update(), x) == x
  
  } && 

  requires (typename T::Value x, typename T::Value y) {
  
    { T::value_op(x, y) } -> std::same_as<typename T::Value>; 
    // T::value_op(x, T::value_op(y, z)) == T::value_op(T::value_op(x, y), z)
    { T::neut_value()   } -> std::same_as<typename T::Value>; 
    // T::value_op(x, T::neut_value()) == x
    // T::value_op(T::neut_value(), x) == x
  };
  



