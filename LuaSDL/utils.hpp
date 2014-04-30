namespace LuaSDL {

template<typename T> size_t getArray(lutok::state& state, int index, std::vector<T> & out, size_t offset, size_t count);
template<typename T> size_t getArray(lutok::state& state, int index, std::vector<T> & out);
template<typename T> void setArray(lutok::state& state, std::vector<T> & in);
template<typename T> void setArray(lutok::state& state, T * in, size_t length);

};
