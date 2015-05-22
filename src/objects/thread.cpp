#include "objects/thread.hpp"
#include <lua.hpp>

static LuaSDL::LuaThread *waitsend = NULL;
static LuaSDL::LuaThread *waitreceive = NULL;
static SDL_mutex* kernel_access = SDL_CreateMutex();

static LuaSDL::LuaThread *searchmatch (const char *channel, LuaSDL::LuaThread **list) {
	LuaSDL::LuaThread *node = *list;
	if (node == NULL) return NULL; /* empty list? */
	do {
		if (strcmp(channel, node->channel) == 0) { /* match? */
			/* remove node from the list */
			if (*list == node) /* is this node the first element? */
				*list = (node->next == node) ? NULL : node->next;
			node->previous->next = node->next;
			node->next->previous = node->previous;
			return node;
		}
		node = node->next;
	} while (node != *list);
	return NULL; /* no match */
}

static LuaSDL::LuaThread *getself (State & state) {
	LuaSDL::LuaThread *p;
	state.get_field(LUA_REGISTRYINDEX, "_SELF");
	p = state.to_userdata<LuaSDL::LuaThread>();
	stack->pop(1);
	return p;
}

static LuaSDL::LuaThread *getself (State & state) {
	LuaSDL::LuaThread *p;
	state->get_field(LUA_REGISTRYINDEX, "_SELF");
	p = state->to_userdata<LuaSDL::LuaThread>();
	state->pop(1);
	return p;
}

static void movevalues (State *send, State *rec) {
	int n = send->get_top();
	int i;
	for (i = 2; i <= n; i++){ /* move values to receiver */
		if (rec){
			rec->push_string(send->to_string(i));
		}
	}
}

static void waitonlist (State & state, const char *channel, LuaSDL::LuaThread **list) {
	LuaSDL::LuaThread *p = getself(state);
	/* link itself at the end of the list */
	if (*list == NULL) { /* empty list? */
		*list = p;
		p->previous = p->next = p;
	} else {
		p->previous = (*list)->previous;
		p->next = *list;
		p->previous->next = p->next->previous = p;
	}
	p->channel = channel;
	do { /* waits on its condition variable */
		SDL_CondWait(p->cond, kernel_access);
	} while (p->channel);
}

static int ll_send (State & state) {
	LuaSDL::LuaThread *p;
	if (stack->is<LUA_TSTRING>(1)){
		std::string & channel = stack->to<const std::string>(1);
		SDL_mutexP(kernel_access);
		p = searchmatch(channel.c_str(), &waitreceive);
		if (p) { /* found a matching receiver? */
			movevalues(&state, p->state); /* move values to receiver */
			p->channel = NULL; /* mark receiver as not waiting */
			SDL_CondSignal(p->cond); /* wake it up */
		}
		else
			waitonlist(state, channel.c_str(), &waitsend);
		SDL_mutexV(kernel_access);
	}
	return 0;
}

static int ll_receive (State & state) {
	LuaSDL::LuaThread *p;
	if (stack->is<LUA_TSTRING>(1)){
		std::string & channel = stack->to<const std::string>(1);
		state.set_top(1);
		SDL_mutexP(kernel_access);
		p = searchmatch(channel.c_str(), &waitsend);
		if (p) { /* found a matching sender? */
			movevalues(p->state, &state); /* get values from sender */
			p->channel = NULL; /* mark sender as not waiting */
			SDL_CondSignal(p->cond); /* wake it up */
		}
		else
			waitonlist(state, channel.c_str(), &waitreceive);
		SDL_mutexV(kernel_access);
		/* return all stack values but channel */
		return state.get_top() - 1;
	}else{
		return 0;
	}
}

static int ll_thread (void *arg) {
	State & state = static_cast<State *>(arg);
	LuaSDL::moduleDef module;

	int t_top = state->get_top();
	state->openLibs();
	t_top = state->get_top();
	LuaSDL::init_thread(*state, module);
	t_top = state->get_top();
	lutok::registerLib(*state, "SDL", module);
	state->pop(1);
	t_top = state->get_top();
	try{
		state->pcall(0,0,0);
	}catch(lutok::api_error & error){
		t_top = state->get_top();
		const char * str = state->typeName(1);
		fprintf(stderr, "thread error: %s", error.what());
	}
	SDL_DestroyCond(getself(state)->cond);
	state->close();
	return NULL;
}

static int ll_start (State & state) {
	SDL_Thread * thread;
	if (stack->is<LUA_TSTRING>(1)){
		State * L1 = state.newState();
		if (L1 == NULL)
			state.error("unable to create new state");

		try{
			L1->load_string(stack->to<const std::string>(1));
		}catch(lutok::api_error & error){
			state.error("error starting thread: %s", error.what());
		}
		
		if ((thread = SDL_CreateThread(ll_thread, NULL, L1)) == NULL)
			state.error("unable to create new thread: %s", SDL_GetError());
	}
	return 0;
}

void LuaSDL::init_thread(State & state, Module & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Thread);
	/* create own control block */
	LuaSDL::LuaThread * self = state.new_userdata<LuaSDL::LuaThread>();
	stack->setField(LUA_REGISTRYINDEX, "_SELF");
	self->tid = SDL_ThreadID();
	self->channel = NULL;
	self->cond = SDL_CreateCond();
	self->state = &state;
	module["Thread"] = ll_start;
	module["thread_send"] = ll_send;
	module["thread_receive"] = ll_receive;
}
