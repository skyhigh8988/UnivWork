//#include <systemc.h>
#include "counter.h"

int sc_main(int argc, char* argv[])
{
	// signal declaration
	sc_clock			clk("clk", 1, SC_SEC);	
	sc_signal<int>		val;
	//sc_signal<bool>		green;
	//sc_signal<bool>		yellow;

	// module declaration
	counter		counter0("counter0");
	// signal connection
	counter0.clk(clk);
	counter0.val(val);

	// run simulation
	sc_start(86400000, SC_SEC);
	
	system("pause");
	return 0;
}