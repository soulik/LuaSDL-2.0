// Copyright 2011 Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
// * Neither the name of Google Inc. nor the names of its contributors
//   may be used to endorse or promote products derived from this software
//   without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/// \file state.hpp
/// Provides the state wrapper class for the Lua C state.

#if !defined(LUTOK_STATE_HPP)
#define LUTOK_STATE_HPP

#include <string>

#ifdef _WIN32
    #include <memory>
#else
    #include <trl/memory>
#endif

namespace lutok {


class debug;
class state;

/// The type of a C++ function that can be bound into Lua.
///
/// Functions of this type are free to raise exceptions.  These will not
/// propagate into the Lua C API.  However, any such exceptions will be reported
/// as a Lua error and their type will be lost.
typedef int (*cxx_function)(state&);
typedef int (*cxx_function_ex)(void *);

struct  cxx_function_ex_holder {
	cxx_function_ex function;
	void * arg;
};


/// Stack index constant pointing to the globals table (_G).
extern const int globals_index;


/// A RAII model for the Lua state.
///
/// This class holds the state of the Lua interpreter during its existence and
/// provides wrappers around several Lua library functions that operate on such
/// state.
///
/// These wrapper functions differ from the C versions in that they use the
/// implicit state hold by the class, they use C++ types where appropriate and
/// they use exceptions to report errors.
///
/// The wrappers intend to be as lightweight as possible but, in some
/// situations, they are pretty complex because they need to do extra work to
/// capture the errors reported by the Lua C API.  We prefer having fine-grained
/// error control rather than efficiency, so this is OK.
class state {
    struct impl;

    /// Pointer to the shared internal implementation.
    std::tr1::shared_ptr< impl > _pimpl;

    void* new_userdata_voidp(const size_t);
    void* to_userdata_voidp(const int);
    void* check_userdata_voidp(const int narg, const std::string& name);

    friend class state_c_gate;
	template <class T> friend class Luna;

    void* raw_state(void);

public:
    state(void);
    explicit state(void*);
    ~state(void);

	state & operator= (state & arg);

	void new_state();
    void close(void);
    void get_global(const std::string&);
    bool get_metafield(const int, const std::string&);
    bool get_metatable(const int = -1);
    void get_table(const int = -2);
    int get_top(void);
    void insert(const int);
    bool is_boolean(const int = -1);
    bool is_function(const int = -1);
    bool is_nil(const int = -1);
    bool is_number(const int = -1);
    bool is_string(const int = -1);
    bool is_table(const int = -1);
    bool is_userdata(const int = -1);
    void load_file(const std::string&);
    void load_string(const std::string&);
    void new_table(void);
    template< typename Type > Type* new_userdata(void);
    bool next(const int = -2);
    void open_base(void);
    void open_string(void);
    void open_table(void);
    void pcall(const int, const int, const int);
    void pop(const int);
    void push_boolean(const bool);
    void push_cxx_closure(cxx_function, const int);
    void push_cxx_function(cxx_function);
    void push_integer(const int);
    void push_nil(void);
    void push_string(const std::string&);
	void push_literal(const std::string&);
    void push_value(const int = -1);
    void raw_get(const int = -2);
    void raw_set(const int = -3);
    void set_global(const std::string&);
    void set_metatable(const int = -2);
    void set_table(const int = -3);
    bool to_boolean(const int = -1);
    long to_integer(const int = -1);
    template< typename Type > Type* to_userdata(const int = -1);
    std::string to_string(const int = -1);
    int upvalue_index(const int);

	void findLib(const std::string& name, const int size, const int nup=0);
	void push_lightuserdata(void *);
	void push_userdata(const void *, const std::string& name);

	void set_field(const std::string& name, const double value, const int index=-3);
	void set_field(const std::string& name, const int value, const int index=-3);
	void set_field(const std::string& name, const std::string& value, const int index=-3);
	void set_field(const std::string& name, const bool value, const int index=-3);
	void set_field(const int index, const std::string& name);
	void get_field(const int index, const std::string& name);
	
	void push_number(const double value);
	const double to_number(const int);

	void remove(const int);

	bool new_metatable(const std::string&);
	void get_metatable(const std::string&);
	template< typename Type > Type* check_userdata(const int, const std::string&);
	void * getLuaState();
	void error(const std::string&);
	void error(const char * fmt, ...);
	void push_fstring(const char * fmt, ...);
    const void* to_lightuserdata(const int);
	int ref();
	int ref(const int);
	void unref(const int, const int);
	void unref(const int);
	void raw_geti(const int, const int);
	const size_t obj_len(const int);

	lutok::state * newState();
	void openLibs();
	void cpcall(cxx_function_ex, void *);
	void set_top(int);
	const char * type(int);
};


}  // namespace lutok

#endif  // !defined(LUTOK_STATE_HPP)
