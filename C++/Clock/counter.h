#include <systemc.h>

SC_MODULE(counter)
{
	sc_in_clk		clk;
	sc_out<int>  	val;
	//sc_out<bool>	green;
	//sc_out<bool>	yellow;

	void process_func();

	SC_CTOR(counter)
	{
		SC_CTHREAD(process_func, clk.pos());
	}
};

