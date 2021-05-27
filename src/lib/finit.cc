typedef void (*finit_ptr)();

extern "C" finit_ptr start_ctors;
extern "C" finit_ptr end_ctors;
extern "C" void call_ctors();
extern "C" void call_dtors();

void call_ctors()
{
	for (finit_ptr* ctor = &start_ctors; ctor != &end_ctors; ++ctor)
	{
		(*ctor)();
	}
}

extern "C" finit_ptr start_dtors;
extern "C" finit_ptr end_dtors;

void call_dtors()
{
	for (finit_ptr* dtor = &start_dtors; dtor != &end_dtors; ++dtor)
	{
		(*dtor)();
	}
}

