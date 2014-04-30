#include "common.hpp"

namespace LuaSDL {

inline void endian_swap(unsigned long& x){
	x = (x>>24) | 
		((x<<8) & 0x00FF0000) |
		((x>>8) & 0x0000FF00) |
		(x<<24);
}

template<> size_t getArray<double>(lutok::state& state, int index, std::vector<double> & out, size_t offset, size_t count){
	if (state.is_table(index)){
		if (count==0 || (offset > count)){
			count = state.obj_len(index);
		}
		out.reserve(count);
		for (size_t i=offset; i<count; i++){
			state.push_integer(i+1);
			state.get_table(index);
			if (state.is_number()){
				out.push_back((double) state.to_number(-1));
			}
			state.pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<float>(lutok::state& state, int index, std::vector<float> & out, size_t offset, size_t count){
	if (state.is_table(index)){
		if (count==0 || (offset > count)){
			count = state.obj_len(index);
		}
		out.reserve(count);
		for (size_t i=offset; i<count; i++){
			state.push_integer(i+1);
			state.get_table(index);
			if (state.is_number()){
				out.push_back((float) state.to_number(-1));
			}
			state.pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<int>(lutok::state& state, int index, std::vector<int> & out, size_t offset, size_t count){
	if (state.is_table(index)){
		if (count==0 || (offset > count)){
			count = state.obj_len(index);
		}
		out.reserve(count);
		for (size_t i=offset; i<count; i++){
			state.push_integer(i+1);
			state.get_table(index);
			if (state.is_number()){
				out.push_back((int) state.to_integer(-1));
			}
			state.pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<unsigned int>(lutok::state& state, int index, std::vector<unsigned int> & out, size_t offset, size_t count){
	if (state.is_table(index)){
		if (count==0 || (offset > count)){
			count = state.obj_len(index);
		}
		out.reserve(count);
		for (size_t i=offset; i<count; i++){
			state.push_integer(i+1);
			state.get_table(index);
			if (state.is_number()){
				out.push_back((unsigned int) state.to_integer(-1));
			}
			state.pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<double>(lutok::state& state, int index, std::vector<double> & out){
	if (state.is_table(index)){
		size_t count = state.obj_len(index);
		out.reserve(count);
		for (size_t i=0; i<count; i++){
			state.push_integer(i+1);
			state.get_table(index);
			if (state.is_number()){
				out.push_back((double) state.to_number(-1));
			}
			state.pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<float>(lutok::state& state, int index, std::vector<float> & out){
	if (state.is_table(index)){
		size_t count = state.obj_len(index);
		out.reserve(count);
		for (size_t i=0; i<count; i++){
			state.push_integer(i+1);
			state.get_table(index);
			if (state.is_number()){
				out.push_back((float) state.to_number(-1));
			}
			state.pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<int>(lutok::state& state, int index, std::vector<int> & out){
	if (state.is_table(index)){
		size_t count = state.obj_len(index);
		out.reserve(count);
		for (size_t i=0; i<count; i++){
			state.push_integer(i+1);
			state.get_table(index);
			if (state.is_number()){
				out.push_back((int) state.to_integer(-1));
			}
			state.pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<unsigned int>(lutok::state& state, int index, std::vector<unsigned int> & out){
	if (state.is_table(index)){
		size_t count = state.obj_len(index);
		out.reserve(count);
		for (size_t i=0; i<count; i++){
			state.push_integer(i+1);
			state.get_table(index);
			if (state.is_number()){
				out.push_back(static_cast<unsigned int>(state.to_integer(-1)));
			}
			state.pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<unsigned char>(lutok::state& state, int index, std::vector<unsigned char> & out){
	size_t _count = 0;
	if (state.is_table(index)){
		size_t count = state.obj_len(index);
		out.reserve(count);
		for (size_t i=0; i<count; i++){
			state.push_integer(i+1);
			state.get_table(index);
			if (state.is_number()){
				out.push_back((unsigned char)state.to_integer(-1));
			}
			state.pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<std::string>(lutok::state& state, int index, std::vector<std::string> & out){
	if (state.is_table(index)){
		size_t count = state.obj_len(index);
		out.reserve(count);
		for (size_t i=0; i<count; i++){
			state.push_integer(i+1);
			state.get_table(index);
			if (state.is_number()){
				out.push_back(state.to_string(-1));
			}
			state.pop(1);
		}
	}
	return out.size();
}
template<> void setArray<double>(lutok::state& state, std::vector<double> & in){
	state.new_table();
	for (size_t i=0; i < in.size(); i++){
		state.push_integer(i+1);
		state.push_number(in[i]);
		state.set_table();
	}
}
template<> void setArray<float>(lutok::state& state, std::vector<float> & in){
	state.new_table();
	for (size_t i=0; i < in.size(); i++){
		state.push_integer(i+1);
		state.push_number(in[i]);
		state.set_table();
	}
}
template<> void setArray<int>(lutok::state& state, std::vector<int> & in){
	state.new_table();
	for (size_t i=0; i < in.size(); i++){
		state.push_integer(i+1);
		state.push_integer(in[i]);
		state.set_table();
	}
}
template<> void setArray<unsigned int>(lutok::state& state, std::vector<unsigned int> & in){
	state.new_table();
	for (size_t i=0; i < in.size(); i++){
		state.push_integer(i+1);
		state.push_integer(in[i]);
		state.set_table();
	}
}

template<> void setArray<bool>(lutok::state& state, std::vector<bool> & in){
	state.new_table();
	for (size_t i=0; i < in.size(); i++){
		state.push_integer(i+1);
		state.push_boolean(in[i]);
		state.set_table();
	}
}
template<> void setArray<char*>(lutok::state& state, std::vector<char *> & in){
	state.new_table();
	for (size_t i=0; i < in.size(); i++){
		state.push_integer(i+1);
		state.push_string(in[i]);
		state.set_table();
	}
}

template<> void setArray<double>(lutok::state& state, double * in, size_t length){
	state.new_table();
	for (size_t i=0; i < length; i++){
		state.push_integer(i+1);
		state.push_number(in[i]);
		state.set_table();
	}
}
template<> void setArray<float>(lutok::state& state, float * in, size_t length){
	state.new_table();
	for (size_t i=0; i < length; i++){
		state.push_integer(i+1);
		state.push_number(in[i]);
		state.set_table();
	}
}
template<> void setArray<int>(lutok::state& state, int * in, size_t length){
	state.new_table();
	for (size_t i=0; i < length; i++){
		state.push_integer(i+1);
		state.push_integer(in[i]);
		state.set_table();
	}
}
template<> void setArray<unsigned int>(lutok::state& state, unsigned int * in, size_t length){
	state.new_table();
	for (size_t i=0; i < length; i++){
		state.push_integer(i+1);
		state.push_integer(in[i]);
		state.set_table();
	}
}
template<> void setArray<bool>(lutok::state& state, bool * in, size_t length){
	state.new_table();
	for (size_t i=0; i < length; i++){
		state.push_integer(i+1);
		state.push_boolean(in[i]);
		state.set_table();
	}
}
template<> void setArray<char*>(lutok::state& state, char ** in, size_t length){
	state.new_table();
	for (size_t i=0; i < length; i++){
		state.push_integer(i+1);
		state.push_string(in[i]);
		state.set_table();
	}
}
template<> void setArray<unsigned char>(lutok::state& state, unsigned char * in, size_t length){
	state.new_table();
	for (size_t i=0; i < length; i++){
		state.push_integer(i+1);
		state.push_integer(in[i]);
		state.set_table();
	}
}

};
