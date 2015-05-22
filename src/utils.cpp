#include "common.hpp"

namespace LuaSDL {

inline void endian_swap(unsigned long& x){
	x = (x>>24) | 
		((x<<8) & 0x00FF0000) |
		((x>>8) & 0x0000FF00) |
		(x<<24);
}
/*
template<> size_t getArray<double>(State & state, int index, std::vector<double> & out, size_t offset, size_t count){
	if (stack->is<LUA_TTABLE>(index)){
		if (count==0 || (offset > count)){
			count = state.obj_len(index);
		}
		out.reserve(count);
		for (size_t i=offset; i<count; i++){
			stack->push<int>(i+1);
			state.get_table(index);
			if (stack->is<LUA_TNUMBER>()){
				out.push_back((double) state.to_number(-1));
			}
			stack->pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<float>(State & state, int index, std::vector<float> & out, size_t offset, size_t count){
	if (stack->is<LUA_TTABLE>(index)){
		if (count==0 || (offset > count)){
			count = state.obj_len(index);
		}
		out.reserve(count);
		for (size_t i=offset; i<count; i++){
			stack->push<int>(i+1);
			state.get_table(index);
			if (stack->is<LUA_TNUMBER>()){
				out.push_back((float) state.to_number(-1));
			}
			stack->pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<int>(State & state, int index, std::vector<int> & out, size_t offset, size_t count){
	if (stack->is<LUA_TTABLE>(index)){
		if (count==0 || (offset > count)){
			count = state.obj_len(index);
		}
		out.reserve(count);
		for (size_t i=offset; i<count; i++){
			stack->push<int>(i+1);
			state.get_table(index);
			if (stack->is<LUA_TNUMBER>()){
				out.push_back((int) stack->to<int>(-1));
			}
			stack->pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<unsigned int>(State & state, int index, std::vector<unsigned int> & out, size_t offset, size_t count){
	if (stack->is<LUA_TTABLE>(index)){
		if (count==0 || (offset > count)){
			count = state.obj_len(index);
		}
		out.reserve(count);
		for (size_t i=offset; i<count; i++){
			stack->push<int>(i+1);
			state.get_table(index);
			if (stack->is<LUA_TNUMBER>()){
				out.push_back((unsigned int) stack->to<int>(-1));
			}
			stack->pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<double>(State & state, int index, std::vector<double> & out){
	if (stack->is<LUA_TTABLE>(index)){
		size_t count = state.obj_len(index);
		out.reserve(count);
		for (size_t i=0; i<count; i++){
			stack->push<int>(i+1);
			state.get_table(index);
			if (stack->is<LUA_TNUMBER>()){
				out.push_back((double) state.to_number(-1));
			}
			stack->pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<float>(State & state, int index, std::vector<float> & out){
	if (stack->is<LUA_TTABLE>(index)){
		size_t count = state.obj_len(index);
		out.reserve(count);
		for (size_t i=0; i<count; i++){
			stack->push<int>(i+1);
			state.get_table(index);
			if (stack->is<LUA_TNUMBER>()){
				out.push_back((float) state.to_number(-1));
			}
			stack->pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<int>(State & state, int index, std::vector<int> & out){
	if (stack->is<LUA_TTABLE>(index)){
		size_t count = state.obj_len(index);
		out.reserve(count);
		for (size_t i=0; i<count; i++){
			stack->push<int>(i+1);
			state.get_table(index);
			if (stack->is<LUA_TNUMBER>()){
				out.push_back((int) stack->to<int>(-1));
			}
			stack->pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<unsigned int>(State & state, int index, std::vector<unsigned int> & out){
	if (stack->is<LUA_TTABLE>(index)){
		size_t count = state.obj_len(index);
		out.reserve(count);
		for (size_t i=0; i<count; i++){
			stack->push<int>(i+1);
			state.get_table(index);
			if (stack->is<LUA_TNUMBER>()){
				out.push_back(static_cast<unsigned int>(stack->to<int>(-1)));
			}
			stack->pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<unsigned char>(State & state, int index, std::vector<unsigned char> & out){
	size_t _count = 0;
	if (stack->is<LUA_TTABLE>(index)){
		size_t count = state.obj_len(index);
		out.reserve(count);
		for (size_t i=0; i<count; i++){
			stack->push<int>(i+1);
			state.get_table(index);
			if (stack->is<LUA_TNUMBER>()){
				out.push_back((unsigned char)stack->to<int>(-1));
			}
			stack->pop(1);
		}
	}
	return out.size();
}
template<> size_t getArray<std::string>(State & state, int index, std::vector<std::string> & out){
	if (stack->is<LUA_TTABLE>(index)){
		size_t count = state.obj_len(index);
		out.reserve(count);
		for (size_t i=0; i<count; i++){
			stack->push<int>(i+1);
			state.get_table(index);
			if (stack->is<LUA_TNUMBER>()){
				out.push_back(stack->to<const std::string>(-1));
			}
			stack->pop(1);
		}
	}
	return out.size();
}
template<> void setArray<double>(State & state, std::vector<double> & in){
	stack->newTable();
	for (size_t i=0; i < in.size(); i++){
		stack->push<int>(i+1);
		state.push_number(in[i]);
		stack->setTable();
	}
}
template<> void setArray<float>(State & state, std::vector<float> & in){
	stack->newTable();
	for (size_t i=0; i < in.size(); i++){
		stack->push<int>(i+1);
		state.push_number(in[i]);
		stack->setTable();
	}
}
template<> void setArray<int>(State & state, std::vector<int> & in){
	stack->newTable();
	for (size_t i=0; i < in.size(); i++){
		stack->push<int>(i+1);
		stack->push<int>(in[i]);
		stack->setTable();
	}
}
template<> void setArray<unsigned int>(State & state, std::vector<unsigned int> & in){
	stack->newTable();
	for (size_t i=0; i < in.size(); i++){
		stack->push<int>(i+1);
		stack->push<int>(in[i]);
		stack->setTable();
	}
}

template<> void setArray<bool>(State & state, std::vector<bool> & in){
	stack->newTable();
	for (size_t i=0; i < in.size(); i++){
		stack->push<int>(i+1);
		stack->push<bool>(in[i]);
		stack->setTable();
	}
}
template<> void setArray<char*>(State & state, std::vector<char *> & in){
	stack->newTable();
	for (size_t i=0; i < in.size(); i++){
		stack->push<int>(i+1);
		stack->push<const std::string>(in[i]);
		stack->setTable();
	}
}

template<> void setArray<double>(State & state, double * in, size_t length){
	stack->newTable();
	for (size_t i=0; i < length; i++){
		stack->push<int>(i+1);
		state.push_number(in[i]);
		stack->setTable();
	}
}
template<> void setArray<float>(State & state, float * in, size_t length){
	stack->newTable();
	for (size_t i=0; i < length; i++){
		stack->push<int>(i+1);
		state.push_number(in[i]);
		stack->setTable();
	}
}
template<> void setArray<int>(State & state, int * in, size_t length){
	stack->newTable();
	for (size_t i=0; i < length; i++){
		stack->push<int>(i+1);
		stack->push<int>(in[i]);
		stack->setTable();
	}
}
template<> void setArray<unsigned int>(State & state, unsigned int * in, size_t length){
	stack->newTable();
	for (size_t i=0; i < length; i++){
		stack->push<int>(i+1);
		stack->push<int>(in[i]);
		stack->setTable();
	}
}
template<> void setArray<bool>(State & state, bool * in, size_t length){
	stack->newTable();
	for (size_t i=0; i < length; i++){
		stack->push<int>(i+1);
		stack->push<bool>(in[i]);
		stack->setTable();
	}
}
template<> void setArray<char*>(State & state, char ** in, size_t length){
	stack->newTable();
	for (size_t i=0; i < length; i++){
		stack->push<int>(i+1);
		stack->push<const std::string>(in[i]);
		stack->setTable();
	}
}
template<> void setArray<unsigned char>(State & state, unsigned char * in, size_t length){
	stack->newTable();
	for (size_t i=0; i < length; i++){
		stack->push<int>(i+1);
		stack->push<int>(in[i]);
		stack->setTable();
	}
}
*/
};
