import java.util.Scanner;

public class java {
  public static void main(String args[]) {
    Scanner input = new Scanner(System.in);
    String s;
    while (input.hasNextLine()) {
      s = input.nextLine();
      int ans = 1;
      int contador = 0;
      for (int i = 0; i < s.length(); i += 1) {
        if (s.charAt(i) == '(')
          contador += 1;
        else if (s.charAt(i) == ')')
          contador -= 1;
        if (contador < 0)
          ans = 0;
      }
      if (contador != 0)
        ans = 0;
      if (ans == 1)
        System.out.println("correct");
      else
        System.out.println("incorrect");
    }
  }
}