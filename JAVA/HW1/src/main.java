
public class main {


	public static void main(String[] args) {
		MySet_F74976120_1 a;
		MySet_F74976120_1 b;
		
		if(args.length > 1){
			a = new MySet_F74976120_1(args[0]);
			b = new MySet_F74976120_1(args[1]);
		}
		else if(args.length > 0){
			a = new MySet_F74976120_1(args[0]);
			b = new MySet_F74976120_1();
		}
		else{
			a = new MySet_F74976120_1();
			b = new MySet_F74976120_1();
		}

		System.out.println("========================================");
		System.out.println("輸入集合為： " + a.toString() + " " + b.toString());
		System.out.println("第一個集合大小： " + a.size());
		System.out.println("第一個集合是否為空集合： " + a.isEmpty());
		System.out.println("第一個集合中最小值： " + a.getMinimalElement());
		System.out.println("第一個集合中最大值： " + a.getMaximalElement());
		a.sort();
		System.out.println("第一個集合排序結果： " + a.toString());
		System.out.print("第一個集合所有子集合： ");
		a.showSubset();
		System.out.print("\n第一個集合總和為質數的子集合： ");
		a.showPrimeofSubset();
		System.out.println("\n第一個集合與第二個集合是否相同： " + a.equals(b));
		System.out.println("第一個集合是否為第二個集合的超集合： " + a.superSet(b));
		System.out.println("第一個集合是否為第二個集合的子集合： " + a.subSet(b));
		System.out.println("第一個集合聯集第二個集合： " + a.union(b));
		System.out.println("第一個集合交集第二個集合： " + a.intersection(b));
		System.out.println("第一個集合差集第二個集合： " + a.difference(b));
		System.out.println("========================================");
		

	}

}
