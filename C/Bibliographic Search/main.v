module main (
	input	[7:0]	gmac_rx_data,
	input			gmac_rx_dvld,
	input			reset,
	input			rxcoreclk,
	output reg		match
);
	reg	[7:0]		key [63:0][63:0];
	reg	[8*64-1:0]	keyt [63:0];
	reg	[31:0]		keyl [63:0];
	reg	[31:0]		keyn;
	reg	[31:0]		glist [63:0][63:0][2:0];
	reg				olist [63:0];
	reg	[31:0]		flist [63:0];
	integer			state;

	initial
	begin
		task_initial();
		task_goto_cons();
		task_fail_cons();
	end
	
	always@(posedge rxcoreclk)
	begin
		if (gmac_rx_dvld && ~reset) task_match(gmac_rx_data);
		else
		begin
			state = 0;
			match = 0;
		end
	end
	
	task task_initial;
		integer	i, j;
		reg		flag;

		begin
			for (i = 0; i < 64; i = i + 1)
			begin
				flist[i] = 0;
				olist[i] = 0;
				for (j = 0; j < 64; j = j + 1)
				begin
					glist[i][j][0] = 0;
					glist[i][j][1] = -1;
				end
			end
			
			// Keywords
			keyt[0] = "he";
			keyt[1] = "she";
			keyt[2] = "his";
			keyt[3] = "hers";
			
			for (keyn = 0; keyt[keyn] != 0; keyn = keyn + 1) keyn = keyn;
			for (i = 0; i < keyn; i = i + 1)
			begin
				flag = 1;
				for (j = 0; flag; j = j + 1)
				begin
					if (!keyt[i][7:0])
					begin
						flag = 0;
						keyl[i] = j;
					end
					key[i][j] = keyt[i][7:0];
					keyt[i] = keyt[i] >> 8;
				end
			end
			
			state = 0;
			match = 0;
		end
	endtask
	
	task task_match;
		input	[7:0]		gmac_rx_data;
		
		begin
			while (func_goto(state, gmac_rx_data) == -1) state = flist[state];
			state = func_goto(state, gmac_rx_data);
			
			if (olist[state]) match = 1;
			if (match) $display("match\n");
			else $display("not match\n");
		end
	endtask

	function signed [31:0]	func_goto;
		input	[31:0]	state;
		input	[7:0]	inputc;
		reg				flag;
		integer			i;
		
		begin
			flag = 1;
			
			for (i = 0; flag; i = i + 1)
			begin
				if (glist[state][i][1] == -1)					// No other rule
				begin
					flag = 0;
					if (state == 0) func_goto = 0;
					else func_goto = -1;
				end
				else if (glist[state][i][0][7:0] == inputc)		// Match
				begin
					flag = 0;
					func_goto = glist[state][i][1];
				end
			end
		end
	endfunction
		
	task task_goto_cons;
		reg				flag;
		integer			i, j, k, state, newstate;
		
		begin
			newstate = 0;
			
			for (i = 0; i < keyn; i = i + 1)
			begin
				state = 0;
				for (j = keyl[i] - 1; func_goto(state, key[i][j]) > 0; j = j - 1)
					state = func_goto(state, key[i][j]);
				
				for (j = j; j >= 0; j = j - 1)
				begin
					newstate = newstate + 1;
					
					flag = 1;
					for (k = 0; flag; k = k + 1)
					begin
						if (glist[state][k][1] == -1)
						begin
							glist[state][k][0][7:0] = key[i][j];
							glist[state][k][1] = newstate;
							state = newstate;
							flag = 0;
						end
					end
				end
				
				olist[state] = 1;
			end
		end
	endtask
	
	task task_fail_cons;
		integer			queue [63:0];
		integer			front, rear, i, j, k, l, pop, state;
		reg				flag;
		
		begin
			front = 0;
			rear = -1;
			flag = 1;
			
			for (i = 0; flag; i = i + 1)
			begin
				if (glist[0][i][1] == -1) flag = 0;
				else
				begin
					rear = rear + 1;
					queue[rear] = glist[0][i][1];
					flist[glist[0][i][1]] = 0;
				end
			end
			
			while (rear >= front)
			begin
				pop = queue[front];
				front = front + 1;
				
				flag = 1;
				for (i = 0; flag; i = i + 1)
				begin
					if (glist[pop][i][1] == -1) flag = 0;
					else
					begin
						rear = rear + 1;
						queue[rear] = glist[pop][i][1];
						
						state = flist[pop];
						while (func_goto(state, glist[pop][i][0]) == -1) state = flist[state];
						flist[glist[pop][i][1]] = func_goto(state, glist[pop][i][0]);
						
						if (olist[flist[glist[pop][i][1]]]) olist[glist[pop][i][1]] = 1;
					end
				end
			end
		end
	endtask
	
endmodule
