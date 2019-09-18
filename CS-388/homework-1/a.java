// 3a, page 355
class SquareCube {
	public static void main(String args[]) {
		System.out.println("number\tsquare\tcube");

		for (int i = 0; i <= 10; i++) {
			int square = i * i;
			int cube = i * i * i;
			String output = String.format("%d\t%d\t%d", i, square, cube);
			System.out.println(output);
		}
	}
}
