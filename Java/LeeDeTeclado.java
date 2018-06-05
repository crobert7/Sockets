import java.io.*;

public class LeeDeTeclado
{
 public static void main(String arg[]) throws Exception
 {
   BufferedReader br = new BufferedReader( new InputStreamReader( System.in ) );
   String s = br.readLine();
   System.out.println( s );
 }
}
