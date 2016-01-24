import java.io.*;

public class MyCalculator_F74976120_1
{
	String inputFileName = ""; //輸入檔案名稱
	String outputFileName = ""; //輸出檔案名稱
	String result = "";

	public MyCalculator_F74976120_1(String inputFileName, String outputFileName)
	{
		//空白建構元，初始化本類別該初始化的所有變數。
		this.inputFileName = inputFileName;
		this.outputFileName = outputFileName;
	}
	
	private String calculate(int x, int y, char op)
	{
		//System.out.println(x + "," + y + "," + op);
		switch(op)
		{
		case '+':
			return (x + y) + "";
		case '-':
			return (x - y) + "";
		case '*':
			return (x * y) + "";
		case '/':
			return (x / y) + "";
		default:
			return "1";
		}
	}
	
	private String calculate(String expr)
	{
		int idxl, idxr, idxo = 0;
		boolean act; 
		String op = "+-*/", oppm = "+-";
		
		do
		{
			act = false;
			idxl = 0;
			idxr = expr.length() - 1;
			
			for(int i = 0; i < expr.length(); i++)
			{
				if(op.indexOf(expr.charAt(i)) > -1 && (expr.charAt(i) != '-' || (i > 0 && op.indexOf(expr.charAt(i - 1)) == -1)))
				{
					if(act)
					{
						idxr = i - 1;
						break;
					}
					if(oppm.indexOf(expr.charAt(i)) > -1) idxl = i + 1;
					else
					{
						idxo = i;
						act = true;
					}
				}
			}
			//System.out.println(idxl + "," + idxr);
			if(act) expr = expr.replace(expr.substring(idxl, idxr + 1), calculate(Integer.parseInt(expr.substring(idxl, idxo)), Integer.parseInt(expr.substring(idxo + 1, idxr + 1)), expr.charAt(idxo)));
		}
		while(act);
		
		do
		{
			act = false;
			idxl = 0;
			idxr = expr.length() - 1;

			for(int i = 0; i < expr.length(); i++)
			{
				if(oppm.indexOf(expr.charAt(i)) > -1 && (expr.charAt(i) != '-' || (i > 0 && oppm.indexOf(expr.charAt(i - 1)) == -1)))
				{
					if(act)
					{
						idxr = i - 1;
						break;
					}
					idxo = i;
					act = true;
				}
			}
			//System.out.println(idxl + "," + idxr);
			if(act) expr = expr.replace(expr.substring(idxl, idxr + 1), calculate(Integer.parseInt(expr.substring(idxl, idxo)), Integer.parseInt(expr.substring(idxo + 1, idxr + 1)), expr.charAt(idxo)));
		}
		while(act);

		return expr;
	}
	
	public void calculate()
	{
		//根據inputFileName檔案的內容，執行相關運算。
		try
		{
			String line = new BufferedReader(new FileReader(inputFileName)).readLine();
			//System.out.println(line);
			while(line.indexOf('[') > -1)
			{
				String subunit = line.substring(line.indexOf('[') + 1, line.indexOf(']'));
				line = line.replace('[' + subunit + ']', '(' + new BufferedReader(new FileReader(subunit)).readLine() + ')');
				//System.out.println(line);
			}
			
			System.out.println(line);
			while(line.indexOf('(') > -1)
			{
				int idxl = -1, idxr = -1;
				String subunit = "";
				
				while((idxr = line.indexOf(')', idxl + 1)) > (idxl = line.indexOf('(', idxl + 1)) && idxl != -1)
				{
					//System.out.println(idxl + "," + idxr);
					subunit = line.substring(idxl + 1, idxr);
				}
				line = line.replace('(' + subunit + ')', calculate(subunit));
				System.out.println(line);
			}
			result = calculate(line);
			System.out.println(result);
		}
		catch(IOException e)
		{
			System.out.println(e);
		}
	}

	public void save()
	{
		//將運算結果存到outputFileName檔案中。
		try
		{
			FileWriter fw = new FileWriter(outputFileName);
			fw.write(result);
			fw.close();
		}
		catch(IOException e)
		{
			System.out.println(e);
		}
	}

	public static void main(String args[])
	{
		//args[0]: 輸入檔案名稱
		//args[1]: 輸出檔案名稱
		MyCalculator_F74976120_1 calculator = new MyCalculator_F74976120_1(args[0], args[1]);

		calculator.calculate();
		calculator.save();
	}
}