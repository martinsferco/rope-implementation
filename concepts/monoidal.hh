template<typename T>
concept Monoidal = requires(T::Value x, T::Value y) {
  
  typename T::Value;
  
  { T::op(x, y) } -> std::same_as<typename T::Value>; 
  // T::op(x, T::op(y, z)) == T::op(T::op(x, y), z)

  { T::neut()   } -> std::same_as<typename T::Value>; 
  // T::op(x, T::neut()) == x
  // T::op(T::neut(), x) == x
};