import java.util.Arrays;
import java.lang.Math;

public class MySet_F74976120_1 {
	private int[] elements;
	
	public MySet_F74976120_1(){
		elements = new int[0];
	}
	
	public MySet_F74976120_1(String input){
		if(input.length() == 0) elements = new int[0];
		else{
			String[] temp = input.split(",");
			elements = new int[temp.length];
			for(int i = 0; i < temp.length; i++){
				elements[i] = Integer.parseInt(temp[i]);
			}
		}
	}
	
	public int size(){
		return elements.length;
	}
	
	public boolean isEmpty(){
		return elements.length == 0;
	}
	
	public int getMinimalElement(){
		int min = (isEmpty() ? 0 : elements[0]);
		for(int i = 1; i < elements.length; i++){
			if(elements[i] < min) min = elements[i];
		}
		return min;
	}
	
	public int getMaximalElement(){
		int max = (isEmpty() ? 0 : elements[0]);
		for(int i = 1; i < elements.length; i++){
			if(elements[i] > max) max = elements[i];
		}
		return max;
	}
	
	public void sort(){
		Arrays.sort(elements);
	}
	
	public void showSubset(){
		//this.sort();
		int n = elements.length;
		String temp = "";
		for(int i = 0; i < n; i++){
			int p = i;
			int[] e = new int[i + 1];
			int[] c = new int[i + 1];
			for(int j = 0; j < i + 1; j++){
				c[j] = j;
				e[j] = elements[j];
				if(!temp.equals("")) temp += ",";
				temp += elements[j];
			}
			System.out.print("{" + temp + "} ");
			temp = "";
			while(p >= 0){
				if(c[p] + 1 < n - (i - p)){
					e[p] = elements[++c[p]];
					if(p != i){
						for(int j = p + 1; j < i + 1; j++){
							c[j] = c[j - 1] + 1;
							e[j] = elements[c[j - 1] + 1];
						}
						p = i;
					}
					for(int j = 0; j < i + 1; j++){
						if(!temp.equals("")) temp += ",";
						temp += e[j];
					}
					System.out.print("{" + temp + "} ");
					temp = "";
				}
				else p--;
			}
		}
	}
	
	private boolean isPrime(int n){
		if(n < 2) return false;
		for(int i = 2; i <= Math.pow(n, 0.5); i++){
			if(n % i == 0) return false;
		}
		return true;
	}
	
	public void showPrimeofSubset(){
		//this.sort();
		int n = elements.length;
		String temp = "";
		for(int i = 0; i < n; i++){
			int p = i, amout = 0;
			int[] e = new int[i + 1];
			int[] c = new int[i + 1];
			for(int j = 0; j < i + 1; j++){
				c[j] = j;
				e[j] = elements[j];
			}
			for(int k = 0; k < i + 1; k++){
				amout += e[k];
			}
			if(isPrime(amout)){
				for(int j = 0; j < i + 1; j++){
					if(!temp.equals("")) temp += ",";
					temp += e[j];
				}
				System.out.print("{" + temp + "} ");
				temp = "";
			}
			while(p >= 0){
				if(c[p] + 1 < n - (i - p)){
					e[p] = elements[++c[p]];
					if(p != i){
						for(int j = p + 1; j < i + 1; j++){
							c[j] = c[j - 1] + 1;
							e[j] = elements[c[j - 1] + 1];
						}
						p = i;
					}
					amout = 0;
					for(int k = 0; k < i + 1; k++){
						amout += e[k];
					}
					if(isPrime(amout)){
						for(int j = 0; j < i + 1; j++){
							if(!temp.equals("")) temp += ",";
							temp += e[j];
						}
						System.out.print("{" + temp + "} ");
						temp = "";
					}
				}
				else p--;
			}
		}
	}
	
	public boolean equals(MySet_F74976120_1 s){
		sort();
		s.sort();
		return Arrays.equals(s.elements, elements);
	}
	
	public boolean subSet(MySet_F74976120_1 s){
		sort();
		s.sort();
		for(int i = 0; i < elements.length; i++)
			if(Arrays.binarySearch(s.elements, elements[i]) < 0) return false;
		return true;
	}

	public boolean superSet(MySet_F74976120_1 s){
		sort();
		s.sort();
		for(int i = 0; i < s.elements.length; i++)
			if(Arrays.binarySearch(elements, s.elements[i]) < 0) return false;
		return true;
	}
	
	public MySet_F74976120_1 union(MySet_F74976120_1 s){
		sort();
		s.sort();
		String n = "";
		for(int i = 0; i < elements.length; i++){
			if(i != 0) n += ",";
			n += elements[i];
		}
		for(int i = 0; i < s.elements.length; i++)
			if(Arrays.binarySearch(elements, s.elements[i]) < 0) n += "," + s.elements[i];
		return new MySet_F74976120_1(n);
	}
	
	public MySet_F74976120_1 intersection(MySet_F74976120_1 s){
		sort();
		s.sort();
		String n = "";
		for(int i = 0; i < s.elements.length; i++)
			if(Arrays.binarySearch(elements, s.elements[i]) >= 0){
				if(n.length() != 0) n += ",";
				n += s.elements[i];
			}
		return new MySet_F74976120_1(n);
	}
	
	public MySet_F74976120_1 difference(MySet_F74976120_1 s){
		sort();
		s.sort();
		String n = "";
		for(int i = 0; i < elements.length; i++)
			if(Arrays.binarySearch(s.elements, elements[i]) < 0){
				if(n.length() != 0) n += ",";
				n += elements[i];
			}
		return new MySet_F74976120_1(n);
	}
	
	public String toString(){
		String n = "{";
		for(int i = 0; i < elements.length; i++){
			if(i != 0) n += ",";
			n += elements[i];
		}
		return n + "}";
	}
}
