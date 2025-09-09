import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Factorization {

  public static List<BigInteger> generateLargeNumbers(int n, int bitLength) {
    Random rand = new Random();
    List<BigInteger> numbers = new ArrayList<>();
    for (int i = 0; i < n; i++) {
      numbers.add(new BigInteger(bitLength, rand));
    }
    return numbers;
  }

  public static void sequentialFactorization(List<BigInteger> numbers) {
    for (BigInteger num : numbers) {
      factorize(num);
    }
    ;
  }

  public static void parallelFactorization(List<BigInteger> numbers) {
    numbers.parallelStream().forEach(Factorization::factorize);
  }

  public static List<BigInteger> factorize(BigInteger number) {
    List<BigInteger> factors = new ArrayList<>();
    BigInteger i = BigInteger.valueOf(2);
    BigInteger n = number;

    while (i.multiply(i).compareTo(n) <= 0) {
      if (n.mod(i).equals(BigInteger.ZERO)) {
        factors.add(i);
        n = n.divide(i);
      } else {
        i = i.add(BigInteger.ONE);
      }
    }
    if (n.compareTo(BigInteger.ONE) > 0) {
      factors.add(n);
    }
    return factors;
  }

  public static void main(String[] args) {
    int n = 100;
    int bitLength = 50;
    List<BigInteger> numbers = generateLargeNumbers(n, bitLength);

    if (args.length > 0 && args[0].equals("parallel")) {
      parallelFactorization(numbers);
    } else {
      sequentialFactorization(numbers);
    }
  }

}
